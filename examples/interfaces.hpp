#pragma once
#ifndef interfaces_hpp
#define interfaces_hpp

namespace interfaces {
	class iplugin1 {
	  public:
		virtual ~iplugin1() = default;
		virtual void just_saying_hi() = 0;
	};

	template <typename T>
	class iplugin_2 {
	  public:
		virtual ~iplugin_2() = default;
		virtual T just_returning_a_value(T v) = 0;
	};

	template <typename T>
	class iplugin_3 {
	  public:
		virtual T just_returning_a_value(T v) = 0;
		virtual ~iplugin_3() = default;
	};

} // namespace interfaces

#endif