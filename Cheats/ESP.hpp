#pragma once

class ESP {
public:
	static void Run() {
		if (!Config::ESP::Enabled) return;

		Controll_StaticFields* GameControll = GameManager->GetGameControll();
		if (!GameControll) return;
		if (!GameControll->local_player || !GameControll->camera || !GameControll->transform_cam) return;

		Resolution Resolution = UnityEngine::Screen::GetResolution();
		if (!Resolution) return;

		if (!ESP::BoxTexture) ESP::BoxTexture = UnityEngine::Texture::GenerateTexture(ESP::BoxColor, SystemString::CreateString(std::wstring{ L"ESPColor" }).get());

		ESP::Players = GameManager->GetPlayers();

		for (const auto& Player : ESP::Players)
		{
			if (!GameManager->TeamCheck(Player) || Player->idx == GameControll->local_player->idx || Player->health <= 10) continue;

			Vector3 OriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, Player->current_pos);
			if (OriginW2S.z < 1.f) continue;

			Vector3 Origin, OriginTextPosition;
			Origin = OriginTextPosition = Player->current_pos;

			Origin.y += 0.7f; OriginTextPosition.y += 0.85f;

			UnityEngine::GameObject* GameObject = nullptr;

			switch (Config::Aimbot::Bone)
			{
			case Enums::Bones::HEAD: GameObject = Player->head_bone; break;
			case Enums::Bones::CHEST: GameObject = Player->chest_bone; break;
			default: GameObject = Player->head_bone; break;
			}

			std::vector<Vector3> EdgesOfBone = GameManager->EdgesOfAnObject(GameObject);
			if (EdgesOfBone.empty()) continue;

			bool LineOfSight = GameManager->MultipleLineOfSight(EdgesOfBone, UnityEngine::Transform::GetPosition(GameControll->transform_cam));

			if (Config::ESP::Visible && !LineOfSight) continue;

			if (!Player->spawnprotect && !LineOfSight)
				ESP::BoxColor = Config::ESP::Colors::Box;
			else if (Player->spawnprotect)
				ESP::BoxColor = Config::ESP::Colors::SpawnProtectBox;
			else if (LineOfSight)
				ESP::BoxColor = Config::ESP::Colors::VisibleBox;

			GameManager->ChangeTextureColor(ESP::BoxTexture, ESP::BoxColor);

			if (Config::ESP::Box) {
				Vector3 BoxOriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, Origin);
				if (BoxOriginW2S.z < 1.f) continue;

				float CalculateBox = abs(BoxOriginW2S.y - OriginW2S.y) * 4.f, CalculateBoxWidth = CalculateBox * 0.60f;

				UnityEngine::GUIM::DrawBoxBorder(UnityEngine::Rect{
					BoxOriginW2S.x - CalculateBoxWidth / 2.f, Resolution.height - BoxOriginW2S.y,
					CalculateBoxWidth, CalculateBox
					}, ESP::BoxTexture, ESP::BoxColor.a);
			}

			if (Config::ESP::Name) {
				Vector3 TextOriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, OriginTextPosition);
				TextOriginW2S.y = Resolution.height - TextOriginW2S.y;

				UnityEngine::GUIM::DrawTextColor(UnityEngine::Rect{
						TextOriginW2S.x - UnityEngine::GUIM::YRES(100.f), TextOriginW2S.y - UnityEngine::GUIM::YRES(20.f),
						UnityEngine::GUIM::YRES(200.f), UnityEngine::GUIM::YRES(20.f)
					}, Player->name, 7, 1, 1, 8, true);
			}
		}
	}
private:
	STATIC_INLINE std::vector<PlayerData*> Players{};
	STATIC_INLINE UnityEngine::Texture* BoxTexture = nullptr;
	STATIC_INLINE UnityEngine::Color BoxColor{ 0.f, 0.f, 0.f, 0.f };
};