
#include "extlib1.hpp"
#include <iostream>

#include <memory>
#include <phpp/phpp_interface.hpp>

namespace extlib1 {

	plugin1::plugin1(){

	};
	void plugin1::just_saying_hi() {
		std::cout << "Hi from extlib1"
				  << "\n";
	};

	double plug2::just_returning_a_value(double v) { return v; }

	DEFINE_PLUGIN(plugin1, test_plugin_1);

	DEFINE_PLUGIN(plug2, double_plugin_2);

}; // namespace extlib1
