
#include "extlib2.hpp"
#include <iostream>

namespace extlib2 {

	std::string plugin_3::just_returning_a_value(std::string v) { return "wilbur says:" + v; };

	int withstate::just_returning_a_value(int v) {
		placeholder = placeholder + v;
		return placeholder;
	};

	DEFINE_PLUGIN(plugin_3, wilbur);
	DEFINE_PLUGIN(withstate, counter);
}; // namespace extlib2
