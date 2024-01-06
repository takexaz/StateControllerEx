#pragma once
#include <special_type.hpp>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state;

namespace stx::state {

	class Argument_impl {
	protected:
		std::string _name;
		bool _require;
		PARAM_TYPE _type;
		eval _eval = {};
		std::variant<int, float, std::string> _value = nullptr;
	public:
		virtual ~Argument_impl() {}
		std::string get_name(void) {
			return this->_name;
		}
		bool get_require(void) {
			return this->_require;
		}
		PARAM_TYPE get_type(void) {
			return this->_type;
		}
		eval get_eval(void) {
			return this->_eval;
		}
		std::variant<int, float, std::string> get_value(void) {
			return this->_value;
		}
	};

	template <exp_t T>
	class STCEXAPI Argument : public Argument_impl {
	public:
		Argument(std::string name, T value) {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			this->_name = name;
			this->_require = false;
			if constexpr (std::is_same_v<T, number>) {
				this->_type = NUMBER;
				if (std::holds_alternative<int>(value)) {
					_value = std::get<int>(value);
				}
				else {
					_value = std::get<float>(value);
				}
			}
			else if constexpr (std::is_same_v<T, int>) {
				this->_type = INTEGER;
				_value = value;
			}
			else if constexpr (std::is_same_v<T, float>) {
				this->_type = FLOATING_POINT;
				_value = value;
			}
			else if constexpr (std::is_same_v<T, quoted_str>) {
				this->_type = QUOTED_STRING;
				_value = value.str;
			}
			else {
				this->_type = RAW_STRING;
				_value = value.str;
			}
		}
	};

	template <exp_t T>
	class STCEXAPI Argument_Require : public Argument_impl {
	public:
		Argument_Require(std::string name) {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			this->_name = name;
			this->_require = true;
			if constexpr (std::is_same_v<T, number>) {
				this->_type = NUMBER;
			}
			else if constexpr (std::is_same_v<T, int>) {
				this->_type = INTEGER;
			}
			else if constexpr (std::is_same_v<T, float>) {
				this->_type = FLOATING_POINT;
			}
			else if constexpr (std::is_same_v<T, quoted_str>) {
				this->_type = QUOTED_STRING;
			}
			else {
				this->_type = RAW_STRING;
			}
		}
	};
}