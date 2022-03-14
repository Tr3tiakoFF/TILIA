#pragma once

#include "Tilia/Layer.h"

#include "Tilia/Events/ApplicationEvent.h"
#include "Tilia/Events/MouseEvent.h"
#include "Tilia/Events/KeyEvent.h"

namespace Tilia {

	class TILIA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void SetDarkThemeColors();
		void SetDarkMagentaThemeColors();

	private:
		float m_Time = 0.0f;
	};

}