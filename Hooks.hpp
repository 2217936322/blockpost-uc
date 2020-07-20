#pragma once

class Hooks {
public:
	VOID Initialize() const;
	VOID Release() const;
private:
	static DWORD WINAPI HookDirectX11();
	static HRESULT WINAPI HookPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);
	static HRESULT WINAPI HookResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static VOID Update(LPVOID instance);
	static VOID OnGUI(LPVOID instance);
	static BOOL GetKeyUp(std::int32_t key);
	static BOOL Raycast(Vector3 pos, Vector3 dir, UnityEngine::RaycastHit& hit, float dist);

	static LRESULT CALLBACK WndProc(const HWND Window, UINT MSG_TYPE, WPARAM WPARAM, LPARAM LPARAM);

	STATIC_INLINE VOID GetImmediateContextFromSwapChain(IDXGISwapChain* SwapChain) {
		if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<LPVOID*>(&Hooks::DX11Device))))
			DX11Device->GetImmediateContext(&Hooks::DX11DeviceContext);
	}

	STATIC_INLINE VOID CreateRenderTargetView(IDXGISwapChain* SwapChain, ID3D11Texture2D* RenderTargetTexture = nullptr) {
		if (SUCCEEDED(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture))))
		{
			Hooks::DX11Device->CreateRenderTargetView(RenderTargetTexture, nullptr, &Hooks::DX11RenderTargetView);
			RenderTargetTexture->Release();
		}
	}

	STATIC_INLINE ID3D11RenderTargetView* DX11RenderTargetView = nullptr;
	STATIC_INLINE ID3D11Device* DX11Device = nullptr;
	STATIC_INLINE ID3D11DeviceContext* DX11DeviceContext = nullptr;

	STATIC_INLINE ID3D11Device* CreateDEVICEDX11Device = nullptr;
	STATIC_INLINE ID3D11DeviceContext* CreateDEVICEDX11DeviceContext = nullptr;
	STATIC_INLINE IDXGISwapChain* SwapChain = nullptr;

	STATIC_INLINE WNDPROC WND_PROC = nullptr;
	STATIC_INLINE HWND GAME_HWND = nullptr;

	STATIC_INLINE std::add_pointer_t<VOID CDECL(LPVOID instance)> Original_Update = nullptr;
	STATIC_INLINE std::add_pointer_t<VOID CDECL(LPVOID instance)> Original_OnGUI = nullptr;
	STATIC_INLINE std::add_pointer_t<BOOL CDECL(std::int32_t key)> Original_GetKeyUp = nullptr;
	STATIC_INLINE std::add_pointer_t<BOOL CDECL(Vector3 pos, Vector3 dir, UnityEngine::RaycastHit& hit, float dist)> Original_Raycast = nullptr;

	STATIC_INLINE std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)> Original_D3D11Present = nullptr;
	STATIC_INLINE std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)> Original_D3D11ResizeBuffers = nullptr;
};

inline std::unique_ptr<const Hooks> GameHooks;