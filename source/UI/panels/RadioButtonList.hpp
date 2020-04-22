#pragma once
#include "ButtonList.hpp"

namespace layoff::UI::IPC {

	class RadioButtonList : public ButtonsListBase
	{
	public:
		RadioButtonList(const LayoffName* data, u8 count, LayoffIdentifier id, u64 inlineFlags) : ButtonsListBase(data, count, id, inlineFlags) {}

		void Update() override
		{
			int i = 0;
			for (auto& n : names)
			{
				if (inlineFlags & (1ull << i))
					ImGui::SameLine();

				if (ImGui::RadioButton(n.str, active == i))
				{
					active = i;
					eventData = i;
					ImGui::FocusWindow(ImGui::GetCurrentWindow());
				}
				i++;
			}
		}

		~RadioButtonList() override { }
	private:
		int active = -1;
	};
}