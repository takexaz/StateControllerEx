#include <argument.hpp>
#include <algorithm>

using namespace stx::state;
using namespace stx::mugen;

namespace stx::state::argument {
	Argument::Argument(std::string name, bool required) : _required(required), _type(UNDEFINED) {
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		this->_name = name;
	}
	std::string Argument::get_name(void) {
		return this->_name;
	}
	bool Argument::is_required(void) {
		return this->_required;
	}
	PARAM_TYPE Argument::get_type(void) {
		return this->_type;
	}
}