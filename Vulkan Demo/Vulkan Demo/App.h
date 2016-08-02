#pragma once

#include <GLFW\glfw3.h>
#include <vulkan\vulkan.h>
#include <vector>
#include <string>
#include <functional>

#include "vkhelpers\VkWrapper.h"
#include "vkhelpers\VkQueryHelper.h"
#include "vkhelpers\LayerHelper.h"
#include "vkhelpers\DeviceHelper.h"

class App {

public:
	App();
	~App();

	void runLoop();

	VkInstance getInstance() { return vkInstance; }
	std::vector<const char*>& getReqExtensions() { return reqExtensions; }
	std::vector<const char*>& getReqLayers() { return reqLayers; }

private:
	GLFWwindow * window;
	VkWrapper<VkInstance> vkInstance{ vkDestroyInstance };
	VkWrapper<VkDebugReportCallbackEXT> vkCallback{ vkInstance, destroyDebugCallback };

	std::vector<const char*> reqExtensions;
	std::vector<const char*> reqLayers;

#ifdef NDEBUG	
	const bool enableDebugLayers = false;
#else
	const bool enableDebugLayers = true;
#endif

	VkQueryHelper<VkExtensionProperties> extHelper;
	VkQueryHelper<VkLayerProperties> layerHelper;
	DeviceHelper deviceHelper;

	
	const int WIDTH = 720;
	const int HEIGHT = 480;

	void initGLFW();
	void initVulkan();
	
	void createVkInstance();
	void loadExtensions();
	void loadLayers();
	void setDebugCallback();
	static void destroyDebugCallback(VkInstance instance, VkDebugReportCallbackEXT callback, VkAllocationCallbacks* allocator);

	static VkBool32 debugLayerCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);

};

