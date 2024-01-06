#pragma once
#include <special_type.hpp>
#include <controller.hpp>
#include <iostream>
#include <wtypes.h>

using namespace stx::state;

namespace stx::mugen {

    using undefined = BYTE;
    using undefined4 = DWORD;

    struct TPFILE {
        void* unknown;
    };

    struct SCX_DATA_EX {
        void* triggers;
        uint32_t triggerCnt;
        int32_t persistent;
        int32_t ignorehitpause;
        int scID;
        stx::state::Controller* ctrl;
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

    static void SetParseErrorText(const char* error) {
        char* mugen_error = (char*)*((DWORD*)0x4b5b4c) + 0xC534;
        snprintf(mugen_error, 1023, "%s", error);
        return;
    }

    static int STATEID = 0x7FFFFFFF;
    static auto TPGetValue = reinterpret_cast<const char* (*)(TPFILE * tpf, const char* label)>(0x483b30);
    static auto SCtrlParseElemType = reinterpret_cast<BOOL(*)(TPFILE * tpf, SCX_DATA_EX * sinfo, PLAYER_INFO * playerInfo)>(0x46aa60);
}
