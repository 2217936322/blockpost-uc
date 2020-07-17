#pragma once

namespace UnityEngine {
	class Rect {
	public:
		float XMin, YMin, Width, Height;
	};

	class Color {
	public:
		float r, g, b, a;
	};

	struct RaycastHit {
		Vector3 Point;
		Vector3 Normal;
		std::uint32_t FaceID;
		float Distance;
		Vector2 UV;
		std::int32_t Collider;
	};

	class Controll {
	public:
		static void SetLockAttack(bool value) {
			return reinterpret_cast<void(*)(bool)>(Offsets::Methods::Controll::SetLockAttack)(value);
		}

		static void SetLockAngle(bool value) {
			return reinterpret_cast<void(*)(bool)>(Offsets::Methods::Controll::SetLockAngle)(value);
		}
	};

	class Crosshair {
	public:
		static void SetCursor(bool value) {
			return reinterpret_cast<void(*)(bool)>(Offsets::Methods::Crosshair::SetCursor)(value);
		}
	};

	class Client {
	public:
		static bool IsConnected() {
			return reinterpret_cast<bool(*)()>(Offsets::Methods::Client::IsConnected)();
		}
	};

	class GUIM {
	public:
		static float YRES(float value) {
			return reinterpret_cast<float(*)(float)>(Offsets::Methods::GUIM::YRES)(value);
		}

		static void DrawBox(UnityEngine::Rect rect, void* texture) {
			return reinterpret_cast<void(*)(UnityEngine::Rect, void*)>(Offsets::Methods::GUIM::DrawBox)(rect, texture);
		}

		static void DrawBoxBorder(UnityEngine::Rect rect, void* texture, float a) {
			return reinterpret_cast<void(*)(UnityEngine::Rect, void*, float)>(Offsets::Methods::GUIM::DrawBoxBorder)(rect, texture, a);
		}

		static void DrawTextColor(UnityEngine::Rect rect, SystemString* text, std::int32_t pos, std::int32_t fontcolor, std::int32_t fontpos, std::int32_t fontsize, bool fontshadow) {
			return reinterpret_cast<void(*)(UnityEngine::Rect, SystemString*, std::int32_t, std::int32_t, std::int32_t, std::int32_t, bool)>(Offsets::Methods::GUIM::DrawTextColor)(rect, text, pos, fontcolor, fontpos, fontsize, fontshadow);
		}
	};

	class Texture {
	public:
		static void* GenerateTexture(UnityEngine::Color color, SystemString* name) {
			return reinterpret_cast<void* (*)(UnityEngine::Color, SystemString*)>(Offsets::Methods::Texture::GenerateTexture)(color, name);
		}
	};

	class Screen {
	public:
		static Resolution GetResolution() {
			return { reinterpret_cast<std::int32_t(*)()>(Offsets::Methods::Screen::GetWidth)(),
				reinterpret_cast<std::int32_t(*)()>(Offsets::Methods::Screen::GetHeight)() };
		}
	};

	class Camera {
	public:
		static Vector3 WorldToScreen(Camera* instance, Vector3 position) {
			return reinterpret_cast<Vector3(*)(Camera*, Vector3)>(Offsets::Methods::Camera::WorldToScreen)(instance, position);
		}

		static float FieldOfView(Camera* instance) {
			return reinterpret_cast<float(*)(Camera*)>(Offsets::Methods::Camera::FieldOfView)(instance);
		}

		static void SetFieldOfView(Camera* instance, float value) {
			return reinterpret_cast<void(*)(Camera*, float)>(Offsets::Methods::Camera::SetFieldOfView)(instance, value);
		}
	};

	class Physics {
	public:
		static bool Linecast(Vector3 start, Vector3 end, RaycastHit& hit_info) {
			return reinterpret_cast<bool(*)(Vector3, Vector3, RaycastHit&)>(Offsets::Methods::Physics::Linecast)(start, end, hit_info);
		}
	};

	class Transform {
	public:
		static Vector3 GetPosition(Transform* instance) {
			return reinterpret_cast<Vector3(*)(Transform*)>(Offsets::Methods::Transform::GetPosition)(instance);
		}

		static Vector3 GetRight(Transform* instance) {
			return reinterpret_cast<Vector3(*)(Transform*)>(Offsets::Methods::Transform::GetRight)(instance);
		}

		static Vector3 GetUp(Transform* instance) {
			return reinterpret_cast<Vector3(*)(Transform*)>(Offsets::Methods::Transform::GetUp)(instance);
		}

		static Vector3 GetForward(Transform* instance) {
			return reinterpret_cast<Vector3(*)(Transform*)>(Offsets::Methods::Transform::GetForward)(instance);
		}

		static Vector3 GetLocalScale(Transform* instance) {
			return reinterpret_cast<Vector3(*)(Transform*)>(Offsets::Methods::Transform::GetLocalScale)(instance);
		}
	};

	class GameObject {
	public:
		static Transform* GetTransform(GameObject* instance) {
			return reinterpret_cast<Transform * (*)(GameObject*)>(Offsets::Methods::GameObject::GetTransform)(instance);
		}
	};
}