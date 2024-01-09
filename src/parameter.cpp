#include <parameter.hpp>
#include <algorithm>

namespace stx::state::parameter {
	Parameter::Parameter(std::string name, std::vector<Argument*> args) {
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		this->_name = name;
		for (auto arg : args) {
			auto name = arg->get_name();
			if (arg->is_required()) {
				for (auto& pair : _args_opt) {
					if (pair.first == name) {
						//stx::error::ShowErrorDialog("Error in Controller: Parameters are the same name.");
						return;
					}
				}
				for (auto& pair : _args_req) {
					if (pair.first == name) {
						pair.second = arg;
						return;
					}
				}
				_args_req.push_back(std::pair<std::string, Argument*>(name, arg));
			}
			else {
				for (auto& pair : _args_req) {
					if (pair.first == name) {
						//stx::error::ShowErrorDialog("Error in Controller: Parameters are the same name.");
						return;
					}
				}
				for (auto& pair : _args_opt) {
					if (pair.first == name) {
						pair.second = arg;
						return;
					}
				}
				_args_opt.push_back(std::pair<std::string, Argument*>(name, arg));
			}
		}
	}
	Parameter* Parameter::set_illegal_argument_error(std::string error_illegal_args) {
		this->_error_illegal_args = error_illegal_args;
		return this;
	};
	std::string Parameter::get_illegal_error(void) {
		return this->_error_illegal_args;
	}
	Parameter* Parameter::set_missing_error(std::string error_missing_parameter) {
		this->_error_missing_parameter = error_missing_parameter;
		return this;
	}
	std::string Parameter::get_missing_error(void) {
		return this->_error_missing_parameter;
	}
	std::string Parameter::get_name(void) {
		return this->_name;
	}
	bool Parameter::is_required(void) {
		return this->_required;
	}
	std::vector<std::pair<std::string, Argument*>> Parameter::get_args_opt(void) {
		return this->_args_opt;
	}
	std::vector<std::pair<std::string, Argument*>> Parameter::get_args_req(void) {
		return this->_args_req;
	}
}