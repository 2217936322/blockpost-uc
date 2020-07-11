#pragma once

class Il2CppClass;

struct VirtualInvokeData
{
    uintptr_t methodPtr;
    void* method;
};

struct Il2CppType
{
    void* data;
    unsigned int bits;
};

struct Il2CppObject
{
    Il2CppClass* klass;
    void* monitor;
};

struct Il2CppArrayBounds
{
    uintptr_t length;
    int32_t lower_bound;
};

class Il2CppClass_1
{
public:
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void* generic_class;
    void* typeDefinition;
    void* interopData;
    Il2CppClass* klass;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    void* interfaceOffsets;
};

class Il2CppClass_2
{
public:
    void* rgctx_data;
    Il2CppClass** typeHierarchy;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    uint64_t cctor_thread;
    int32_t genericContainerIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

class Il2CppClass
{
public:
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};