#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <numeric>
#include <string>

#include <phpp/phpp.hpp>

#include "../examples/interfaces.hpp"

TEST(PhppTests1, PluginLoadTests) {

	std::string path = "./";
	std::string lib1name = "libtestextlib1";
	std::string lib2name = "libtestextlib2";

	auto ph = phpp::plugin_handler(path);
	auto pl2 = ph.get_plugin<interfaces::iplugin_2<double>>(lib1name, "double_plugin_2");
	auto v = pl2->just_returning_a_value(2.0);
	EXPECT_DOUBLE_EQ(v, 2.0);
	auto pl3 = ph.get_plugin<interfaces::iplugin_3<std::string>>(lib2name, "wilbur");
	EXPECT_EQ("wilbur says:oink", pl3->just_returning_a_value("oink"));

	auto pl4 = ph.get_plugin<interfaces::iplugin_3<int>>(lib2name, "counter");
	auto zz = pl4->just_returning_a_value(3);
	EXPECT_EQ(zz, 3);

	auto zz2 = pl4->just_returning_a_value(5);
	EXPECT_EQ(zz2, 8);
	auto pl5 = ph.get_plugin<interfaces::iplugin_3<int>>(lib2name, "counter");
	auto zz3 = pl5->just_returning_a_value(3);
	EXPECT_EQ(zz3, 3);
	EXPECT_EQ(pl4->just_returning_a_value(0), 8);
};