#define IMGUI_DEFINE_MATH_OPERATORS

#include "NotificationWindow.hpp"
#include "../utils.hpp"
#include <string>
#include "../NotificationManager.hpp"
#include <time.h>
#include "VolumeWindow.hpp"

using namespace layoff;
using namespace layoff::UI;

inline void NotificationWindow::UpdateCache()
{
	if (!notif::HasNewNotifs()) return;

	auto&& n = notif::LockNotifs();	
	//Oldest notifs end up at the end of the cache
	notifCache.insert(notifCache.begin(), n.obj.rbegin(), n.obj.rend());

	n.obj.clear();

	PrintLn("TODO: play a sound here");
}

void NotificationWindow::Update() { Update(false); }

void NotificationWindow::Update(bool IsVolumeOpened)
{
	s64 ts = time(NULL);

	PushStyling();

	ImVec2 pos = {0,0};
	if (IsVolumeOpened)
		pos.y = VolumeWindow::Size.y;

	int RemoveIndex = -1;
	char subWinName[20] = "win";
	for (u32 i = 0; i < notifCache.size() && i < 4; i++)
	{
		const auto n = notifCache[i];
		if (n.ts + NotifScreenTime < ts)
		{
			RemoveIndex = i;
			break;
		}

		itoa(i, subWinName + 3, 10);
		ImGui::Begin(subWinName, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
		ImGui::SetWindowPos(pos);
		if (n.HasImage())
		{
			ImGui::Text("TODO: image");
			ImGui::Text(n.message.c_str());
			ImGui::Text(n.author.c_str());
		}
		else
		{
			ImGui::Text(n.message.c_str());
			ImGui::Text(n.author.c_str());
		}
		auto sz = ImGui::GetWindowSize();
		pos = { 0, sz.y + pos.y + 1 };
		ImGui::End();
	}

	if (RemoveIndex >= 0)
		notifCache.erase(notifCache.begin() + RemoveIndex, notifCache.end());

	PopStyiling();
}

bool NotificationWindow::ShouldRender()
{
	UpdateCache();
	return notifCache.size() != 0;
}

inline void NotificationWindow::PushStyling()
{
	ImGui::Begin("Notif", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs);
	ImGui::SetWindowPos({ 0, 0 });
	ImGui::SetWindowSize({ MaxNotifWidth, 720 });
}

inline void NotificationWindow::PopStyiling()
{
	ImGui::End();
}