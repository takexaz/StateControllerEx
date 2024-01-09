#include <Windows.h>
#include <Mebius.hpp>
#include <STX.hpp>

#include <_hooking.hpp>

using namespace stx::state::argument;
using namespace stx::state::parameter;
using namespace stx::state::controller;
using namespace stx::state::processor;

BOOL set_round_timer(Processor* p, stx::mugen::PLAYER* player, stx::mugen::PLAYER_REDIRECTS* redirects) {
    DWORD* roundtimer = (DWORD*)(*((DWORD*)0x4b5b4c) + 0xBC40);

    int* i = p->get_value<int>("value", "time");
    if (i != nullptr) {
        *roundtimer = *i;
    }

    return true;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        mebius::hook::HookOnTail(stx::mugen::SCtrlParseElemType, stx::hooking::reg::regmodstate);
        mebius::inline_hook::HookInline(0x47154f, stx::hooking::proc::inhook_proc);
        mebius::hook::HookOnTail(stx::mugen::PlayerSCtrlApplyElem, stx::hooking::proc::procmodstate);

        // Type = SetRoundTimer
        // time(ïKê{) =  v(int/ïKê{)

        Controller::create(set_round_timer, "setroundtimer", {
                    (new Parameter_Required("value", {
                        new Argument_Required<int>("time")
                    })),
            });
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
