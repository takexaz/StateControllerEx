#pragma once

#include <argument.hpp>

#ifdef STCEX_EXPORT
#define STCEXAPI __declspec(dllexport)
#else
#define STCEXAPI __declspec(dllimport)
#endif

using namespace stx::state::argument;

namespace stx::state::parameter {
	class STCEXAPI Parameter {
	protected:
		std::string _name;
		bool _required;
		std::vector<std::pair<std::string, Argument*>> _args_opt;
		std::vector<std::pair<std::string, Argument*>> _args_req;
		std::string _error_illegal_args = "Illegal ${param_name} parameter for ${state_name}";
		std::string _error_missing_parameter = "Missing ${param_name} parameter for ${state_name}";
	public:
		virtual ~Parameter() {}
		Parameter(std::string name, std::vector<Argument*> args);
		std::string get_name(void);
		bool is_required(void);
		std::vector<std::pair<std::string, Argument*>> get_args_opt(void);
		std::vector<std::pair<std::string, Argument*>> get_args_req(void);
		std::string get_illegal_error(void);
		std::string get_missing_error(void);
		Parameter* set_illegal_argument_error(std::string error_illegal_args);
		Parameter* set_missing_error(std::string error_missing_parameter);
	};

	class STCEXAPI Parameter_Optional : public Parameter {
	public:
		Parameter_Optional(std::string name, std::vector<Argument*> args) : Parameter{ std::move(name), std::move(args) } {
			this->_required = false;
		}
	};

	class STCEXAPI Parameter_Required : public Parameter {
	public:
		Parameter_Required(std::string name, std::vector<Argument*> args) : Parameter{ std::move(name), std::move(args) } {
			this->_required = true;
		}
	};
}