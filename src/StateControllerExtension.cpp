#include "_StateControllerExtension.h"

vector<STX> gStateList;

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

int clamp(int value, int minimum, int maximum) {
    return min(max(minimum, value), maximum);
}

// 本処理
int findTargetStateByName(string type) {
    for (size_t i = 0; i < gStateList.size(); i++) {
        if (gStateList[i].type == type) {
            return static_cast<int>(i);
        }
    }
    return HOOK_NOT_FOUND;
}

void addState(STX stx) {
    if (findTargetStateByName(stx.type) == -1) {
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
            ADD stack, 0x30
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

        auto reg = reinterpret_cast<int (*)(TPFILE*, STATE_INFO*, PLAYER_CACHE*)>(gStateList[index].reg);
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
    auto proc = reinterpret_cast<int (*)(PLAYER * , STATE_INFO*)>(gStateList[sinfo->substateid].proc);
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
    auto free = reinterpret_cast<int (*)(STATE_INFO*)>(gStateList[sinfo->substateid].free);
    free(sinfo);

    return;
}