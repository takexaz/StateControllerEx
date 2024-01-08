#include <Windows.h>
#include <Mebius.hpp>
#include <STX.hpp>

#include <_hooking.hpp>

using namespace stx::state::argument;
using namespace stx::state::parameter;
using namespace stx::state::controller;
using namespace stx::state::processor;

bool example_state(Processor* p) {
    return true;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        mebius::hook::HookOnTail(stx::mugen::SCtrlParseElemType, stx::hooking::regmodstate);

        // Type = Example
        // params_v(îCà”) =  x(int/ïKê{), y(float/ïKê{), z(number/îCà”)
        // params_s(ïKê{) =  b(quoted_string/îCà”), c(raw_string/îCà”)

        Controller::create(example_state, "example", {
                    (new Parameter_Required("params_v", {
                        new Argument_Optional<int>("x", 100),
                        new Argument_Optional<float>("y", 200.0f),
                        new Argument_Optional<number>("z", 300),
                        new Argument_Optional<number>("z", 400.0f),
                    }))->set_illegal_argument_error("illegal"),
                    (new Parameter_Required("params_s", {
                        new Argument_Optional<RawString>("b", "500"),
                        new Argument_Optional<QuotedString>("a", "600"),
                    }))
                    ->set_illegal_argument_error("illegal")
                    ->set_missing_error("missing")

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
