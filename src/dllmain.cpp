#include "_StateControllerExtension.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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
