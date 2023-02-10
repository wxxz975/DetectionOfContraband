#pragma once
#include <memory>
#include "Common/Image.h"
#include "UI/ui_AbstractEngine.h"
#include "UI/ui_EngineConfig.h"
#include "UI/Widgets/ui_FileBrowser.h"
#include "ModelAdapter/onnx/OnnxruntimeInfer.h"

class OnnxruntimeInfer;

class ui_Engine: public ui_AbstractEngine
{
private:
    std::shared_ptr<ui_EngineAbstractConfig> m_config = std::make_shared<ui_EngineConfig>();

    std::unique_ptr<AbstractDetectAlgorithm> m_algo = std::make_unique<OnnxruntimeInfer>("x_ray.onnx", true);

private:
    ImGui::FileBrowser fileDialog;
    GLuint texId = 0;
    std::vector<DetectionResultNode> m_result;
public:
    ui_Engine() = default;
    ~ui_Engine() = default;

    virtual bool setupUi(ui_AbstractEngine* parent = nullptr) override;

private:
    void OnDocking() const;
};

