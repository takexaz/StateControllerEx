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
	public:
		Processor(params_t* ps, proc_t proc);
		void set_player(PLAYER* player);

		param_t* get_parameter(std::string name);
		arg_t* get_argument_required(param_t* p, std::string name);
		arg_t* get_argument_optional(param_t* p, std::string name);

		template<typename T>
		T get_value(arg_t* a) {
			switch (a->first)
			{
			case NUMBER:
			{
				int i = 0;
				float f = 0.0f;
				EVAL_VALUE e = std::get<EVAL_VALUE>(a->second);
				break;
			}
			case INTEGER:
			{

				break;
			}
			case FLOATING_POINT:
			{

				break;
			}
			case QUOTED_STRING:
			{

				break;
			}
			case RAW_STRING:
			{

				break;
			}
			default:
			{
				//ShowErrorDialog("Error in get_value: Unknown value type.");
				break;
			}
			}
		}
	};

	struct SCX_DATA_EX {
		void* triggers;
		uint32_t triggerCnt;
		int32_t persistent;
		int32_t ignorehitpause;
		int scID;
		Processor* proc;
	};

}