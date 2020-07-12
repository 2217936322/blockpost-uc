#include <Includes.h>

DWORD WINAPI Main() {
	//Utils::InitConsole("internal-blockpost");

	GameMemory = std::make_unique<const Memory>();
	GameHooks = std::make_unique<const Hooks>();
	GameManager = std::make_unique<Manager>();

	GameHooks->Initialize();

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID reserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: std::thread(Main).detach(); break;
	case DLL_PROCESS_DETACH: GameHooks->Release(); break;
	}
	return TRUE;
}