#include <imgui/imgui.h>
#include "UI/ui_Engine.h"
#include "Common/Image.h"
#include <map>

void OnDocking()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    

    ImGui::End();
}

                            // <lables index, confidence>
void myCreateTable(const std::map<int, float>& data = {}, const std::vector<std::string>& lables = {}) {
    int maxSz = lables.size(), dataCnt = data.size();

    using namespace ImGui;
    auto size = ImGui::GetWindowSize();
    BeginChild("ResultShow", ImVec2(0,400), true, ImGuiWindowFlags_HorizontalScrollbar);

    // Teble header
    Columns(2, "Header");
    //SetColumnWidth(0, 100.f);
    //SetColumnWidth(1, 100.f);
    Text("ClassName"); NextColumn();
    Text("Confidence"); NextColumn();
    Separator();
    Columns(1);

    // Table content
    BeginChild("TableContent", ImVec2(0, 0));
    for (const auto& iter : data)
    {
        Columns(2, "data");
        Text("%s", lables[iter.first].c_str()); NextColumn();
        Text("%.4f", iter.second); NextColumn();
        Columns(1);
    }
    EndChild();


    EndChild();
}


//static ImGui::FileBrowser fileDialog;
bool ui_Engine::setupUi(ui_AbstractEngine* parent) {
    (void)parent; // avoid warning
    
    using namespace ImGui;
    OnDocking();
    {
        Begin("Image Show");

        End();
    }
    static std::map<int, float> mp = {
            {2, 0.87}, {5, 0.56}, {0, 0.87}
    };
    static std::vector<std::string> lables = {
        "cat", "car", "tree", "computer",
        "notebook", "musicBox"
    };
    {
        Begin("Contral Bar");

        myCreateTable(mp, lables);


        {
            BeginChild("ThresHold",ImVec2(0,60), true);
            // get the config
            static float confThreshold = 0.5f;
            static float iouThreshold = 0.45f;

            //Text("");
            //ImGui::SetCursorPosX();
            ImGui::PushItemWidth(100.0f);
            if (SliderFloat("confidence Threshold", &confThreshold, 0, 1)) {
                // change the  out conf
                std::cout << "change confidence:" << confThreshold << "\n";
            }
            
            if (SliderFloat("iou Threshold", &iouThreshold, 0, 1)) {
                std::cout << "change iou:" << iouThreshold << "\n";
            }
            ImGui::PopItemWidth();

            EndChild();
        }

        {
            BeginChild("Contr", ImVec2(0,0), true);
            Text("First. load model");
            Text("Second. select the picture to be reasoned"); NewLine();

            if (Button("LoadModel", ImVec2(100, 80))) {
                /*
                fileDialog.SetTitle("please select a onnx model");
                fileDialog.SetTypeFilters({ ".onnx" });
                fileDialog.Open();
                */
            }
            SameLine();
            if (Button("SelectImage", ImVec2(100, 80))) {
                /*
                fileDialog.SetTitle("please select a image");
                fileDialog.SetTypeFilters({".jpg", ".jpeg", ".png", ".bmp"});
                fileDialog.Open();
                */
            }

            EndChild();
        }
        
        /*
        fileDialog.Display();

        if (fileDialog.HasSelected()) {
            std::cout << "Selected filename:" << fileDialog.GetSelected().string() << std::endl;
            fileDialog.ClearSelected();
        }*/
        
        End();
    }

    return true;
}

// this layout follow the leader
