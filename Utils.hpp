#pragma once

namespace Utils {
	auto EXIT_FAILURE_WITH_MSG = [](const std::string msg) -> void {
		MessageBoxA(nullptr, msg.c_str(), "BLOCKPOST", MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	};

	auto InitConsole = [](const std::string console_title) -> bool {
		if (AllocConsole()) {
			FILE* pCout;
			freopen_s(&pCout, "CONOUT$", "w", stdout);
			SetConsoleTitleA(console_title.c_str());
			return true;
		}
		else
			return false;
	};
};