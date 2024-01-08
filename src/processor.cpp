#include <processor.hpp>

namespace stx::state::processor {
	Processor::Processor(params_t* ps, proc_t proc) : _ps(ps), _proc(proc), _player(nullptr) {}
	void Processor::set_player(PLAYER* player) {
		this->_player = player;
	}

	param_t* Processor::get_parameter(std::string name) {
		if (this->_ps->count(name)) {
			return _ps->at(name);
		}
		else {
			return nullptr;
		}
	}
	arg_t* Processor::get_argument_required(param_t* p, std::string name) {
		if (p == nullptr) {
			return nullptr;
		}

		args_t* a = p->first;
		if (a->count(name)) {
			return a->at(name);
		}
		else {
			return nullptr;
		}
	}
	arg_t* Processor::get_argument_optional(param_t* p, std::string name) {
		if (p == nullptr) {
			return nullptr;
		}

		args_t* a = p->second;
		if (a->count(name)) {
			return a->at(name);
		}
		else {
			return nullptr;
		}
	}
}