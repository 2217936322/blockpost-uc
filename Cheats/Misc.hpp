#pragma once

class Misc {
public:
	static void Run() {
		Misc::CustomCameraFOV();
	}

private:
	static void CustomCameraFOV() {
		Controll_StaticFields* GameControll = GameManager->GetGameControll();

		if (GameControll)
			if (GameControll->camera)
				if (!Config::Misc::CameraFov) {
					Config::Misc::CameraFov = UnityEngine::Camera::FieldOfView(GameControll->camera);
				}
				else
					UnityEngine::Camera::SetFieldOfView(GameControll->camera, Config::Misc::CameraFov);
	}
};