#include "SynApp.h"
#include "AppInput.h"

#include <chrono>
#include "GLFW/glfw3native.h"
#include "SynUI.h"
#ifdef GetObject
#    undef GetObject
#endif
#ifdef CreateWindow
#    undef CreateWindow
#endif

#include "AppState.h"
#include "Texture2D.h"

using namespace Diligent;

SynApp* SynApp::This = nullptr;
double lx, ly;

void* bg_data = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        AppInput::_KeyState[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        AppInput::_KeyState[key] = false;
    };

    //if (key == GLFW_KEY_E && action == GLFW_PRESS)
    //    activate_airship();

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        AppInput::_ButtonState[0] = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

        AppInput::_ButtonState[0] = false;

    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        AppInput::_ButtonState[1] = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {

        AppInput::_ButtonState[1] = false;

    }

}

void GLFW_ResizeCallback(GLFWwindow* wnd, int w, int h)
{
    //auto* pSelf = static_cast<SynApp*>(glfwGetWindowUserPointer(wnd));

    auto pSelf = SynApp::This;

    if (pSelf->m_pSwapChain != nullptr)
        pSelf->m_pSwapChain->Resize(static_cast<Uint32>(w), static_cast<Uint32>(h));
    pSelf->_width = w;
    pSelf->_height = h;

        SynUI::This->Resize(w, h);
}


SynApp::SynApp(int width, int height, std::string title, bool full_screen) {

    for (int i = 0; i < 512; i++) {
        AppInput::_KeyState[i] == false;
    }
    for (int i = 0; i < 16; i++)
    {
        AppInput::_ButtonState[i] = false;
    }
    
  



    _width = width;
    _height = height;
	std::cout << "Synergy Lib intialized." << std::endl;
    if (glfwInit() != GLFW_TRUE)
        return;
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
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
    glfwSetFramebufferSizeCallback(m_Window, &GLFW_ResizeCallback);
     glfwSetKeyCallback(m_Window, &key_callback);
//    glfwSetMouseButtonCallback(m_Window, &GLFW_MouseButtonCallback);
//    glfwSetCursorPosCallback(m_Window, &GLFW_CursorPosCallback);
 //   glfwSetScrollCallback(m_Window, &GLFW_MouseWheelCallback);
     glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetWindowSizeLimits(m_Window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    if (InitDE(RENDER_DEVICE_TYPE_D3D11)) {
    
        std::cout << "Initialized back-end." << std::endl;
    
    }
    else {
        std::cout << "Failed to initialize back-end." << std::endl;
    }
    glfwSwapInterval(0);
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

    auto dsv = pSwapchain->GetDepthBufferDSV();

    ITextureView* pRTV = pSwapchain->GetCurrentBackBufferRTV();
    pContext->SetRenderTargets(1, &pRTV, dsv, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    const float ClearColor[4] = {0,0,0,1.0f};
    pContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_VERIFY);
    pContext->ClearDepthStencil(dsv, CLEAR_DEPTH_FLAG, 1.0, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void SynApp::EndFrame() {

    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    //pContext->Flush();
    pSwapchain->Present();

}

void SynApp::SetWindow(glm::vec2 pos) {

    int px, py;
    px = py = 0;
    glfwGetWindowPos(m_Window, &px, &py);
    
    glfwSetWindowPos(m_Window, pos.x, pos.y);
     

     double mx, my;
     mx = my = 0;

     int ax = pos.x - px;
     int ay = pos.y - py;

     lx = lx - ax;
     ly = ly - ay;

     glfwGetCursorPos(m_Window, &mx, &my);

     //lx = mx;
     //ly = my;


}



void SynApp::Run() {

    int fps = 0;
    int frame = 0;
    int ltick = 0;

    bool first = true;
    TClock::time_point m_LastUpdate = {};
  
    lx = ly = 0;
    int ptime = 0;
    float dt3 = 0;
    int dt4;
    m_LastUpdate = TClock::now();
    while (true) {
        glfwPollEvents();

        double p_x, p_y;
        glfwGetCursorPos(m_Window, &p_x, &p_y);
        AppInput::_MousePosition = glm::vec2(p_x, p_y);
        AppInput::_MouseDelta = glm::vec2(p_x - lx, p_y - ly);
        lx = p_x;
        ly = p_y;
        if (first) {
            AppInput::_MouseDelta = glm::vec2(0, 0);
            first = false;
        }



        BeginFrame();

        if (DesktopTex == nullptr)
        {
//            DesktopTex = new Texture2D((char*)bg_data, screenWidth, screenHeight, 4);
        }

        const auto time = TClock::now();
        const auto dt = std::chrono::duration_cast<TSeconds>(time - m_LastUpdate).count();
        m_LastUpdate = time;


        float dt2 = std::min(dt, 1.0f/30.0f);


        

        if (_states.size() > 0) {
            auto state = _states.back();
            state->UpdateState(dt2);
            state->RenderState();

        }

        int time1 = clock();
        
     
        if (time1 > ltick + 1000) {
            ltick = time1;
            fps = frame;
            frame = 0;
            std::cout << "FPS:" << fps << std::endl;
        }
        frame++;
        

        EndFrame();

    }

}


void SynApp::ClearZ() {

    auto* pContext = GetContext();
    auto* pSwapchain = GetSwapChain();

    auto dsv = pSwapchain->GetDepthBufferDSV();
    pContext->ClearDepthStencil(dsv, CLEAR_DEPTH_FLAG, 1.0, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

//State

void SynApp::PushState(AppState* state) {

    _states.push_back(state);
    state->InitState();

}

void SynApp::PopState() {

    auto state = _states.back();
    _states.pop_back();
    state->EndState();


}

void* bitmapToRGBA(HBITMAP hBitmap, int width, int height) {
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height; // Negative to ensure top-down bitmap
    bi.biPlanes = 1;
    bi.biBitCount = 32; // 32 bits per pixel for RGBA
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0; // No compression
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    HDC hDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hDC);

    // Allocate memory for RGBA data
    BYTE* pData = (BYTE*)malloc(width * height * 4); // 4 bytes per pixel (RGBA)
    if (!pData) {
        DeleteDC(hMemDC);
        ReleaseDC(NULL, hDC);
        return NULL;
    }

    // Extract the data
    BITMAPINFO biInfo;
    biInfo.bmiHeader = bi;
    GetDIBits(hMemDC, hBitmap, 0, height, pData, &biInfo, DIB_RGB_COLORS);

    // Set alpha channel to 255 (fully opaque)
    for (int i = 0; i < width * height; i++) {
        pData[i * 4 + 3] = 255;
    }

    DeleteDC(hMemDC);
    ReleaseDC(NULL, hDC);

    return pData;
}

void* captureScreenUnderWindow(int x,int y,int w,int h) {
    int winX, winY, winWidth, winHeight;
    winX = x;
    winY = y;
    winWidth = w;
    winHeight = h;
    //    glfwGetWindowPos(window, &winX, &winY);

    //glfwGetWindowSize(window, &winWidth, &winHeight);

    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, winWidth, winHeight);
    SelectObject(hDC, hBitmap);

    // Copy from screen to bitmap
    BitBlt(hDC, 0, 0, winWidth, winHeight, hScreen, winX, winY, SRCCOPY);

    // Here you can process the bitmap (hBitmap) and extract RGB data
    // ...

    void* rgbData = bitmapToRGBA(hBitmap, winWidth, winHeight);

    if (rgbData) {
        // Process RGB data
        // ...

        // Don't forget to free the memory!
       // free(rgbData);
    }

    // Cleanup
    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);

    return rgbData;
}


void* SynApp::GetBackground(int x,int y,int w,int h) {

    int winX, winY, winWidth, winHeight;
   // glfwGetWindowPos(m_Window, &winX, &winY);
  //  glfwGetWindowSize(m_Window, &winWidth, &winHeight);

     screenWidth = GetSystemMetrics(SM_CXSCREEN);
     screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
   // glfwSetWindowPos(m_Window, 2000, 0);
  //  glfwIconifyWindow(m_Window); // or glfwHideWindow(window);

    auto rgb = captureScreenUnderWindow(x,y,w,h);

//    glfwSetWindowPos(m_Window, winX, winY);

 //   glfwIconifyWindow(m_Window); // or glfwHideWindow(window);
//    glfwRestoreWindow(m_Window); // 

    int b = 5;


   // free(rgb);

    return rgb;

}

void SynApp::Minimize() {

    glfwIconifyWindow(m_Window);

}

void SynApp::Maximize() {

    glfwMaximizeWindow(m_Window);
}

bool SynApp::IsVisible() {

    return IsWindowVisible(glfwGetWin32Window(m_Window));

}