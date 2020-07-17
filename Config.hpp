#pragma once

namespace Config {
	namespace Aimbot {
		inline bool Enabled{ true };
		inline float Fov{ 90.f };
		inline bool DrawFov{ true };
		inline int Bone{ 0 };
		inline bool Visible{ true };
		inline bool SpawnProtect{ true };
	}

	namespace ESP {
		inline bool Enabled{ true };
		inline bool Visible{ false };
		inline bool Name{ true };
		inline bool Box{ true };

		inline UnityEngine::Color BoxColor{ 1.f, 0.f, 0.f, 1.f };
		inline UnityEngine::Color VisibleBoxColor{ 0.f, 1.f, 0.f, 1.f };
		inline UnityEngine::Color SpawnProtectBoxColor{ 0.f, 0.f, 1.f, 1.f };
	}

	namespace Misc {
		inline float CameraFov{ 0.f };
	}
}