#pragma once
#include <_mugen.hpp>

using namespace stx::mugen;
namespace stx::hooking {
	BOOL regmodstate(int32_t original_result, TPFILE* tpf, SCX_DATA_EX* sinfo, PLAYER_INFO* playerInfo);
}