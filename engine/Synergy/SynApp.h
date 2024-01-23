#pragma once

#define PLATFORM_WIN32 1

#include <chrono>
#include <vector>
#include <iostream>

#include "RenderTargetCube.h"
#include "RenderTarget2D.h"
#include "RefCntAutoPtr.hpp"
#include "RenderDevice.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "RenderStateNotationLoader.h"
#include "BasicMath.hpp"

#include "GLFW/glfw3.h"



#ifndef ENGINE_DLL
#    define ENGINE_DLL 1
#endif

#ifndef D3D11_SUPPORTED
#    define D3D11_SUPPORTED 0
#endif

#ifndef D3D12_SUPPORTED
#    define D3D12_SUPPORTED 0
#endif

#ifndef GL_SUPPORTED
#    define GL_SUPPORTED 0
#endif

#ifndef VULKAN_SUPPORTED
#    define VULKAN_SUPPORTED 0
#endif

#ifndef METAL_SUPPORTED
#    define METAL_SUPPORTED 0
#endif

#if PLATFORM_WIN32
#    define GLFW_EXPOSE_NATIVE_WIN32 1
#endif

#if PLATFORM_LINUX
#    define GLFW_EXPOSE_NATIVE_X11 1
#endif

#if PLATFORM_MACOS
#    define GLFW_EXPOSE_NATIVE_COCOA 1
#endif

#if D3D11_SUPPORTED
#    include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#endif
#if D3D12_SUPPORTED
#    include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#endif
#if GL_SUPPORTED
#    include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#endif
#if VULKAN_SUPPORTED
#    include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#endif
#if METAL_SUPPORTED
#    include "Graphics/GraphicsEngineMetal/interface/EngineFactoryMtl.h"
#endif

#ifdef GetObject
#    undef GetObject
#endif
#ifdef CreateWindow
#    undef CreateWindow
#endif

class AppState;

using namespace Diligent;

class SynApp
{
public:

    SynApp(int width, int height,std::string title, bool full_screen);
    bool InitDE(RENDER_DEVICE_TYPE DevType);
    void Run();
    void BeginFrame();
    void CreateFrame();
    void EndFrame();

    //state
    void PushState(AppState* state);
    void PopState();

  
    
    static SynApp* This;

    int GetWidth() {
        if (_BoundRTCube != nullptr) {
            return _BoundRTCube->GetWidth();
        }
        if (_BoundRT2D != nullptr) {
            return _BoundRT2D->GetWidth();
        }
        return _width;
    }

    int GetHeight() {
        if (_BoundRTCube != nullptr) {
            return _BoundRTCube->GetHeight();
        }
        if (_BoundRT2D != nullptr) {
            return _BoundRT2D->GetHeight();
        }
        return _height;
    }

    void SetBoundCubeRT(RenderTargetCube* cube) {
        _BoundRTCube = cube;
    }
    void SetBound2DRT(RenderTarget2D* rt) {
        _BoundRT2D = rt;
    }
    RenderTargetCube* GetBoundCubeRT() {

    }

    //diligent
    IEngineFactory* GetEngineFactory() { return m_pDevice->GetEngineFactory(); }
    IRenderDevice* GetDevice() { return m_pDevice; }
    IDeviceContext* GetContext() { return m_pImmediateContext; }
    ISwapChain* GetSwapChain() { return m_pSwapChain; }
    
    


    
    IRenderDevice* m_pDevice;
    IDeviceContext* m_pImmediateContext;
    ISwapChain*     m_pSwapChain;
    GLFWwindow* m_Window = nullptr;
    std::vector<AppState*> _states;
    int _width, _height;
    RenderTargetCube* _BoundRTCube = nullptr;
    RenderTarget2D* _BoundRT2D = nullptr;
private:
    using TClock = std::chrono::high_resolution_clock;
    using TSeconds = std::chrono::duration<float>;
};

