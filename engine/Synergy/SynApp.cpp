#include "SynApp.h"



#include "GLFW/glfw3native.h"
#ifdef GetObject
#    undef GetObject
#endif
#ifdef CreateWindow
#    undef CreateWindow
#endif


using namespace Diligent;

SynApp* SynApp::This = nullptr;

SynApp::SynApp(int width, int height, std::string title, bool full_screen) {

	std::cout << "Synergy Lib intialized." << std::endl;
    if (glfwInit() != GLFW_TRUE)
        return;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //if (GlfwApiHint == GLFW_OPENGL_API)
    {
        // We need compute shaders, so request OpenGL 4.2 at least
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    }


    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
    //    LOG_ERROR_MESSAGE("Failed to create GLFW window");
        return;
    }

    glfwSetWindowUserPointer(m_Window, this);
//    glfwSetFramebufferSizeCallback(m_Window, &GLFW_ResizeCallback);
//    glfwSetKeyCallback(m_Window, &GLFW_KeyCallback);
//    glfwSetMouseButtonCallback(m_Window, &GLFW_MouseButtonCallback);
//    glfwSetCursorPosCallback(m_Window, &GLFW_CursorPosCallback);
 //   glfwSetScrollCallback(m_Window, &GLFW_MouseWheelCallback);

    glfwSetWindowSizeLimits(m_Window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    if (InitDE(RENDER_DEVICE_TYPE_D3D12)) {
    
        std::cout << "Initialized back-end." << std::endl;
    
    }
    else {
        std::cout << "Failed to initialize back-end." << std::endl;
    }

    This = this;

    return;
}

bool SynApp::InitDE(RENDER_DEVICE_TYPE DevType) {

#if PLATFORM_WIN32
    Win32NativeWindow Window{ glfwGetWin32Window(m_Window) };
#endif


    SwapChainDesc SCDesc;
    switch (DevType)
    {
#if D3D11_SUPPORTED
    case RENDER_DEVICE_TYPE_D3D11:
    {
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D11() function
        auto* GetEngineFactoryD3D11 = LoadGraphicsEngineD3D11();
#    endif
        auto* pFactoryD3D11 = GetEngineFactoryD3D11();

        EngineD3D11CreateInfo EngineCI;
        pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
    }
    break;
#endif // D3D11_SUPPORTED


#if D3D12_SUPPORTED
    case RENDER_DEVICE_TYPE_D3D12:
    {
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D12() function
        auto* GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
#    endif
        auto* pFactoryD3D12 = GetEngineFactoryD3D12();

        EngineD3D12CreateInfo EngineCI;
        pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
    }
    break;
#endif // D3D12_SUPPORTED


#if GL_SUPPORTED
    case RENDER_DEVICE_TYPE_GL:
    {
#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
        // Load the dll and import GetEngineFactoryOpenGL() function
        auto GetEngineFactoryOpenGL = LoadGraphicsEngineOpenGL();
#    endif
        auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

        EngineGLCreateInfo EngineCI;
        EngineCI.Window = Window;
        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc, &m_pSwapChain);
    }
    break;
#endif // GL_SUPPORTED


#if VULKAN_SUPPORTED
    case RENDER_DEVICE_TYPE_VULKAN:
    {
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
        // Load the dll and import GetEngineFactoryVk() function
        auto* GetEngineFactoryVk = LoadGraphicsEngineVk();
#    endif
        auto* pFactoryVk = GetEngineFactoryVk();

        EngineVkCreateInfo EngineCI;
        pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
    }
    break;
#endif // VULKAN_SUPPORTED

#if METAL_SUPPORTED
    case RENDER_DEVICE_TYPE_METAL:
    {
        auto* pFactoryMtl = GetEngineFactoryMtl();

        EngineMtlCreateInfo EngineCI;
        pFactoryMtl->CreateDeviceAndContextsMtl(EngineCI, &m_pDevice, &m_pImmediateContext);
        pFactoryMtl->CreateSwapChainMtl(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
    }
    break;
#endif // METAL_SUPPORTED

    default:
        std::cerr << "Unknown/unsupported device type";
        return false;
        break;
    }

    if (m_pDevice == nullptr || m_pImmediateContext == nullptr || m_pSwapChain == nullptr)
        return false;

    return true;

}

void SynApp::BeginFrame() {

    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    ITextureView* pRTV = pSwapchain->GetCurrentBackBufferRTV();
    pContext->SetRenderTargets(1, &pRTV, nullptr, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    const float ClearColor[4] = {0.1f,0.1f,0.1f,1.0f};
    pContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);

}

void SynApp::EndFrame() {

    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    pContext->Flush();
    pSwapchain->Present();

}

void SynApp::Run() {

    while (true) {
        glfwPollEvents();

        BeginFrame();

        EndFrame();

    }

}