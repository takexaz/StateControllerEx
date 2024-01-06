#pragma once
#include <argument.hpp>
#include <vector>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state;

namespace stx::state {

	class Parameter_impl {
	protected:
		std::string _name;
		bool _require;
		std::vector<Argument_impl*> _args;
		std::vector<Argument_impl*> _args_req;
		std::string _error_illegal_args = "Illegal ${param_name} parameter for ${state_name}";
	public:
		virtual ~Parameter_impl() {}
		void set_illegal_argument_error(std::string error_illegal_args) {
			this->_error_illegal_args = error_illegal_args;
			return;
		};
		std::string get_name(void) {
			return this->_name;
		}
		bool get_require(void) {
			return this->_require;
		}
		std::vector<Argument_impl*> get_args(void) {
			return this->_args;
		}
		std::vector<Argument_impl*> get_args_req(void) {
			return this->_args_req;
		}
		std::string get_illegal_error(void) {
			return this->_error_illegal_args;
		}
	};

	class STCEXAPI Parameter : public Parameter_impl {
	public:
		Parameter(std::string name, std::vector<Argument_impl*> args) {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			this->_name = name;
			this->_require = false;
			for (Argument_impl* arg : args) {
				if (!arg->get_require()) {
					this->_args.push_back(arg);
				}
				else {
					this->_args_req.push_back(arg);
				}
			}
		}
	};

	class STCEXAPI Parameter_Require : public Parameter_impl {
	private:
		std::string _error_missing_parameter = "Missing ${param_name} parameter for ${state_name}";
	public:
		Parameter_Require(std::string name, std::vector<Argument_impl*> args, std::string error_missing_parameter = "") {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			this->_name = name;
			this->_require = true;
			if (error_missing_parameter != "") this->_error_missing_parameter = error_missing_parameter;
			for (Argument_impl* arg : args) {
				if (!arg->get_require()) {
					this->_args.push_back(arg);
				}
				else {
					this->_args_req.push_back(arg);
				}
			}
		}
		std::string get_missing_error(void) {
			return this->_error_missing_parameter;
		}
	};
}