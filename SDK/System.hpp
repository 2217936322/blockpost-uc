#pragma once

class SystemString;

struct SystemString_StaticFields {
	SystemString* Empty;
};

class SystemStringKlass {
public:
	std::byte pad[92];
	SystemString_StaticFields* static_fields;
};

class SystemString {
public:
	SystemStringKlass* klass;
	void* monitor;
	std::int32_t StringLength;

	std::wstring String() const {
		return std::wstring(this->UnicodeString);
	};

	static inline std::unique_ptr<SystemString> CreateString(std::wstring unicode_str) {
		std::unique_ptr<SystemString> system_str = std::make_unique<SystemString>();

		system_str->klass = nullptr;
		system_str->monitor = nullptr;

		system_str->StringLength = unicode_str.length();
		wcscpy(system_str->UnicodeString, unicode_str.c_str());

		return system_str;
	}

private:
	wchar_t UnicodeString[TRUE];
};