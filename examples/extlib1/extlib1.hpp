#pragma once
#ifndef extlib1_hpp
#define extlib1_hpp

#include "../interfaces.hpp"

namespace extlib1 {

	class plugin1 : public interfaces::iplugin1 {
	  public:
		plugin1();
		~plugin1() override = default;
		void just_saying_hi() override;
	};

	class plug2 : public interfaces::iplugin_2<double> {
	  public:
		plug2() = default;
		~plug2() override = default;
		double just_returning_a_value(double v) override;
	};

}; // namespace extlib1

#endif