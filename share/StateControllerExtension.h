#pragma once
#include <Windows.h>
#include <filesystem>
using namespace std;

struct Date {
    int Month;
    int Year;
    int Day;
};

struct COORD3D {
    float x;
    float y;
    float z;
};

struct TRIGGER_CONTROL {
    DWORD unkown1;
    int numBytes;//トリガーは何Byte区切りか
    int count01;//トリガー総数
    int count02;
    int count03;
    void* info;
    void* list;
};

struct STATE_INFO {
    TRIGGER_CONTROL* trg;
    int trgX;//triggerX最大
    int persistent;
    int ignoregitpause;
    int stateid;
    int substateid;
    void* params;
    void* type;
};

struct PLAYER_CACHE {
    char name[48];
    char displayname[48];
    char author[48];
    Date Version;
    Date MugenVersion;
};

struct TPFILE {
    void* unknown;
};

struct PLAYER {
    PLAYER_CACHE* pcache;
    int pID;
    int slot;
    int teamside;
    int undef01;//Player:0 Helper-1
    int undef02, undef03;
    int ishelper;
    char debugname[48];
    int consts[66];
    int exist;
    int flozen;
    int life, lifemax, life_disp, life_damage_disp;
    int* powerptr, powermaxptr;
    int power, powermax, power_disp, power_gauge;
    float attackmul, defencemul;
    int facing;
    int undef04;
    int invisible;
    COORD3D pos;
    COORD3D screenpos;
    COORD3D vel;
    COORD3D offset;
    int airjump_num;
    int undef05, undef06;
    int pausemovetime, supermovetime;
    int undef07, undef08, undef09;
};

struct EVAL_EXP {
    void* ptr1 = 0;
    void* ptr2 = 0;
    int value = 0;
};

struct STX {
    string type = "";
    int (*reg)(TPFILE*, STATE_INFO*, PLAYER_CACHE*) = NULL;
    void (*proc)(PLAYER*, STATE_INFO*) = NULL;
    void (*free)(STATE_INFO*) = NULL;
};

static auto TPGetValue = reinterpret_cast<const char* (*)(TPFILE* tpf, const char* label)>(0x483b30);
static auto SCtrlReadExpList = reinterpret_cast<int (*)(const char* value, const char* format, PLAYER_CACHE* pcache, DWORD* TEMP, ...)>(0x47d780);
static auto ParsePosType = reinterpret_cast<int (*)(const char* postype)>(0x47db40);
static auto FreeExpression = reinterpret_cast<void (*)(EVAL_EXP* ptr)>(0x406e00);
static auto Warn = reinterpret_cast<void (*)(PLAYER* p, const char *str)>(0x4155f0);
static auto VWarn = reinterpret_cast<void (*)(PLAYER * p, const char* format, ...)>(0x415630);

#ifdef STCEX_EXPORT
#define CLASS_DECLSPECEC extern "C" __declspec(dllexport)
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPECEC extern "C" __declspec(dllimport)
#define CLASS_DECLSPEC __declspec(dllimport)
#endif

CLASS_DECLSPECEC void addState(STX stx);
CLASS_DECLSPECEC void setErrorText(const char* error);
CLASS_DECLSPECEC int GetQuotedString(TPFILE* tpf, const char* label, const char* dest, size_t size); // if ERROR return 0
CLASS_DECLSPECEC int clamp(int value, int minimum, int maximum);
CLASS_DECLSPEC void constExp(EVAL_EXP* ptr, int value);
CLASS_DECLSPEC void constExp(EVAL_EXP* ptr, float value);
CLASS_DECLSPEC int EvalExpression(PLAYER* p, EVAL_EXP* ptr, int warnNo);
CLASS_DECLSPEC float EvalExpression(PLAYER* p, EVAL_EXP* ptr);