#pragma once

class Hooks {
public:
	VOID Initialize() const;
	VOID Release() const;
private:
	static DWORD WINAPI HookDirectX11();
	static HRESULT WINAPI HookPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);
	static VOID OnUpdate(LPVOID instance);
	static VOID OnGUI(LPVOID instance);
	static BOOL GetKeyUp(std::int32_t key);

	static LRESULT CALLBACK WndProc(const HWND Window, UINT MSG_TYPE, WPARAM WPARAM, LPARAM LPARAM);

	static inline ID3D11RenderTargetView* DX11RenderTargetView = nullptr;
	static inline ID3D11Device* DX11Device = nullptr;
	static inline ID3D11DeviceContext* DX11DeviceContext = nullptr;

	static inline ID3D11Device* CreateDEVICEDX11Device = nullptr;
	static inline ID3D11DeviceContext* CreateDEVICEDX11DeviceContext = nullptr;
	static inline IDXGISwapChain* SwapChain = nullptr;

	static inline WNDPROC WND_PROC = nullptr;
	static inline HWND GAME_HWND = nullptr;

	static inline std::add_pointer_t<VOID CDECL(LPVOID instance)> Original_OnUpdate = nullptr;
	static inline std::add_pointer_t<VOID CDECL(LPVOID instance)> Original_OnGUI = nullptr;
	static inline std::add_pointer_t<BOOL CDECL(std::int32_t key)> Original_GetKeyUp = nullptr;

	static inline std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)> Original_D3D11Present = nullptr;
};

inline std::unique_ptr<const Hooks> GameHooks;