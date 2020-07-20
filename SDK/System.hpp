#pragma once

class SystemString {
public:
	std::byte pad[8];
	std::int32_t StringLength;

	std::wstring String() const {
		return std::wstring(this->UnicodeString);
	};

	static std::shared_ptr<SystemString> CreateString(std::wstring UnicodeString) {
		std::shared_ptr<SystemString> SystemStringPTR = std::make_unique<SystemString>();

		SystemStringPTR->StringLength = UnicodeString.length();
		wcscpy(SystemStringPTR->UnicodeString, UnicodeString.c_str());

		return SystemStringPTR;
	};

private:
	wchar_t UnicodeString[256];
};