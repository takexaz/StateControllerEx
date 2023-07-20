// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include <Mebius.h>
#include <StateControllerEx.h>

auto SCtrlParseElemType = reinterpret_cast<bool (*)(TPFILE* tpf, STATE_INFO* sinfo, PLAYER_CACHE* pcache)>(0x46aa60);
auto SCtrlRCElemFree = reinterpret_cast<void (*)(STATE_INFO* sinfo)>(0x4718d0);
auto ConstExpI = reinterpret_cast<void (*)(EVAL_EXP* ptr, int value)>(0x406f20);
auto ConstExpF = reinterpret_cast<void (*)(EVAL_EXP* ptr, float value)>(0x406fa0);
auto EvalExpressionI = reinterpret_cast<int (*)(PLAYER* p, EVAL_EXP* ptr, int warnNo)>(0x4075e0);
auto EvalExpressionF = reinterpret_cast<float (*)(PLAYER* p, EVAL_EXP* ptr)>(0x4076d0);

int findTargetStateByName(string);
int regModState(int);
int procModState(void);
void freeModState(void);

vector<STX*> gStateList;
DWORD STATEID = 0x7FFFFFFF;

// 補助関数
void constExp(EVAL_EXP* ptr, int value) {
    ConstExpI(ptr, value);
    return;
}

void constExp(EVAL_EXP* ptr, float value) {
    ConstExpF(ptr, value);
    return;
}

int EvalExpression(PLAYER* p, EVAL_EXP* ptr, int warnNo) {
    return EvalExpressionI(p,ptr,warnNo);
}

float EvalExpression(PLAYER* p, EVAL_EXP* ptr) {
    return EvalExpressionF(p,ptr);
}

int GetQuotedString(TPFILE* tpf, const char* label, const char* dest, size_t size) {
    auto GetQuotedStringWrap = reinterpret_cast<int (*)(TPFILE * wtpf, const char* wlabel, const char* wdest, int wsize, int zero)>(0x415df0);
    return GetQuotedStringWrap(tpf, label, dest, size - 1, 0);
}

void setErrorText(const char* error) {
    char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
    snprintf(mugen_error, 1023, "%s", error);
    return;
}

void setErrorText(const char* state, const char* error) {
    char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
    snprintf(mugen_error, 1023, "%s:%s", state, error);
    return;
}

// 本処理
int findTargetStateByName(string type) {
    for (size_t i = 0; i < gStateList.size(); i++) {
        if (gStateList[i]->type == type) {
            return static_cast<int>(i);
        }
    }
    return HOOK_NOT_FOUND;
}

void addState(STX* stx) {
    if (findTargetStateByName(stx->type) == -1) {
        gStateList.push_back(stx);
    }
    return;
}

int regModState(int RETVALUE) {
    if (RETVALUE == 1) return RETVALUE;

    char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
    char* error = (char*)"Not a ";
    if (strncmp(mugen_error, error, 6) == 0) {

        DWORD* stack;
        _asm {
            MOV stack, EBP
            ADD stack, 0x2C
        }
        TPFILE* tpf = (TPFILE*)*(stack);
        STATE_INFO* sinfo = (STATE_INFO*)*(stack + 1);
        PLAYER_CACHE* pcache = (PLAYER_CACHE*)*(stack + 2);

        // ステコン名から番号取得
        string statename(mugen_error + 23);
        int index = findTargetStateByName(statename);
        // 見つからなければエラー
        if (index == -1) return RETVALUE;

        // ID登録
        sinfo->stateid = STATEID;
        sinfo->substateid = index;
        // エラー削除
        mugen_error[0] = '\x0';

        auto reg = reinterpret_cast<int (*)(TPFILE*, STATE_INFO*, PLAYER_CACHE*)>(gStateList[index]->reg);
        return reg(tpf, sinfo, pcache);
    }
    else {
        return RETVALUE;
    }
}

int procModState(void) {
    DWORD* stack;
    _asm {
        MOV stack, EBP
        ADD stack, 0x10A8
    }
    PLAYER* p = (PLAYER*)*(stack);
    STATE_INFO* sinfo = (STATE_INFO*)*(stack + 1);

    if (sinfo->stateid != STATEID) return TRUE;
    auto proc = reinterpret_cast<int (*)(PLAYER * , STATE_INFO*)>(gStateList[sinfo->substateid]->proc);
    proc(p, sinfo);
    return FALSE;
}

void freeModState(void) {
    DWORD* stack;
    _asm {
        MOV stack, EBP
        ADD stack, 0x20
    }

    STATE_INFO* sinfo = (STATE_INFO*)*(stack);

    if (sinfo->stateid != STATEID) return;
    auto free = reinterpret_cast<int (*)(STATE_INFO*)>(gStateList[sinfo->substateid]->free);
    free(sinfo);

    return;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        // ステート登録フック
        Hook(SCtrlParseElemType, regModState, TAIL);

        // ステート処理埋め込み
        writeGotoOpcode((void*)0x471554, procModState, CALL);
        BYTE proc[37] = {
            0x85,0xC0,0x74,0x25,0x68,0x78,0xC3,0x4A,
            0x00,0xA1,0x4C,0x5B,0x4B,0x00,0x05,0x34,
            0xC5,0x00,0x00,0x50,0xE8,0xE5,0x0C,0x02,
            0x00,0x83,0xC4,0x08,0xE8,0xE6,0x42,0xFA,
            0xFF,0x90,0x90,0x90,0x90 };
        writeBytesToROM((void*)0x471559, proc, sizeof(proc));

        // ステート開放フック
        Hook(SCtrlRCElemFree, freeModState, HEAD);

        LoadAllDLL("mods", ".stx");
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH: {
        FreeAllDLL("mods", ".stx");
        break;
    }
    }
    return TRUE;
}

