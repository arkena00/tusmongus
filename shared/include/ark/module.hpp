#pragma once

#include <Windows.h>

namespace au
{
    class mod;
} // ark

using Module_load_ptr = int (*)(au::mod&);
using Module_unload_ptr = int (*)(au::mod&);

#define ark_os_module_function GetProcAddress
#define ark_os_module_load(path) LoadLibraryA(path)
#define ark_os_module_unload FreeLibrary
#define ark_os_sharelibext ".dll"

#define ARK_IMPORT __declspec(dllimport)
#define ARK_EXPORT __declspec(dllexport)

#define ARK_SHARED ARK_IMPORT