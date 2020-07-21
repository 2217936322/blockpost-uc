#pragma once

class ControllKlass;
class PLHKlass;

#define STATIC_INLINE static inline

#define IL2CPP_ARRAY_MAX_SIZE 65535

#define VALIDPAGE_START 0x10000
#define VALIDPAGE_END 0x7FFFFFFF

#define GameAssembly GetModuleHandleA("GameAssembly")

class Memory {
public:
	Memory() {
		this->Controll	= Memory::FindKlass<ControllKlass>("Controll");
		this->PLH		= Memory::FindKlass<PLHKlass>("PLH");
	};

	static constexpr auto MAKE_RVA = [](std::uintptr_t address) -> std::uintptr_t
	{
		return reinterpret_cast<std::uintptr_t>(GameAssembly) + address;
	};

	template <class T> static constexpr auto MAKE_RVA_PTR = [](std::uintptr_t address) -> T*
	{
		T* RVAddress = reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(GameAssembly) + address);

		if (!RVAddress)
			Utils::EXIT_FAILURE_WITH_MSG("Wrong RVA (outdated?)");

		return RVAddress;
	};

	template <class T> static T* FindKlass(const std::string& KlassName) { // from github@rexyrexy
		auto IsValidPage = [](std::uint32_t Pointer) -> bool {
			if (Pointer < VALIDPAGE_START || Pointer > VALIDPAGE_END) return false;

			std::unique_ptr<MEMORY_BASIC_INFORMATION> MEMORY_INFORMATION = std::make_unique<MEMORY_BASIC_INFORMATION>();

			if (!VirtualQuery(reinterpret_cast<void*>(Pointer), MEMORY_INFORMATION.get(), sizeof(MEMORY_BASIC_INFORMATION))) return false;

			return MEMORY_INFORMATION->Protect > PAGE_NOACCESS;
		};

		PIMAGE_SECTION_HEADER DataSection = nullptr, NextDataSection = nullptr;

		static std::uintptr_t GameAssemblyAddress = reinterpret_cast<std::uintptr_t>(GameAssembly);

		PIMAGE_NT_HEADERS NT_HEADERS = reinterpret_cast<PIMAGE_NT_HEADERS>(GameAssemblyAddress + reinterpret_cast<PIMAGE_DOS_HEADER>(GameAssemblyAddress)->e_lfanew);
		PIMAGE_SECTION_HEADER SECTION_HEADER = IMAGE_FIRST_SECTION(NT_HEADERS);

		for (; SECTION_HEADER; ++SECTION_HEADER)
			if (!std::strcmp(reinterpret_cast<const char*>(SECTION_HEADER->Name), ".data")) {
				DataSection = SECTION_HEADER;
				NextDataSection = SECTION_HEADER + 1;
				break;
			}

		if (!DataSection || !NextDataSection) return nullptr;

		DWORD DataBase = GameAssemblyAddress + DataSection->VirtualAddress;
		DWORD DataSize = NextDataSection->VirtualAddress - DataSection->VirtualAddress - sizeof(uintptr_t);

		for (size_t Offset = DataSize; Offset; Offset -= sizeof(uintptr_t)) {
			DWORD CurrentData = DataBase + Offset;

			std::uint32_t Klass = *reinterpret_cast<std::uint32_t*>(CurrentData);
			if (!Klass) continue;
			if (!IsValidPage(Klass)) continue;

			std::uint32_t KlassNamePtr = *reinterpret_cast<std::uint32_t*>(Klass + 0x8);
			if (!KlassNamePtr) continue;
			if (!IsValidPage(KlassNamePtr)) continue;

			if (!std::strcmp(reinterpret_cast<const char*>(KlassNamePtr), KlassName.c_str())) {
				std::printf("%s: %p\n", KlassName.c_str(), reinterpret_cast<T*>(Klass));
				return reinterpret_cast<T*>(Klass);
			}
		}

		Utils::EXIT_FAILURE_WITH_MSG(std::string{ KlassName + " not found" });
		return nullptr;
	}

	template<typename T, typename... TypeArgs>
	static constexpr T FUNCTION_CAST(std::uintptr_t Offset, TypeArgs&... type_args) {
		return reinterpret_cast<T(*)(TypeArgs...)>(Offset)(std::forward<TypeArgs>(type_args)...);
	};

	template <class T> static VOID SAFE_RELEASE(T*& Pointer)
	{
		if (Pointer)
		{
			Pointer->Release();
			Pointer = nullptr;
		}
	}

	ControllKlass* Controll;
	PLHKlass* PLH;
};

inline std::unique_ptr<const Memory> GameMemory;