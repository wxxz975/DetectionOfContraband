#pragma once
#include "UI/Widgets/AWidget.h"
#include "UI/Internal/MemoryMode.h"

namespace DcUI::Internal
{
  /**
   * The base class for any widget container
   */
  class WidgetContainer
  {
    public:
      /**
       * Remove a widget from the container
       * @param p_widget
       */
      void RemoveWidget(Widgets::AWidget& p_widget);

      /**
       * Remove all widgets from the container
       */
      void RemoveAllWidgets();

      /**
       * Consider a widget
       * @param p_manageMemory
       */
      void ConsiderWidget(Widgets::AWidget& p_widget, bool p_manageMemory = true);

      /**
       * Unconsider a widget
       * @param p_widget
       */
      void UnconsiderWidget(Widgets::AWidget& p_widget);

      /**
       * Collect garbages by removing widgets marked as "Destroyed"
       */
      void CollectGarbages();

      /**
       * Draw every widgets
       */
      void DrawWidgets();

      /**
       * Allow the user to reverse the draw order of this widget container
       */
      void ReverseDrawOrder(bool reversed = true);

      /**
       * Create a widget
       * @param p_args
       */
      template <typename T, typename ... Args>
        T& CreateWidget(Args&&... p_args)
        {
          m_widgets.emplace_back(new T(p_args...), Internal::MemoryMode::INTERNAL_MANAGMENT);
          T& instance = *reinterpret_cast<T*>(m_widgets.back().first);
          instance.SetParent(this);
          return instance;
        }

      /**
       * Returns the widgets and their memory management mode
       */
      std::vector<std::pair<DcUI::Widgets::AWidget*, Internal::MemoryMode>>& GetWidgets();

    protected:
      std::vector<std::pair<DcUI::Widgets::AWidget*, Internal::MemoryMode>> m_widgets;
      bool m_reversedDrawOrder = false;
  };


}

