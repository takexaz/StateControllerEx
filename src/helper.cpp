#include "_StateControllerExtension.h"

void addState(STX stx) {
    transform(stx.type.begin(), stx.type.end(), stx.type.begin(), ::tolower);
    if (findTargetStateByName(stx.type) == -1) {
        gStateList.push_back(stx);
    }
    return;
}

int regModState(void** stack, int RETVALUE) {
    if (RETVALUE == 1) return RETVALUE;

    char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
    char* error = (char*)"Not a ";
    if (strncmp(mugen_error, error, 6) == 0) {
        TPFILE* tpf = (TPFILE*)*(stack);
        STATE_INFO* sinfo = (STATE_INFO*)*(stack + 1);
        PLAYER_CACHE* pcache = (PLAYER_CACHE*)*(stack + 2);

        // ステコン名から番号取得
        string statename(mugen_error + 23);
        int index = findTargetStateByName(statename);
        // 見つからなければエラー
        if (index == -1) return RETVALUE;

        // エラー削除
        mugen_error[0] = '\x0';

        auto reg = reinterpret_cast<int (*)(TPFILE*, STATE_INFO*, PLAYER_CACHE*)>(gStateList[index].reg);
        RETVALUE = reg(tpf, sinfo, pcache);

        // ID登録
        sinfo->stateid = STATEID;
        sinfo->substateid = index;
    }
    return RETVALUE;
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
    auto proc = reinterpret_cast<int (*)(PLAYER*, STATE_INFO*)>(gStateList[sinfo->substateid].proc);
    proc(p, sinfo);
    return FALSE;
}

void freeModState(void** stack) {
    STATE_INFO* sinfo = (STATE_INFO*)*(stack);

    if (sinfo->stateid != STATEID) return;
    auto free = reinterpret_cast<int (*)(STATE_INFO*)>(gStateList[sinfo->substateid].free);
    free(sinfo);

    return;
}