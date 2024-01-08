#pragma once
#include <stdio.h>
#include <stdint.h>
#include <wtypes.h>

namespace stx::state::processor {
    class Processor;
}

namespace stx::mugen {
	using undefined = BYTE;
	using undefined4 = DWORD;

	enum PARAM_TYPE {
		INTEGER = 0,
		FLOATING_POINT = 1,
		OPERATOR = 2,
		TRIGGER = 3,
		UNDEFINED = 4,
		NUMBER = 5,
		QUOTED_STRING = 6,
		RAW_STRING = 7,
	};
	struct EVAL_VALUE {
		void* exprs = nullptr;
		int* types = nullptr;
		uint32_t value = NULL;
	};

    struct TPFILE {
        void* unknown;
    };
    struct VERSION_DATA {
        int32_t month;
        int32_t day;
        int32_t year;
    };

    struct PLAYER_CONSTRAINTS {
        int32_t data_life;
        int32_t data_power;
        int32_t data_attack;
        int32_t size_attack_z_width_front;
        int32_t size_attack_z_width_back;
        int32_t data_airJuggle;
        int32_t size_attack_dist;
        int32_t size_proj_attack_dist;
        int32_t data_defence;
        float data_fall_defence_mul;
        int32_t data_lieDown_time;
        float size_XScale;
        float size_YScale;
        int32_t size_ground_back;
        int32_t size_ground_front;
        int32_t size_air_back;
        int32_t size_air_front;
        int32_t size_z_width;
        int32_t size_height;
        uint32_t size_proj_doScale;
        int32_t size_head_pos_x;
        int32_t size_head_pos_y;
        int32_t size_mid_pos_x;
        int32_t size_mid_pos_y;
        int32_t size_shadowOffset;
        float velocity_walk_fwd_x;
        float velocity_walk_back_x;
        float velocity_walk_up_x;
        float velocity_walk_down_x;
        float velocity_run_fwd_x;
        float velocity_run_fwd_y;
        float velocity_run_back_x;
        float velocity_run_back_y;
        float velocity_run_down_x;
        float velocity_run_down_y;
        float velocity_run_up_x;
        float velocity_run_up_y;
        float velocity_jump_y;
        float velocity_jump_new_x;
        float velocity_jump_fwd_x;
        float velocity_jump_back_x;
        float velocity_jump_up_x;
        float velocity_jump_down_x;
        float velocity_runJump_y;
        float velocity_runJump_fwd_x;
        float velocity_runJump_back_x;
        float velocity_runJump_up_x;
        float velocity_runJump_down_x;
        int32_t movement_airJump_num;
        int32_t movement_airJump_height;
        float velocity_airJump_y;
        float velocity_airJump_new_x;
        float velocity_airJump_fwd_x;
        float velocity_airJump_back_x;
        float velocity_airJump_up_x;
        float velocity_airJump_down_x;
        float movement_YAccel;
        float movement_stand_friction;
        float movement_crouch_friction;
        int32_t data_sparkNo;
        int32_t data_guard_sparkNo;
        uint32_t data_KO_echo;
        int32_t size_draw_offset_x;
        int32_t size_draw_offset_y;
        int32_t data_intPersistIndex;
        int32_t data_floatPersistIndex;
    };

    struct PLAYER_INFO {
        char name[48];
        char displayName[48];
        char authorName[48];
        VERSION_DATA versionDate;
        VERSION_DATA mugenVersion;
        undefined _unknown_1[512];
        int32_t charsIdx;
        PLAYER_CONSTRAINTS consts;
        void* command;
        undefined4 _unknown_2;
        int32_t commandCnt;
        int32_t uniqueCommandCnt;
        void** stateList;
        void* sff;
        void* anim;
        int32_t volume;
        void** snd;
        char ai_filepath[512];
        void* _unknown_3;
        void* _unknown_4;
        undefined4 _unknown_5[64];
    };

    struct PLAYER {
        PLAYER_INFO* info;
    };

    struct SCX_DATA_EX {
        void* triggers;
        uint32_t triggerCnt;
        int32_t persistent;
        int32_t ignorehitpause;
        int scID;
        stx::state::processor::Processor* proc;
    };

    static void SetParseErrorText(const char* error) {
        char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
        snprintf(mugen_error, 1023, "%s", error);
        return;
    }

    static auto TPGetValue = reinterpret_cast<char* (*)(TPFILE * tpf, const char* label)>(0x483b30);
    static auto SCtrlReadExpList = reinterpret_cast<int (*)(char* value, const char* format, PLAYER_INFO * playerInfo, char** parseEnd, ...)>(0x47d780);
    static auto ConstExpI = reinterpret_cast<void (*)(EVAL_VALUE * eval, int value)>(0x406f20);
    static auto ConstExpF = reinterpret_cast<void (*)(EVAL_VALUE * eval, float value)>(0x406fa0);
    static auto EvalExpression = reinterpret_cast<PARAM_TYPE(*)(PLAYER * player, EVAL_VALUE * eval, int* pInt, float* pFloat)>(0x407780);
    static auto EvalExpressionI = reinterpret_cast<int(*)(PLAYER * player, EVAL_VALUE * eval, int warnNo)>(0x4075e0);
    static auto EvalExpressionF = reinterpret_cast<float(*)(PLAYER * player, EVAL_VALUE * eval)>(0x4076d0);

    static auto FreeExpression = reinterpret_cast<void (*)(EVAL_VALUE * eval)>(0x406e00);

    static auto SCtrlParseElemType = reinterpret_cast<BOOL(*)(TPFILE * tpf, SCX_DATA_EX * sinfo, PLAYER_INFO * playerInfo)>(0x46aa60);
}
