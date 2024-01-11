#pragma once
#include <Mebius.hpp>
#include <special_type.hpp>
#include <mugen.hpp>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state;
using namespace stx::mugen;

namespace stx::state::argument {
	class Argument {
	protected:
		std::string _name;
		PARAM_TYPE _type;
		bool _required;
	public:
		virtual ~Argument() {}
		Argument(std::string name, bool required);
		std::string get_name(void);
		bool is_required(void);
		PARAM_TYPE get_type(void);
	};

	template <exp_t T>
	class STCEXAPI Argument_Optional : public Argument {
	private:
		std::variant<int, float, std::string> _value;
	public:
		Argument_Optional(std::string name, T value) : Argument{ std::move(name), false } {
			PLOGD << "Argopt";
			bool _required = false;
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
			else if constexpr (std::is_same_v<T, QuotedString>) {
				this->_type = QUOTED_STRING;
				_value = value.str;
			}
			else {
				this->_type = RAW_STRING;
				_value = value.str;
			}
		}
		std::variant<int, float, std::string> get_value(void) {
			return this->_value;
		}
	};

	template <exp_t T>
	class STCEXAPI Argument_Required : public Argument {
	public:
		Argument_Required(std::string name) : Argument{ std::move(name), true } {
			bool _required = true;
			if constexpr (std::is_same_v<T, number>) {
				this->_type = NUMBER;
			}
			else if constexpr (std::is_same_v<T, int>) {
				this->_type = INTEGER;
			}
			else if constexpr (std::is_same_v<T, float>) {
				this->_type = FLOATING_POINT;
			}
			else if constexpr (std::is_same_v<T, QuotedString>) {
				this->_type = QUOTED_STRING;
			}
			else {
				this->_type = RAW_STRING;
			}

		}
	};
}