#pragma once

#include <special_type.hpp>
#include <parameter.hpp>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state;
using namespace stx::state::parameter;

namespace stx::state::controller {
	class STCEXAPI Controller {
	private:
		static std::unordered_map<std::string, Controller*> ctrls;
		proc_t _proc;
		std::string _name;
		std::unordered_map<std::string, Parameter*> _params_opt;
		std::unordered_map<std::string, Parameter*> _params_req;

		Controller(proc_t func, std::string name, std::vector<Parameter*> params);
	public:
		static Controller* create(proc_t func, std::string name, std::vector<Parameter*> params);
		static Controller* get_ctrl(std::string name);
		std::string get_name(void);
		proc_t get_proc(void);
		std::unordered_map<std::string, Parameter*> get_params_opt(void);
		std::unordered_map<std::string, Parameter*> get_params_req(void);
	};
}

