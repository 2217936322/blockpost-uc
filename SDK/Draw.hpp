#pragma once

namespace Draw {
	inline ImU32 UnityEngineToImU32(UnityEngine::Color color) {
		return ImGui::ColorConvertFloat4ToU32(ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));
	}

	inline VOID Circle(Vector2 position, float radius, UnityEngine::Color color, int segments, float thickness = 1.0F)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(position.x, position.y), radius, UnityEngineToImU32(color), segments, thickness);
	}

	inline VOID Rect(Vector2 position, Vector2 size, UnityEngine::Color color, float thickness = 1.0F)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(position.x, position.y), ImVec2(position.x + size.x, position.y + size.y), UnityEngineToImU32(color), 0, 0, thickness);
	}
}