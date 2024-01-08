#include <controller.hpp>
#include <algorithm>

namespace stx::state::controller {
	std::unordered_map<std::string, Controller*> Controller::ctrls;

	Controller::Controller(proc_t func, std::string name, std::vector<Parameter*> params) {
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		this->_name = name;
		this->_proc = func;
		for (auto param : params) {
			auto name = param->get_name();
			if (param->is_required()) {
				if (!_params_opt.count(name)) {
					_params_req[name] = param;
				}
				else {
					//stx::error::ShowErrorDialog("Error in Controller: Parameters are the same name.");
				}
			}
			else {
				if (!_params_req.count(name)) {
					_params_opt[name] = param;
				}
				else {
					//stx::error::ShowErrorDialog("Error in Controller: Parameters are the same name.");
				}
			}
		}
	}

	Controller* Controller::create(proc_t func, std::string name, std::vector<Parameter*> params) {
		Controller* ctrl = new Controller(func, name, params);
		ctrls[name] = ctrl;
		return ctrl;
	}

	Controller* Controller::get_ctrl(std::string name) {
		if (ctrls.count(name)) {
			return ctrls[name];
		}
		return nullptr;
	}

	proc_t Controller::get_proc(void) {
		return this->_proc;
	}
	std::string Controller::get_name(void) {
		return this->_name;
	}
	std::unordered_map<std::string, Parameter*> Controller::get_params_opt(void) {
		return this->_params_opt;
	}
	std::unordered_map<std::string, Parameter*> Controller::get_params_req(void) {
		return this->_params_req;
	}
}