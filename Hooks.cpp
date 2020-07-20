#include <Includes.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND Window, UINT MSG_TYPE, WPARAM WPARAM, LPARAM LPARAM);

LRESULT Hooks::WndProc(const HWND Window, UINT MSG_TYPE, WPARAM WPARAM, LPARAM LPARAM) {
	if (MSG_TYPE == WM_KEYDOWN && LOWORD(WPARAM) == VK_INSERT) Menu::Open = !Menu::Open;

	if (ImGui_ImplWin32_WndProcHandler(Window, MSG_TYPE, WPARAM, LPARAM)) return true;

	return CallWindowProc(Hooks::WND_PROC, Window, MSG_TYPE, WPARAM, LPARAM);
}

HRESULT WINAPI Hooks::HookPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
	if (!Hooks::DX11Device || !Hooks::DX11DeviceContext)
	{
		ImGui::CreateContext();

		Hooks::GetImmediateContextFromSwapChain(SwapChain);

		if (Hooks::DX11Device && Hooks::DX11DeviceContext) {
			Hooks::CreateRenderTargetView(SwapChain);

			ImGui_ImplWin32_Init(Hooks::GAME_HWND);
			ImGui_ImplDX11_Init(Hooks::DX11Device, Hooks::DX11DeviceContext);

			ImGui::StyleColorsDark();

			if (!Hooks::WND_PROC) Hooks::WND_PROC = WNDPROC(SetWindowLongPtrA(Hooks::GAME_HWND, GWLP_WNDPROC, LONG_PTR(Hooks::WndProc)));
		}
	}

	if (!Hooks::DX11Device || !Hooks::DX11DeviceContext) return Hooks::Original_D3D11Present(SwapChain, SyncInterval, Flags);

	Resolution ScreenResolution = {
		static_cast<std::int32_t>(ImGui::GetIO().DisplaySize.x * ImGui::GetIO().DisplayFramebufferScale.x),
		static_cast<std::int32_t>(ImGui::GetIO().DisplaySize.y * ImGui::GetIO().DisplayFramebufferScale.y)
	};

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Menu::Render();

	if (Config::Aimbot::DrawFov && UnityEngine::Client::IsConnected())
		Draw::Circle(Vector2{ ScreenResolution.width / 2.f, ScreenResolution.height / 2.f }, Config::Aimbot::Fov, UnityEngine::Color{ 255.f, 255.f, 255.f, 255.f }, 180);

	Hooks::DX11DeviceContext->OMSetRenderTargets(1, &Hooks::DX11RenderTargetView, nullptr);
	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return Hooks::Original_D3D11Present(SwapChain, SyncInterval, Flags);
}

HRESULT WINAPI Hooks::HookResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	Memory::SAFE_RELEASE(Hooks::DX11RenderTargetView);

	const HRESULT result = Hooks::Original_D3D11ResizeBuffers(SwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	Hooks::CreateRenderTargetView(SwapChain);

	return result;
}

DWORD WINAPI Hooks::HookDirectX11()
{
	while (!FindWindowA("UnityWndClass", "BLOCKPOST")) std::this_thread::sleep_for(std::chrono::milliseconds(1));

	Hooks::GAME_HWND = FindWindowA("UnityWndClass", "BLOCKPOST");

	D3D_FEATURE_LEVEL D3DLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 }, ObtainedLevel;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	{
		ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDesc.OutputWindow = Hooks::GAME_HWND;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.Windowed = true;
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		SwapChainDesc.BufferDesc.Width = UnityEngine::Screen::GetResolution().width;
		SwapChainDesc.BufferDesc.Height = UnityEngine::Screen::GetResolution().height;
	}

	HRESULT DeviceAndSwapChain = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		FALSE, D3DLevels,
		sizeof(D3DLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&SwapChainDesc, &Hooks::SwapChain,
		&Hooks::CreateDEVICEDX11Device,
		&ObtainedLevel,
		&Hooks::CreateDEVICEDX11DeviceContext);

	if (FAILED(DeviceAndSwapChain))
		Utils::EXIT_FAILURE_WITH_MSG("Failed to create device and swapchain");

	std::uintptr_t* SwapChainVTable = reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t*>(Hooks::SwapChain)[0]);

	if (MH_CreateHook(reinterpret_cast<LPVOID>(SwapChainVTable[8]), &Hooks::HookPresent, reinterpret_cast<LPVOID*>(&Hooks::Original_D3D11Present)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("DX11 Present Hook Error");

	if (MH_CreateHook(reinterpret_cast<LPVOID>(SwapChainVTable[13]), &Hooks::HookResizeBuffers, reinterpret_cast<LPVOID*>(&Hooks::Original_D3D11ResizeBuffers)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("DX11 ResizeBuffers Hook Error");

	return S_OK;
}

VOID Hooks::Update(LPVOID instance) {
	Hooks::Original_Update(instance);

	GameManager->DisableInput(Menu::Open);
	Aimbot::Run();
	Misc::Run();
}

VOID Hooks::OnGUI(LPVOID instance) {
	Hooks::Original_OnGUI(instance);

	ESP::Run();
}

BOOL Hooks::GetKeyUp(std::int32_t key) {
	return key == Enums::KeyCode::Insert ? false : Hooks::Original_GetKeyUp(key); // The best anti-cheat in the world
}

BOOL Hooks::Raycast(Vector3 pos, Vector3 dir, UnityEngine::RaycastHit& hit, float dist) {
	if (!Aimbot::Target && Config::Misc::HitDistanceLimit)
		dist = INFINITY;

	if (Config::Aimbot::Silent && Aimbot::Target)
		pos = Aimbot::Target;

	return Hooks::Original_Raycast(pos, dir, hit, dist);
}

VOID Hooks::Initialize() const
{
	if (MH_Initialize() != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MH Initialize Error");

	if (MH_CreateHook(Offsets::Hooks::Update, &Hooks::Update, reinterpret_cast<LPVOID*>(&Hooks::Original_Update)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::Update Error");

	if (MH_CreateHook(Offsets::Hooks::GUI, &Hooks::OnGUI, reinterpret_cast<LPVOID*>(&Hooks::Original_OnGUI)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::OnGUI Error");

	if (MH_CreateHook(Offsets::Hooks::GetKeyUp, &Hooks::GetKeyUp, reinterpret_cast<LPVOID*>(&Hooks::Original_GetKeyUp)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::GetKeyUp Error");

	if (MH_CreateHook(Offsets::Hooks::Raycast, &Hooks::Raycast, reinterpret_cast<LPVOID*>(&Hooks::Original_Raycast)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::Raycast Error");

	Hooks::HookDirectX11();

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MH Enable Error");
}

VOID Hooks::Release() const
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Memory::SAFE_RELEASE(Hooks::DX11Device);
	Memory::SAFE_RELEASE(Hooks::DX11DeviceContext);

	SetWindowLongPtrA(Hooks::GAME_HWND, GWLP_WNDPROC, LONG_PTR(Hooks::WND_PROC));

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
