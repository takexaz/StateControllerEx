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
        MUGEN_SC_DATA_EX* scdataEx = (MUGEN_SC_DATA_EX*)*(stack + 1);
        MUGEN_PLAYER_INFO* pinfo = (MUGEN_PLAYER_INFO*)*(stack + 2);

        // ステコン名から番号取得
        string statename(mugen_error + 23);
        int index = findTargetStateByName(statename);
        // 見つからなければエラー
        if (index == -1) return RETVALUE;

        // エラー削除
        mugen_error[0] = '\x0';
        scdataEx->SCX = new MEBIUS_SCX_DATA;

        auto reg = reinterpret_cast<int (*)(TPFILE*, MUGEN_SC_DATA_EX*, MUGEN_PLAYER_INFO*)>(gStateList[index].reg);
        RETVALUE = reg(tpf, scdataEx, pinfo);

        // ID登録
        scdataEx->scID = (MUGEN_SC_ID)STATEID;
        scdataEx->SCX->exscID = index;
    }
    return RETVALUE;
}

int procModState(void) {
    DWORD* stack;
    _asm {
        MOV stack, EBP
        ADD stack, 0x10A8
    }
    MUGEN_PLAYER* player = (MUGEN_PLAYER*)*(stack);
    MUGEN_SC_DATA_EX* scdataEx = (MUGEN_SC_DATA_EX*)*(stack + 1);

    if (scdataEx->scID != STATEID) return TRUE;
    auto proc = reinterpret_cast<int (*)(MUGEN_PLAYER*, MUGEN_SC_DATA_EX*)>(gStateList[scdataEx->SCX->exscID].proc);
    proc(player, scdataEx);
    return FALSE;
}

void freeModState(void** stack) {
    MUGEN_SC_DATA_EX* scdataEx = (MUGEN_SC_DATA_EX*)*(stack);

    if (scdataEx->scID != STATEID) return;
    auto free = reinterpret_cast<int (*)(MUGEN_SC_DATA_EX*)>(gStateList[scdataEx->SCX->exscID].free);
    free(scdataEx);

    return;
}