#pragma once
#include <Windows.h>
#include <filesystem>
#include <Winmugen.h>
using namespace std;


struct STX {
    string scName = "";
    int (*reg)(TPFILE* tpf, MUGEN_SC_DATA_EX* scdx, MUGEN_PLAYER_INFO* pinfp) = NULL;
    void (*proc)(MUGEN_PLAYER* player, MUGEN_SC_DATA_EX* scdx) = NULL;
    void (*free)(MUGEN_SC_DATA_EX* scdx) = NULL;
};

#ifdef STCEX_EXPORT
#define CLASS_DECLSPECEC extern "C" __declspec(dllexport)
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPECEC extern "C" __declspec(dllimport)
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

CLASS_DECLSPECEC void addState(STX stx);
CLASS_DECLSPECEC void setErrorText(const char* error);
CLASS_DECLSPECEC int clamp(int value, int minimum, int maximum);

CLASS_DECLSPEC void constExpN(MUGEN_EVAL_VALUE* eval, int value);
CLASS_DECLSPEC void constExpN(MUGEN_EVAL_VALUE* eval, float value);
CLASS_DECLSPEC int EvalExpressionN(MUGEN_PLAYER* player, MUGEN_EVAL_VALUE* eval, int warnNo);
CLASS_DECLSPEC float EvalExpressionN(MUGEN_PLAYER* player, MUGEN_EVAL_VALUE* eval);
CLASS_DECLSPEC MUGEN_EVAL_TYPE EvalExpressionN(MUGEN_PLAYER* player, MUGEN_EVAL_VALUE* eval, int* pInt, float* pFloat);

CLASS_DECLSPECEC int GetQuotedStringEx(TPFILE* tpf, const char* label, const char* dest, size_t size); // if ERROR return 0