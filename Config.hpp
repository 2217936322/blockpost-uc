#pragma once

namespace Config {
	namespace Aimbot {
		inline bool Enabled{ false };
		inline float Fov{ 90.f };
		inline bool DrawFov{ true };
		inline int Bone{ 0 };
		inline bool Visible{ true };
	}

	namespace ESP {
		inline bool Enabled{ false };
		inline bool Name{ false };
		inline bool Box{ false };

		inline UnityEngine::Color BoxColor{ 0.f, 0.f, 0.f, 1.f };
	}

	namespace Misc {
		inline float CameraFov{ 0.f };
	}
}