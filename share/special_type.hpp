#pragma once
#include <mugen.hpp>
#include <iostream>
#include <variant>
#include <unordered_map>

namespace stx::mugen {
	enum PARAM_TYPE;
	struct EVAL_VALUE;
}

namespace stx::state::processor {
	class Processor;
}

namespace stx::state {
	using eval = std::variant<std::string, stx::mugen::EVAL_VALUE>;
	using number = std::variant<int, float>;

	using arg_t = std::pair<stx::mugen::PARAM_TYPE, eval>;
	using args_t = std::unordered_map <std::string, arg_t*>;
	using param_t = std::pair<args_t*, args_t*>;
	using params_t = std::unordered_map <std::string, param_t*>;
	using proc_t = BOOL(*)(stx::state::processor::Processor*, stx::mugen::PLAYER* player, stx::mugen::PLAYER_REDIRECTS* redirects);

	struct RawString {
		std::string str;
		RawString(const char* str) : str(str) {}
	};
	struct QuotedString {
		std::string str;
		QuotedString(const char* str) : str(str) {}
	};

	template <typename T>
	concept exp_t = std::same_as<T, number> || std::same_as<T, int> || std::same_as <T, float> || std::same_as<T, RawString> || std::same_as<T, QuotedString>;
}