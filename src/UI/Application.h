#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "UI/AbstractApplication.h"
#include "UI/ui_Engine.h"



class Application: public AbstractApplication, public ui_Engine
{

private:
    bool isActive = true;
    GLFWwindow* wind = nullptr;
    const char* WindowName = "ContrabandOfDetection";
    ImVec2 windSize = {1920.f,  1080.f};

    float windowFontSacle = 1.4f;
public:
    Application();
    ~Application() = default;

    
    virtual bool run() override;

private:
    void preprocess() const;
    void postprocess() const;
};

