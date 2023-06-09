#pragma once
#include "UI/API/IDrawable.h"
#include "UI/Panels/APanel.h"
#include <vector>
#include <algorithm>


namespace DcUI::Modules
{
	/**
	* A Canvas represents the whole frame available for UI drawing
	*/
	class Canvas : public API::IDrawable
	{
	public:
		/**
		* Adds a panel to the canvas
		* @param p_panel
		*/
		void AddPanel(Panels::APanel& p_panel);

		/**
		* Removes a panel from the canvas
		* @param p_panel
		*/
		void RemovePanel(Panels::APanel& p_panel);

		/**
		* Removes every panels from the canvas
		*/
		void RemoveAllPanels();

		/**
		* Makes the canvas a dockspace (Dockable panels will be able to attach themselves to the canvas)
		*/
		void MakeDockspace(bool p_state);

		/**
		* Returns true if the canvas is a dockspace
		*/
		bool IsDockspace() const;

		/**
		* Draw the canvas (Draw every panels)
		*/
		void Draw() override;

	private:
		std::vector<std::reference_wrapper<Panels::APanel>> m_panels;
		bool m_isDockspace = false;
	};
}
