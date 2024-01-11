#include <Windows.h>
#include <Mebius.hpp>
#include <STX.hpp>
#include <_hooking.hpp>

using namespace stx::state::argument;
using namespace stx::state::parameter;
using namespace stx::state::controller;
using namespace stx::state::processor;

BOOL set_round_timer(Processor* p, stx::mugen::PLAYER* player, stx::mugen::PLAYER_REDIRECTS* redirects) {

    volatile DWORD* roundtimer = (DWORD*)(*((DWORD*)0x4b5b4c) + 0xBC40);

    int i;
    if (p->get_value<int>("value", "time", &i)) {
        *roundtimer = i;
    }

    return true;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        PLOGD << "Initializing StateControllerExtension.";
        mebius::hook::HookOnTail(stx::mugen::SCtrlParseElemType, stx::hooking::reg::regmodstate);
        PLOGD << "Hooked SCtrlParseElemType.";
        mebius::inline_hook::HookInline(PlayerSCtrlApplyElem, 0x2D4F, stx::hooking::proc::inhook_proc);
        PLOGD << "Hooked PlayerSCtrlApplyElem+0x2D4F";
        mebius::hook::HookOnTail(stx::mugen::PlayerSCtrlApplyElem, stx::hooking::proc::procmodstate);
        PLOGD << "Hooked PlayerSCtrlApplyElem";
        mebius::hook::HookOnTail(stx::mugen::SCtrlRCElemFree, stx::hooking::free::freemodstate);
        PLOGD << "Hooked SCtrlRCElemFree";

        // Type = SetRoundTimer
        // time(•K{) =  v(int/•K{)

        Controller::create(set_round_timer, "setroundtimer", {
                    (new Parameter_Required("value", {
                        new Argument_Required<int>("time")
                    })),
            });

        mebius::loader::Plugins::create("mods/StateControllerExtension", "stx");
        break;
    }
    case DLL_THREAD_ATTACH: {
        break;
    }
    case DLL_THREAD_DETACH: {
        break;
    }
    case DLL_PROCESS_DETACH: {
        break;
    }
    }
    return TRUE;
}
