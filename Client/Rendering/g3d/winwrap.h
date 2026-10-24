#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOGDI
#define NOGDI
#endif

#include <functional>     // for std::binary_function, std::unary_function
#include <windows.h>
#include <G3D/System.h>
#include <objbase.h>