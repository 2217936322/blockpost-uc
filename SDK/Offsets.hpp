#pragma once

namespace Offsets {
	namespace Methods {
		namespace Controll {
			inline std::uintptr_t SetLockAttack = Memory::MAKE_RVA(0x6AD070);
			inline std::uintptr_t SetLockAngle = Memory::MAKE_RVA(0x6AD0D0);
		}

		namespace Crosshair {
			inline std::uintptr_t SetCursor = Memory::MAKE_RVA(0x6BAE30);
		}

		namespace Client {
			inline std::uintptr_t IsConnected = Memory::MAKE_RVA(0x606AC0);
		}

		namespace GUIM {
			inline std::uintptr_t YRES = Memory::MAKE_RVA(0x778350);
			inline std::uintptr_t DrawBoxBorder = Memory::MAKE_RVA(0x774BC0);
			inline std::uintptr_t DrawTextColor = Memory::MAKE_RVA(0x776190);
		}

		namespace Texture {
			inline std::uintptr_t GenerateTexture = Memory::MAKE_RVA(0x662F60);
		}

		namespace Screen {
			inline std::uintptr_t GetWidth = Memory::MAKE_RVA(0x3DEF80);
			inline std::uintptr_t GetHeight = Memory::MAKE_RVA(0x3DEF00);
		}

		namespace Camera {
			inline std::uintptr_t WorldToScreen = Memory::MAKE_RVA(0x343640);
		}

		namespace Transform {
			inline std::uintptr_t GetPosition = Memory::MAKE_RVA(0x59AFB0);
			inline std::uintptr_t GetForward = Memory::MAKE_RVA(0x59A9C0);
		}

		namespace GameObject {
			inline std::uintptr_t GetTransform = Memory::MAKE_RVA(0x348F20);
		}
	}

	namespace Hooks {
		inline LPVOID Update = Memory::MAKE_RVA_PTR<VOID>(0x6B7BB0);
		inline LPVOID GUI = Memory::MAKE_RVA_PTR<VOID>(0x6A87E0);
		inline LPVOID GetKeyUp = Memory::MAKE_RVA_PTR<VOID>(0x34B9B0);
	}
}