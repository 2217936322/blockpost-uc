#pragma once

namespace Draw {
	inline VOID Circle(Vector2 position, float radius, UnityEngine::Color color, int segments)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(position.x, position.y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f)), segments);
	}
}