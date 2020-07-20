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
			return Memory::FUNCTION_CAST<void, bool>(Offsets::Methods::Controll::SetLockAttack, value);
		}

		static void SetLockAngle(bool value) {
			return Memory::FUNCTION_CAST<void, bool>(Offsets::Methods::Controll::SetLockAngle, value);
		}
	};

	class Crosshair {
	public:
		static void SetCursor(bool value) {
			return Memory::FUNCTION_CAST<void, bool>(Offsets::Methods::Crosshair::SetCursor, value);
		}
	};

	class Client {
	public:
		static bool IsConnected() {
			return Memory::FUNCTION_CAST<bool>(Offsets::Methods::Client::IsConnected);
		}
	};

	class Texture;

	class GUIM {
	public:
		static float YRES(float value) {
			return Memory::FUNCTION_CAST<float>(Offsets::Methods::GUIM::YRES, value);
		}

		static void DrawBox(Rect rect, std::add_pointer_t<Texture> texture) {
			return Memory::FUNCTION_CAST<void, Rect, std::add_pointer_t<Texture>>(Offsets::Methods::GUIM::DrawBox, rect, texture);
		}

		static void DrawBoxBorder(Rect rect, std::add_pointer_t<Texture> texture, float alpha) {
			return Memory::FUNCTION_CAST<void, Rect, std::add_pointer_t<Texture>, float>(Offsets::Methods::GUIM::DrawBoxBorder, rect, texture, alpha);
		}

		static void DrawTextColor(Rect rect, std::add_pointer_t<SystemString> text, std::int32_t pos, std::int32_t fontcolor, std::int32_t fontpos, std::int32_t fontsize, bool fontshadow) {
			return Memory::FUNCTION_CAST<void, Rect, std::add_pointer_t<SystemString>, std::int32_t, std::int32_t, std::int32_t, std::int32_t, bool>(Offsets::Methods::GUIM::DrawTextColor, rect, text, pos, fontcolor, fontpos, fontsize, fontshadow);
		}
	};

	class Input {
	public:
		static bool GetKey(Enums::KeyCode key) {
			return Memory::FUNCTION_CAST<bool, Enums::KeyCode>(Offsets::Methods::Input::GetKey, key);
		}
	};

	class Object {
	public:
		static std::add_pointer_t<SystemString> GetName(std::add_pointer_t<Object> instance) {
			return Memory::FUNCTION_CAST<std::add_pointer_t<SystemString>, std::add_pointer_t<Object>>(Offsets::Methods::Object::GetName, instance);
		}
	};

	class Texture {
	public:
		static std::add_pointer_t<Texture> GenerateTexture(Color color, SystemString* name) {
			return Memory::FUNCTION_CAST<std::add_pointer_t<Texture>, Color, SystemString*>(Offsets::Methods::Texture::GenerateTexture, color, name);
		}

		static void SetPixel(std::add_pointer_t<Texture> instance, std::int32_t x, std::int32_t y, Color color) {
			return Memory::FUNCTION_CAST<void, std::add_pointer_t<Texture>, int32_t, int32_t, Color>(Offsets::Methods::Texture::SetPixel, instance, x, y, color);
		}

		static void Apply(std::add_pointer_t<Texture> instance, bool UpdateMipmaps) {
			return Memory::FUNCTION_CAST<void, std::add_pointer_t<Texture>, bool>(Offsets::Methods::Texture::Apply, instance, UpdateMipmaps);
		}
	};

	class Screen {
	public:
		static Resolution GetResolution() {
			return { Memory::FUNCTION_CAST<std::int32_t>(Offsets::Methods::Screen::GetWidth),
				Memory::FUNCTION_CAST<std::int32_t>(Offsets::Methods::Screen::GetHeight) };
		}
	};

	class Camera {
	public:
		static Vector3 WorldToScreen(std::add_pointer_t<Camera> instance, Vector3 position) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Camera>, Vector3>(Offsets::Methods::Camera::WorldToScreen, instance, position);
		}

		static float FieldOfView(std::add_pointer_t<Camera> instance) {
			return Memory::FUNCTION_CAST<float, std::add_pointer_t<Camera>>(Offsets::Methods::Camera::FieldOfView, instance);
		}

		static void SetFieldOfView(std::add_pointer_t<Camera> instance, float value) {
			return Memory::FUNCTION_CAST<void, std::add_pointer_t<Camera>, float>(Offsets::Methods::Camera::SetFieldOfView, instance, value);
		}
	};

	class Physics {
	public:
		static bool Linecast(Vector3 start, Vector3 end, std::add_lvalue_reference_t<RaycastHit> hit_info) {
			return Memory::FUNCTION_CAST<bool, Vector3, Vector3, std::add_lvalue_reference_t<RaycastHit>>(Offsets::Methods::Physics::Linecast, start, end, hit_info);
		}
	};

	class Transform {
	public:
		static Vector3 GetPosition(std::add_pointer_t<Transform> instance) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Transform>>(Offsets::Methods::Transform::GetPosition, instance);
		}

		static Vector3 GetRight(std::add_pointer_t<Transform> instance) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Transform>>(Offsets::Methods::Transform::GetRight, instance);
		}

		static Vector3 GetUp(std::add_pointer_t<Transform> instance) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Transform>>(Offsets::Methods::Transform::GetUp, instance);
		}

		static Vector3 GetForward(std::add_pointer_t<Transform> instance) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Transform>>(Offsets::Methods::Transform::GetForward, instance);
		}

		static Vector3 GetLocalScale(std::add_pointer_t<Transform> instance) {
			return Memory::FUNCTION_CAST<Vector3, std::add_pointer_t<Transform>>(Offsets::Methods::Transform::GetLocalScale, instance);
		}
	};

	class GameObject {
	public:
		static std::add_pointer_t<Transform> GetTransform(std::add_pointer_t<GameObject> instance) {
			return Memory::FUNCTION_CAST<std::add_pointer_t<Transform>, std::add_pointer_t<GameObject>>(Offsets::Methods::GameObject::GetTransform, instance);
		}
	};
}