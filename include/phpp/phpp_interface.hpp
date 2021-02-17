#pragma once
#ifndef phpp_interface_hpp
#define phpp_interface_hpp

#ifdef WIN32
#define PLUGIN_EXPORT __declspec(dllexport)
#else
#define PLUGIN_EXPORT // empty
#endif

// namespace phpp {

// note classtype and pluginname need to be different
#define DEFINE_PLUGIN(plugin_class, plugin_name)                                                                                                               \
	extern "C" {                                                                                                                                               \
	PLUGIN_EXPORT plugin_class *plugin_name() { return new plugin_class(); };                                                                                  \
	PLUGIN_EXPORT void plugin_name##_destroyer(plugin_class *ptr) { delete ptr; };                                                                             \
	};
//}; // namespace phpp

#endif