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
		void set_player(PLAYER* player);

		void warn(std::string str);

		proc_t get_proc(void);

		template<typename T> T* get_value(std::string param_name, std::string arg_name);

		template<> number* get_value(std::string param_name, std::string arg_name) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return nullptr;

			int i;
			float f;
			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			number v;
			switch (EvalExpression(_player, &e, &i, &f))
			{
			case N_INT:
			{
				v = i;
				break;
			}
			case N_FLOAT:
			{
				v = f;
				break;
			}
			default:
			{
				// error
				break;
			}
			}
			return &v;
		}

		template<> int* get_value(std::string param_name, std::string arg_name) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return nullptr;

			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			int v = EvalExpressionI(_player, &e, FALSE);
			return &v;
		}

		template<> float* get_value(std::string param_name, std::string arg_name) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return nullptr;

			EVAL_VALUE e = std::get<EVAL_VALUE>(value->second);
			float v = EvalExpressionF(_player, &e);
			return &v;
		}

		template<> std::string* get_value(std::string param_name, std::string arg_name) {
			auto value = get_argument(get_parameter(param_name), arg_name);
			if (value == nullptr) return nullptr;

			std::string v = std::get<std::string>(value->second);
			return &v;
		}
	};
}