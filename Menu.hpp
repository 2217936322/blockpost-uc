#pragma once

constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

namespace Menu {
	static inline bool Open = true;

	inline void AimbotWindow() {
		ImGui::PushItemWidth(200);

		ImGui::Checkbox("Enabled", &Config::Aimbot::Enabled);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Fov", &Config::Aimbot::DrawFov);

		ImGui::SliderFloat("Fov", &Config::Aimbot::Fov, 10.0f, 360.0f, "%.2f", 1.f);
		ImGui::Combo("Bone", &Config::Aimbot::Bone, "Head\0Chest\0");
	}

	inline void ESPWindow() {
		ImGui::PushItemWidth(200);

		ImGui::Checkbox("Enabled", &Config::ESP::Enabled);
		ImGui::Checkbox("Name", &Config::ESP::Name);
		ImGui::Checkbox("Box", &Config::ESP::Box);

		static float BoxColor[4] = { Config::ESP::BoxColor.r, Config::ESP::BoxColor.g, Config::ESP::BoxColor.b, Config::ESP::BoxColor.a };

		if (ImGui::ColorEdit4("Box Color", BoxColor, ImGuiColorEditFlags_None)) {
			Config::ESP::BoxColor.r = BoxColor[0];
			Config::ESP::BoxColor.g = BoxColor[1];
			Config::ESP::BoxColor.b = BoxColor[2];
			Config::ESP::BoxColor.a = BoxColor[3];
		}
	}

	inline void Render() {
		if (!Menu::Open) return;

		ImGui::SetNextWindowSize({ 0.f, 0.f });
		ImGui::Begin("BLOCKPOST", nullptr, window_flags | ImGuiWindowFlags_NoTitleBar);

		if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
			if (ImGui::BeginTabItem("Aimbot")) {
				AimbotWindow();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("ESP")) {
				ESPWindow();
				ImGui::EndTabItem();
			}
		}
	}
}