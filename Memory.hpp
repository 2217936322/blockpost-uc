#pragma once

class Controll;
class PLH;

class Memory {
public:
	Memory() {
		this->ClassControll = Memory::MAKE_RVA_PTR<Controll*>(0xB2D7B8);
		this->ClassPLH = Memory::MAKE_RVA_PTR<PLH*>(0xB2D824);
	};

	static constexpr auto MAKE_RVA = [](std::uintptr_t address) -> std::uintptr_t
	{
		return reinterpret_cast<std::uintptr_t>(GetModuleHandleA("GameAssembly")) + address;
	};

	template <typename T>
	static constexpr auto MAKE_RVA_PTR = [](std::uintptr_t address) -> T
	{
		T RVAddress = reinterpret_cast<T>(reinterpret_cast<std::uintptr_t>(GetModuleHandleA("GameAssembly")) + address);

		if (!RVAddress)
			Utils::EXIT_FAILURE_WITH_MSG("Wrong RVA (outdated?)");

		return RVAddress;
	};

	Controll* ClassControll;
	PLH* ClassPLH;
};

inline std::unique_ptr<const Memory> GameMemory;