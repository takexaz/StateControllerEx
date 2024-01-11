#pragma once
#include <special_type.hpp>
#include <mugen.hpp>
#include <variant>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state;
using namespace stx::mugen;

namespace stx::state::processor {
	class STCEXAPI Processor {
	private:
		params_t* _ps;
		PLAYER* _player;
		proc_t _proc;

		param_t* get_parameter(std::string name);
		arg_t* get_argument(param_t* p, std::string name);
	public:
		Processor(params_t* ps, proc_t proc);
		~Processor();
		void set_player(PLAYER* player);

		void warn(std::string str);

		proc_t get_proc(void);

		template<typename T> bool get_value(std::string param_name, std::string arg_name, T* value);

		template<> bool get_value(std::string param_name, std::string arg_name, number* v) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return false;

			int i;
			float f;
			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			switch (EvalExpression(_player, &e, &i, &f))
			{
			case N_INT:
			{
				*v = i;
				break;
			}
			case N_FLOAT:
			{
				*v = f;
				break;
			}
			default:
			{
				// error
				break;
			}
			}
			return true;
		}

		template<> bool get_value(std::string param_name, std::string arg_name, int* v) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return false;

			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			*v = EvalExpressionI(_player, &e, FALSE);
			return true;
		}

		template<> bool get_value(std::string param_name, std::string arg_name, float* v) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return false;

			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			*v = EvalExpressionF(_player, &e);
			return true;
		}

		template<> bool get_value(std::string param_name, std::string arg_name, std::string* v) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return false;

			*v = std::get<std::string>(value->second);
			return true;
		}
	};
}