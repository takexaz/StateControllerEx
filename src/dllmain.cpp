#include <Windows.h>
#include <Mebius.hpp>
#include <STX.hpp>

#include <_hooking.hpp>
#include <_mugen.hpp>
using namespace stx::state;


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        mebius::hook::HookOnTail(stx::mugen::SCtrlParseElemType, stx::hooking::regmodstate);



        // Type = Example
        // params_v(îCà”) =  x(int/ïKê{), y(float/ïKê{), z(number/îCà”)
        // params_s(ïKê{) =  b(quoted_string/îCà”), c(raw_string/îCà”)

        Controller::create(nullptr, "example", {
                    new Parameter("params_v", {
                        new Argument_Require<int>("x"),
                        new Argument_Require<float>("y"),
                        new Argument<number>("z", 0),
                    }),
                    new Parameter_Require("params_s", {
                        new Argument<quoted_str>("a", "quoted"),
                        new Argument<raw_str>("b", "raw"),
                    },
                    "Missing ${param_name} parameter for ${state_name}"),
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
