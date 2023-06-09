#pragma once
#include <string>
#include <stdint.h>
#include "UI/API/IDrawable.h"
#include "UI/Plugins/Pluginable.h"

namespace DcUI::Internal {class WidgetContainer;}

namespace DcUI::Widgets
{
  class AWidget: public API::IDrawable, public Plugins::Pluginable
  {
    public:
      /*
       * Constructor
       * */
      AWidget();

      /*
       * Draw the widget on the panel
       * */
      virtual void Draw() override;

      /*
       *
       * */
      /**
       * Link the widget to another one by making its id identical to the given widget
       * @param p_widget
       */
      void LinkTo(const AWidget& p_widget);

      /**
       * Mark the widget as destroyed. It will be removed from the owner panel
       * by the garbage collector
       */
      void Destroy();

      /**
       * Returns true if the widget is marked as destroyed
       */
      bool IsDestroyed() const;

      /**
       * Defines the parent of this widget
       * @param p_parent
       */
      void SetParent(Internal::WidgetContainer* p_parent);

      /**
       * Returns true if the widget has a parent
       */
      bool HasParent() const;

      /**
       * Returns the parent of the widget or nullptr if there is no parent
       */
      Internal::WidgetContainer* GetParent();

    protected:
      virtual void _Draw_Impl() = 0;

    public:
      bool enabled = true;
      bool lineBreak = true;

    protected:
      Internal::WidgetContainer* m_parent;
      std::string m_widgetID = "?";
      bool m_autoExecutePlugins = true;

    private:
      static uint64_t __WIDGET_ID_INCREMENT;
      bool m_destroyed = false;

  };

}
