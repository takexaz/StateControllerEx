#pragma once
#include <parameter.hpp>
#include <bit>
#include <algorithm>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

namespace stx::state {
	class Controller;
	using proc_t = bool(*)(Controller*);

	class STCEXAPI Controller {
	private:
		static std::vector<std::pair<proc_t, Controller*>> ctrls;
		std::string _name;
		std::vector<Parameter_impl*> _params;
		std::vector<Parameter_impl*> _params_req;

		Controller(std::string name, std::vector<Parameter_impl*> params) {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			this->_name = name;
			for (Parameter_impl* param : params) {
				if (!param->get_require()) {
					this->_params.push_back(param);
				}
				else {
					this->_params_req.push_back(param);
				}
			}
		}
	public:
		static Controller* create(proc_t func, std::string name, std::vector<Parameter_impl*> params) {
			Controller* ctrl = new Controller(name, params);
			ctrls.push_back({ func, ctrl });
			return ctrl;
		}
		std::string get_name(void) {
			return this->_name;
		}
		std::vector<Parameter_impl*> get_params(void) {
			return this->_params;
		}
		std::vector<Parameter_impl*> get_params_req(void) {
			return this->_params_req;
		}
	};
}

