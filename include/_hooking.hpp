#pragma once
#include <mugen.hpp>
#include <iostream>

using namespace stx::mugen;
namespace stx::hooking {
	BOOL regmodstate(int32_t original_result, TPFILE* tpf, SCX_DATA_EX* sinfo, PLAYER_INFO* playerInfo);

	static std::string replace(std::string error, std::string state, std::string param) {
		std::string var = "${state_name}";
		size_t pos = error.find(var);
		while (pos != std::string::npos) {
			error.replace(pos, var.length(), state);
			pos = error.find(var, pos + state.length());
		}
		var = "${param_name}";
		pos = error.find(var);
		while (pos != std::string::npos) {
			error.replace(pos, var.length(), param);
			pos = error.find(var, pos + param.length());
		}

		return error;
	}
}