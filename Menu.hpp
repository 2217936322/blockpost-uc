#pragma once

constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

namespace Menu {
	static inline bool Open = true;

	inline void AimbotWindow() {
		ImGui::Checkbox("Enabled", &Config::Aimbot::Enabled);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Fov", &Config::Aimbot::DrawFov);
		ImGui::Checkbox("Visible check", &Config::Aimbot::Visible);
		ImGui::Checkbox("Spawn protect", &Config::Aimbot::SpawnProtect);

		ImGui::SliderFloat("Fov", &Config::Aimbot::Fov, 10.0f, 360.0f, "%.2f", 1.f);
		ImGui::Combo("Bone", &Config::Aimbot::Bone, "Head\0Chest\0");
	}

	inline void ESPWindow() {
		ImGui::Checkbox("Enabled", &Config::ESP::Enabled);
		ImGui::Checkbox("Visible check", &Config::ESP::Visible);
		ImGui::Checkbox("Name", &Config::ESP::Name);
		ImGui::Checkbox("Box", &Config::ESP::Box);

		if (ImGui::TreeNode("Box Colors"))
		{
			static float BoxColor[4] = { Config::ESP::BoxColor.r, Config::ESP::BoxColor.g, Config::ESP::BoxColor.b, Config::ESP::BoxColor.a };

			if (ImGui::ColorEdit4("Box", BoxColor, ImGuiColorEditFlags_None)) {
				Config::ESP::BoxColor.r = BoxColor[0];
				Config::ESP::BoxColor.g = BoxColor[1];
				Config::ESP::BoxColor.b = BoxColor[2];
				Config::ESP::BoxColor.a = BoxColor[3];
			}

			static float VisibleBoxColor[4] = { Config::ESP::VisibleBoxColor.r, Config::ESP::VisibleBoxColor.g, Config::ESP::VisibleBoxColor.b, Config::ESP::VisibleBoxColor.a };

			if (ImGui::ColorEdit4("Visible Box", VisibleBoxColor, ImGuiColorEditFlags_None)) {
				Config::ESP::VisibleBoxColor.r = VisibleBoxColor[0];
				Config::ESP::VisibleBoxColor.g = VisibleBoxColor[1];
				Config::ESP::VisibleBoxColor.b = VisibleBoxColor[2];
				Config::ESP::VisibleBoxColor.a = VisibleBoxColor[3];
			}

			static float SpawnProtectBoxColor[4] = { Config::ESP::SpawnProtectBoxColor.r, Config::ESP::SpawnProtectBoxColor.g, Config::ESP::SpawnProtectBoxColor.b, Config::ESP::SpawnProtectBoxColor.a };

			if (ImGui::ColorEdit4("Spawn Protect Box", SpawnProtectBoxColor, ImGuiColorEditFlags_None)) {
				Config::ESP::SpawnProtectBoxColor.r = SpawnProtectBoxColor[0];
				Config::ESP::SpawnProtectBoxColor.g = SpawnProtectBoxColor[1];
				Config::ESP::SpawnProtectBoxColor.b = SpawnProtectBoxColor[2];
				Config::ESP::SpawnProtectBoxColor.a = SpawnProtectBoxColor[3];
			}

			ImGui::TreePop();
		}
	}

	inline void MiscWindow() {
		if (!UnityEngine::Client::IsConnected()) {
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}

		ImGui::SliderFloat("Camera fov", &Config::Misc::CameraFov, 10.0f, 180.0f, "%.2f", 1.f);

		if (!UnityEngine::Client::IsConnected()) {
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}
	}

	inline void Theme() {
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_Separator] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);

		style->FramePadding = ImVec2(4, 2);
		style->ItemSpacing = ImVec2(10, 2);
		style->IndentSpacing = 12;
		style->ScrollbarSize = 10;

		style->WindowRounding = 0;
		style->FrameRounding = 0;
		style->PopupRounding = 0;
		style->GrabRounding = 0;
		style->TabRounding = 0;

		style->WindowMenuButtonPosition = ImGuiDir_Right;

		style->DisplaySafeAreaPadding = ImVec2(4, 4);
	}

	inline void SeparatorWithPadding(ImVec2 padding) {
		ImGui::Dummy(padding);
		ImGui::Separator();
		ImGui::Dummy(padding);
	}

	inline void Render() {
		if (!Menu::Open) return;

		Menu::Theme();

		ImGui::SetNextWindowSize({ 500.f, 0.f });
		ImGui::Begin("BLOCKPOST", nullptr, window_flags);

		if (ImGui::TreeNode("Aimbot")) {
			AimbotWindow(); ImGui::TreePop();
		}

		Menu::SeparatorWithPadding(ImVec2(0, 4));

		if (ImGui::TreeNode("ESP")) {
			ESPWindow(); ImGui::TreePop();
		}

		Menu::SeparatorWithPadding(ImVec2(0, 4));

		if (ImGui::TreeNode("Misc")) {
			MiscWindow(); ImGui::TreePop();
		}
	}
}
