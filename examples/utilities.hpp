#pragma once
#ifndef utilities_hpp
#define utilities_hpp

#include <iomanip>
#include <iostream>
#include <string>

namespace phpp_examples_utilities {
	class helper {
	  private:
	  public:
		static void PRINT_ERROR_MSG(const std::string &str) { WRITE_MSG("ERROR! |>" + str); };
		static void PRINT_TEST_MESSAGE(const std::string &str) { WRITE_MSG("MSG! |>" + str); };
		static void WRITE_MSG(const std::string &str) { std::cout << str << "\n"; };
		static void WRITE_ERR(const std::string &str) { std::cerr << str << "\n"; };
	};
}; // namespace phpp_examples_utilities

#endif