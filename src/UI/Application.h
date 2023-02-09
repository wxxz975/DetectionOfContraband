#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "UI/AbstractApplication.h"
#include "UI/ui_Engine.h"
#include "ModelAdapter/onnx/OnnxruntimeInfer.h"



class Application: public AbstractApplication
{

private:
    bool isActive = true;
    GLFWwindow* wind = nullptr;
    const char* WindowName = "ContrabandOfDetection";
    ImVec2 windSize = {720.f,  320.f};

    std::unique_ptr<ui_AbstractEngine> m_engine = std::make_unique<ui_Engine>();
    std::unique_ptr<AbstractDetectAlgorithm> m_algo = std::make_unique<OnnxruntimeInfer>("yolov5s.onnx", true);
    float windowFontSacle = 1.2f;
public:
    Application();
    ~Application() = default;

    
    virtual bool run() override;

private:
    void preprocess() const;
    void postprocess() const;
};

//using App = std::unique_ptr<AbstractApplication>;