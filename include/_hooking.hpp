#pragma once
#include <STX.hpp>
#include <Mebius.hpp>
#include <mugen.hpp>
#include <regex>
#include <iostream>

using namespace stx::mugen;
namespace stx::hooking::proc {
	void inhook_proc(mebius::inline_hook::PMBCONTEXT context);
	BOOL procmodstate(int32_t original_result, PLAYER* player, SC_DATA_EX* sinfo, PLAYER_REDIRECTS* redirects);
}
namespace stx::hooking::reg {
	BOOL regmodstate(int32_t original_result, TPFILE* tpf, SC_DATA_EX* sinfo, PLAYER_INFO* playerInfo);
}
namespace stx::hooking::free {
	void freemodstate(SC_DATA_EX* sinfo);
}