#include <Main.h>

std::add_pointer_t<void _cdecl(Controll* _inst)> ControllUpdate = nullptr;
std::add_pointer_t<void _cdecl(Controll* _inst)> ControllGUI = nullptr;

VOID Controll__Update(Controll* inst) {
	ControllUpdate(inst);

	Aimbot::Run();
}

VOID Controll__GUI(Controll* inst) {
	ControllGUI(inst);

	ESP::Run();
}

DWORD WINAPI Main() {
	Utils::InitConsole("internal-blockpost");

	GameMemory = std::make_unique<const Memory>();
	GameManager = std::make_unique<Manager>();

	if (MH_Initialize() != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MinHook Initialize Error");

	if (MH_CreateHook(Offsets::Hooks::Update, &Controll__Update, reinterpret_cast<LPVOID*>(&ControllUpdate)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Controll__Update Hook Error");

	if (MH_CreateHook(Offsets::Hooks::GUI, &Controll__GUI, reinterpret_cast<LPVOID*>(&ControllGUI)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Controll__GUI Hook Error");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MinHook EnableHook Error");

	return TRUE;
}

VOID WINAPI HooksRelease() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID reserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: std::thread(Main).detach(); break;
	case DLL_PROCESS_DETACH: HooksRelease(); break;
	}
	return TRUE;
}