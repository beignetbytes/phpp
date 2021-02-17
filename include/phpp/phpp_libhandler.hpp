#pragma once
#ifndef phpp_libhandler_hpp
#define phpp_libhandler_hpp

#include <iostream>
#include <memory>
#include <string>

#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace phpp {

	class lib_handler {

	  private:
		std::string _lib_path;
#ifdef WIN32
		HMODULE _libhandle;
		std::string _lib_suffix = ".dll";
#else
		void *_libhandle;
		std::string _lib_suffix = ".so";
#endif
	  public:
		explicit lib_handler(const std::string& path_to_lib) noexcept : _libhandle(nullptr), _lib_path(path_to_lib) {}

		~lib_handler() = default;

		bool operator==(const lib_handler &other) const { return other._lib_path == _lib_path; };
		bool operator!=(const lib_handler &other) const { return !((*this) == other); };

		void open_lib() {
#ifdef WIN32
			if (!(_libhandle = LoadLibrary((_lib_path + _lib_suffix).c_str()))) {
				std::cerr << "Can't open and load " << _lib_path << "\n";
			}
#else
			if (!(_libhandle = dlopen((_lib_path + _lib_suffix).c_str(), RTLD_NOW | RTLD_LAZY))) {
				std::cerr << dlerror() << "\n";
			}
#endif
		}

		template <typename T>
		std::shared_ptr<T> get_instance(const std::string &plugin_name) const {
#ifdef WIN32
			auto pl_instance_gen = reinterpret_cast<T *(*)()>(GetProcAddress(_libhandle, plugin_name.c_str()));
			auto pl_instance_dest = reinterpret_cast<void (*)(T *)>(GetProcAddress(_libhandle, (plugin_name + "_destroyer").c_str()));
#else
			auto pl_instance_gen = reinterpret_cast<T *(*)()>(dlsym(_libhandle, plugin_name.c_str()));
			auto pl_instance_dest = reinterpret_cast<void (*)(T *)>(dlsym(_libhandle, (plugin_name + "_destroyer").c_str()));
#endif
			if (!pl_instance_gen || !pl_instance_dest) {
				std::cerr << "cant find allocator or deleter for " << plugin_name << " in " << _lib_path << "\n";
				return std::shared_ptr<T>(nullptr);
			}
			return std::shared_ptr<T>(pl_instance_gen(), [pl_instance_dest](T *p) { pl_instance_dest(p); });
		}

		void close_lib() {
#ifdef WIN32
			if (FreeLibrary(_libhandle) == 0) {
				std::cerr << "err closing: " << _lib_path << "\n";
			}
#else
			if (dlclose(_libhandle) != 0) {
				std::cerr << "err closing: " << _lib_path << "\n";
			}
#endif
		}
	};

} // namespace phpp

#endif