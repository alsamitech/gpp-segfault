#ifndef ALSAMI_VULKAN_MAIN_HEADER_OPENGL
#define ALSAMI_VULKAN_MAIN_HEADER_OPENGL

#define ALS_RUNTIME_ERROR 50

//#include "tarray.h"

/*
 *      ALSGM CODENAME YIN
 *      VULKAN SUPPORT COMPONENT
 *
 *      OFFICIAL PUBLIC REPOSITORY
 *      https://github.com/alsamitech/alsgm
 *
 * */

#include <stdio.h>
#include <stdlib.h>

// Requires Vulkan SDK
// https://vulkan.lunarg.com/sdk/home#linux
//#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>
#ifdef GLFW_VULK
#include <GLFW/glfw3.h>
#endif
#include "renderer.h"
#ifdef __cplusplus
extern "C" {
#endif
FILE *vulk_filelgr;

void vulkanlogger_alsami(unsigned int lgr_md, const char* lgr_msg){

    vulk_filelgr=fopen("vulk_runtime.als.log", "w+");

    fprintf(vulk_filelgr, "%s\n", lgr_msg);

}
#ifdef __cplusplus
}
#endif

/*
 *  The Vulkan module for ALSGM Overwrites the Runtime Logs every time it starts.
 *  This is just to save space. If something is truly critical, the module will just log it to console (stderr).
 **/

/*verification stuff*/
#ifdef NDEBUG
  const bool enableValidationLayers=false;
#else
  const bool enableValidationLayers=true;
#endif

void gm_cmdpool_init(uint32_t cmdbufcount){
    VkCommandPool cmd_pool;
    VkCommandPoolCreateInfo gm_pool_info_x;
    gm_pool_info_x.sType            =VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    gm_pool_info_x.queueFamilyIndex = Renderer::vulk_graphics_family_index;
    gm_pool_info_x.flags            =VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkCreateCommandPool(Renderer::a_device,&gm_pool_info_x, nullptr, &cmd_pool);

    VkCommandBuffer gm_cmdbuf;
    VkCommandBufferAllocateInfo gm_cmdbuf_alloc_inf;
    gm_cmdbuf_alloc_inf.sType                   = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    gm_cmdbuf_alloc_inf.commandPool             = cmd_pool;
    gm_cmdbuf_alloc_inf.commandBufferCount      = cmdbufcount;
    gm_cmdbuf_alloc_inf.level                   = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vkAllocateCommandBuffers( Renderer::a_device, &gm_cmdbuf_alloc_inf, &gm_cmdbuf);

    VkCommandBufferBeginInfo gm_cmdbuf_binfo;
    gm_cmdbuf_binfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    // If you give the ONE_TIME_SUBMIT_BIT, you can only submit it once. After that, you need to either reset it or re-record it
    // if you give the the simultaneous use bit, you can use this at the same time as the submit command
    // If you pass the RENDER_PASS_CONTINUE_BIT, it will be ignored if the command-buffer level is primary. On the primary command buffer, you can submit only primary command buffers to the GPU. You can either record one huge primary command buffer and update that for every single frame.
    // However, you can save on memory by recording and reusing them
    gm_cmdbuf_binfo.flags                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vkBeginCommandBuffer(gm_cmdbuf, &gm_cmdbuf_binfo);

    //vkCmdSetViewport(gm_cmdbuf);

    vkEndCommandBuffer(gm_cmdbuf);

    VkSubmitInfo gm_sinfos {};
    gm_sinfos.sType         = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    gm_sinfos.commandBufferCount    = cmdbufcount;
    gm_sinfos.pCommandBuffers       = &gm_cmdbuf;


    vkQueueSubmit(Renderer::a_queue, 1, &gm_sinfos, VK_NULL_HANDLE);

    vkQueueWaitIdle(Renderer::a_queue);

    vkDestroyCommandPool(Renderer::a_device, cmd_pool, nullptr);

}

#ifdef GLFW_VULK
bool checkValidationLayerSupport(){
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount,availableLayers.data());
  return false;
}


VkInstance vulk_instance;

const uint32_t WIDTH=800;
const uint32_t HEIGHT=600;
uint32_t glfwExtensionCount=0;
const char** glfwExtensions;

int vern1;
int vern2;
int vern3;

void win_init(){
  // Tells GLFW to not create an OpenGL context
  glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
}



/*uint graphics_start(){
  win_init();
  vulk_init();
  return 0;
}*/

/*
 *  The Vulkan Procedure can be spun off into it's own process.
 **/
/*void vulk_proc_init(void *Yin){
  vulk_run();
  return NULL;
}*/
#endif
#endif
