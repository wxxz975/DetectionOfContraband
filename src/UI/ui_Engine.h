#pragma once
#include <memory>
#include "UI/ui_AbstractEngine.h"
#include "UI/ui_EngineConfig.h"
#include "UI/Widgets/ui_FileBrowser.h"

class ui_Engine: public ui_AbstractEngine
{
private:
    std::shared_ptr<ui_EngineAbstractConfig> m_config = std::make_shared<ui_EngineConfig>();
private:
    /* function */
public:
    ui_Engine() = default;
    ~ui_Engine() = default;

    virtual bool setupUi(ui_AbstractEngine* parent = nullptr) override;
};

