
#include "phpp_examples.hpp"
#include "utilities.hpp"

#include <chrono>
#include <iostream>
#include <numeric>
#include <string>

#include <phpp/phpp.hpp>

#include "interfaces.hpp"

void phpp_tests::test_lib() {

#ifdef WIN32
	std::string path = "";
	std::string lib1name = "extlib1";
	std::string lib2name = "extlib2";

#else
	std::string path = "./";
	std::string lib1name = "libextlib1";
	std::string lib2name = "libextlib2";
#endif
	auto ph = phpp::plugin_handler(path);
	auto pl1 = ph.get_plugin<interfaces::iplugin1>(lib1name, "test_plugin_1");
	pl1->just_saying_hi();
	auto pl2 = ph.get_plugin<interfaces::iplugin_2<double>>(lib1name, "double_plugin_2");
	auto v = pl2->just_returning_a_value(2.0);
	phpp_examples_utilities::helper::WRITE_MSG(std::to_string(v));
	auto pl3 = ph.get_plugin<interfaces::iplugin_3<std::string>>(lib2name, "wilbur");
	phpp_examples_utilities::helper::WRITE_MSG(pl3->just_returning_a_value("oink"));

	auto pl4 = ph.get_plugin<interfaces::iplugin_3<int>>(lib2name, "counter");
	auto zz = pl4->just_returning_a_value(3);
	phpp_examples_utilities::helper::WRITE_MSG(std::to_string(zz));
	auto zz2 = pl4->just_returning_a_value(5);
	phpp_examples_utilities::helper::WRITE_MSG(std::to_string(zz2));
	auto pl5 = ph.get_plugin<interfaces::iplugin_3<int>>(lib2name, "counter");
	auto zz3 = pl5->just_returning_a_value(3);
	phpp_examples_utilities::helper::WRITE_MSG(std::to_string(zz3));
	phpp_examples_utilities::helper::WRITE_MSG(std::to_string(pl4->just_returning_a_value(0)));
};

int main() {
	try {
		phpp_tests::test_lib();
		std::cout << "done"
				  << "\n";
		return 0;
	} catch (const std::exception &ex) {
		phpp_examples_utilities::helper::WRITE_MSG(ex.what());
		return 1;
	}
}
