#include "_StateControllerExtension.h"

void constExp(EVAL_EXP* ptr, int value) {
    ConstExpI(ptr, value);
    return;
}

void constExp(EVAL_EXP* ptr, float value) {
    ConstExpF(ptr, value);
    return;
}

int EvalExpression(PLAYER* p, EVAL_EXP* ptr, int warnNo) {
    return EvalExpressionI(p, ptr, warnNo);
}

float EvalExpression(PLAYER* p, EVAL_EXP* ptr) {
    return EvalExpressionF(p, ptr);
}

EVAL_TYPE EvalExpression(PLAYER* p, EVAL_EXP* ptr, int* pInt, float* pFloat) {
    return EvalExpressionN(p, ptr, pInt, pFloat);
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