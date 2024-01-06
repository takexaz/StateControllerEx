#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <variant>

namespace stx::state {
	enum PARAM_TYPE {
		NUMBER,
		INTEGER,
		FLOATING_POINT,
		QUOTED_STRING,
		RAW_STRING
	};
	struct EVAL_VALUE {
		void* exprs = nullptr;
		int* types = nullptr;
		uint32_t value;
	};

	using eval = std::variant<std::string, EVAL_VALUE>;
	using number = std::variant<int, float>;

	struct raw_str {
		std::string str;
		raw_str(const char* str) : str(str) {}
	};
	struct quoted_str {
		std::string str;
		quoted_str(const char* str) : str(str) {}
	};

	template <typename T>
	concept exp_t = std::same_as<T, number> || std::same_as<T, int> || std::same_as <T, float> || std::same_as<T, raw_str> || std::same_as<T, quoted_str>;
}