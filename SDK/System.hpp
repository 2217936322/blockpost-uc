#pragma once

class SystemString {
public:
	std::byte pad[8];
	std::int32_t StringLength;

	std::wstring String() const {
		return std::wstring(this->UnicodeString);
	};

private:
	wchar_t UnicodeString[TRUE];
};