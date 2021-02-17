#pragma once
#ifndef phpp_handler_hpp
#define phpp_handler_hpp

#include <memory>
#include <phpp/phpp_libhandler.hpp>
#include <string>
#include <unordered_map>

namespace phpp {
	class plugin_handler {
	  private:
		std::string _pl_dir_path;
		std::unordered_map<std::string, std::unique_ptr<lib_handler>> _open_lib_dict;

	  public:
		explicit plugin_handler(const std::string& pl_dir_path) noexcept
			: _pl_dir_path(pl_dir_path){

			  };
		~plugin_handler() {
			for (auto it = _open_lib_dict.begin(); it != _open_lib_dict.end(); ++it) {
				it->second->close_lib();
			}
		};
		template <typename T>
		std::shared_ptr<T> get_plugin(const std::string& lib_name, const std::string& pl_name) {
			std::string fullpath = _pl_dir_path + lib_name;
			if (_open_lib_dict.find(fullpath) == _open_lib_dict.end()) {
				auto lh = std::make_unique<lib_handler>(fullpath);
				lh->open_lib();
				_open_lib_dict.emplace(std::make_pair(fullpath, std::move(lh)));
			}
			return _open_lib_dict.at(fullpath)->get_instance<T>(pl_name);
		};
	};
} // namespace phpp
#endif