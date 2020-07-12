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

		if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<LPVOID*>(&Hooks::DX11Device))))
			DX11Device->GetImmediateContext(&Hooks::DX11DeviceContext);

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		SwapChain->GetDesc(&SwapChainDesc);

		ImGui_ImplWin32_Init(SwapChainDesc.OutputWindow);

		ImGui::StyleColorsDark();

		Hooks::WND_PROC = WNDPROC(SetWindowLongPtrA(FindWindowA("UnityWndClass", "BLOCKPOST"), GWLP_WNDPROC, LONG_PTR(Hooks::WndProc)));
	}
	else
	{
		ID3D11Texture2D* RenderTargetTexture = nullptr;

		if (!Hooks::DX11RenderTargetView)
			if (SUCCEEDED(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture))))
			{
				Hooks::DX11Device->CreateRenderTargetView(RenderTargetTexture, nullptr, &Hooks::DX11RenderTargetView);
				RenderTargetTexture->Release();
			}
	}

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChain->GetDesc(&SwapChainDesc);

	DXGI_MODE_DESC BufferDesc = SwapChainDesc.BufferDesc;

	ImGui_ImplDX11_Init(Hooks::DX11Device, Hooks::DX11DeviceContext);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Menu::Render();

	if (Config::Aimbot::DrawFov && UnityEngine::Client::IsConnected())
		Draw::Circle(Vector2{ BufferDesc.Width / 2.f, BufferDesc.Height / 2.f }, Config::Aimbot::Fov, UnityEngine::Color{ 255.f, 255.f, 255.f, 255.f }, 180);

	Hooks::DX11DeviceContext->OMSetRenderTargets(1, &Hooks::DX11RenderTargetView, nullptr);
	ImGui::EndFrame();
	ImGui::Render();

	Memory::SAFE_RELEASE(Hooks::DX11RenderTargetView);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return Hooks::Original_D3D11Present(SwapChain, SyncInterval, Flags);
}

DWORD WINAPI Hooks::HookDirectX11()
{
	D3D_FEATURE_LEVEL D3DLevel = D3D_FEATURE_LEVEL_11_0, ObtainedLevel;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	{
		ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
		SwapChainDesc.BufferCount = 1;
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDesc.OutputWindow = FindWindowA("UnityWndClass", "BLOCKPOST");
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.Windowed = true;
		SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT DeviceAndSwapChain = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		FALSE, &D3DLevel, TRUE,
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

	return S_OK;
}

VOID Hooks::OnUpdate(LPVOID instance) {
	Hooks::Original_OnUpdate(instance);

	GameManager->DisableInput(Menu::Open);
	Aimbot::Run();
}

VOID Hooks::OnGUI(LPVOID instance) {
	Hooks::Original_OnGUI(instance);

	ESP::Run();
}

BOOL Hooks::GetKeyUp(std::int32_t key) {
	return key == Manager::KeyCode::Insert ? false : Hooks::Original_GetKeyUp(key); // The best anti-cheat in the world
}

VOID Hooks::Initialize() const
{
	if (MH_Initialize() != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MH Initialize Error");

	if (MH_CreateHook(Offsets::Hooks::Update, &Hooks::OnUpdate, reinterpret_cast<LPVOID*>(&Hooks::Original_OnUpdate)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::OnUpdate Error");

	if (MH_CreateHook(Offsets::Hooks::GUI, &Hooks::OnGUI, reinterpret_cast<LPVOID*>(&Hooks::Original_OnGUI)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::OnGUI Error");

	if (MH_CreateHook(Offsets::Hooks::GetKeyUp, &Hooks::GetKeyUp, reinterpret_cast<LPVOID*>(&Hooks::Original_GetKeyUp)) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("Hooks::GetKeyUp Error");

	Hooks::HookDirectX11();

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		Utils::EXIT_FAILURE_WITH_MSG("MH Enable Error");
}

VOID Hooks::Release() const
{
	Memory::SAFE_RELEASE(Hooks::DX11Device);
	Memory::SAFE_RELEASE(Hooks::DX11DeviceContext);
	Memory::SAFE_RELEASE(Hooks::SwapChain);

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
