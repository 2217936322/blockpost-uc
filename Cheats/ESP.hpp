#pragma once

class ESP {
public:
	static void Run() {
		if (!Config::ESP::Enabled) return;

		Controll_StaticFields* GameControll = GameManager->GetGameControll();
		if (!GameControll) return;
		if (!GameControll->local_player) return;

		ESP::Players = GameManager->GetPlayers();

		for (size_t i = 0; i < ESP::Players.size(); i++)
		{
			PlayerData* Player = ESP::Players[i];

			if (!GameManager->TeamCheck(Player)) continue;
			if (Player->idx == GameControll->local_player->idx) continue;
			if (Player->health <= 10) continue;

			Vector3 OriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, Player->current_pos);
			if (OriginW2S.z < 1.f) continue;

			Resolution Resolution = UnityEngine::Screen::GetResolution();
			if (!Resolution) continue;

			Vector3 Origin, OriginTextPosition;
			Origin = OriginTextPosition = Player->current_pos;
			Origin.y += 0.7f;
			OriginTextPosition.y += 0.75f;

			if (Config::ESP::Box) {
				Vector3 BoxOriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, Origin);
				if (BoxOriginW2S.z < 1.f) continue;

				float CalculateBox = abs(BoxOriginW2S.y - OriginW2S.y) * 4.f;
				float CalculateBoxWidth = CalculateBox * 0.65f;

				UnityEngine::GUIM::DrawBoxBorder(UnityEngine::Rect{
					BoxOriginW2S.x - CalculateBoxWidth / 2.f, Resolution.height - BoxOriginW2S.y,
					CalculateBoxWidth, CalculateBox
					}, UnityEngine::Texture::GenerateTexture(Config::ESP::BoxColor, nullptr), 350.f);
			}

			if (Config::ESP::Name) {
				Vector3 TextOriginW2S = UnityEngine::Camera::WorldToScreen(GameControll->camera, OriginTextPosition);
				TextOriginW2S.y = Resolution.height - TextOriginW2S.y;

				UnityEngine::GUIM::DrawTextColor(UnityEngine::Rect{
						TextOriginW2S.x - UnityEngine::GUIM::YRES(100.f), TextOriginW2S.y - UnityEngine::GUIM::YRES(20.f),
						UnityEngine::GUIM::YRES(200.f), UnityEngine::GUIM::YRES(20.f)
					}, Player->name, 7, 1, 1, 10, true);
			}
		}
	}
private:
	static inline std::vector<PlayerData*> Players{};
};