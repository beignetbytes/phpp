#pragma once
#ifndef extlib2_hpp
#define extlib2_hpp

#include "../interfaces.hpp"
#include <phpp/phpp_interface.hpp>
#include <string>

namespace extlib2 {

	class plugin_3 : public interfaces::iplugin_3<std::string> {
	  public:
		plugin_3() = default;
		~plugin_3() override = default;
		std::string just_returning_a_value(std::string v) override;
	};

	class withstate : public interfaces::iplugin_3<int> {
		int placeholder;

	  public:
		withstate() = default;
		~withstate() override = default;
		int just_returning_a_value(int v) override;
	};

}; // namespace extlib2

#endif