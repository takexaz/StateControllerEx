#include <_mugen.hpp>
#include <_hooking.hpp>
#include <regex>
using namespace stx::state;
using namespace stx::mugen;

BOOL stx::hooking::regmodstate(int32_t original_result, TPFILE* tpf, SCX_DATA_EX* sinfo, PLAYER_INFO* playerInfo) {
	if (original_result == TRUE) return original_result;

	const char* mugen_error = (const char*)*((DWORD*)0x4b5b4c) + 0xC534;
	std::regex pattern("Not a valid elem type: (.*)");
	std::cmatch match;

    if (!std::regex_search(mugen_error, match, pattern)) {
		return original_result;
    }

	if (match.size() <= 1) {
		return original_result;
	}

}