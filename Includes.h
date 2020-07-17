#pragma once

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS 1

#include <MinHook/MinHook.h>

#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include <thread>
#include <cstddef>
#include <Psapi.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

#include <Utils.hpp>
#include <Memory.hpp>

#include <SDK/Offsets.hpp>
#include <SDK/System.hpp>
#include <SDK/Vector.hpp>
#include <SDK/UnityEngine.hpp>
#include <SDK/Controll.hpp>
#include <SDK/PLH.hpp>
#include <SDK/Manager.hpp>
#include <SDK/Draw.hpp>

#include <Config.hpp>
#include <Menu.hpp>

#include <Cheats/Aimbot.hpp>
#include <Cheats/ESP.hpp>

#include <Hooks.hpp>