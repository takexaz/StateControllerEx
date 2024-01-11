#include <processor.hpp>

namespace stx::state::processor {
	Processor::Processor(params_t* ps, proc_t proc) : _ps(ps), _proc(proc), _player(nullptr) {}

	Processor::~Processor()
	{
		delete _ps;
	}

	void Processor::set_player(PLAYER* player) {
		this->_player = player;
	}

	void Processor::warn(std::string str) {
		stx::mugen::Warn(_player, str.c_str());
	}

	proc_t Processor::get_proc(void)
	{
		return this->_proc;
	}

	param_t* Processor::get_parameter(std::string name) {
		if (this->_ps->count(name)) {
			return _ps->at(name);
		}
		else {
			return nullptr;
		}
	}
	arg_t* Processor::get_argument(param_t* p, std::string name) {
		if (p == nullptr) {
			return nullptr;
		}
		if (p->first->count(name)) {
			return p->first->at(name);
		}
		else if (p->second->count(name)) {
			return p->second->at(name);
		}
		else {
			// error
			return nullptr;
		}
	}

}