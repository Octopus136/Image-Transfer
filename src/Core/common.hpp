#pragma once

#ifdef _WIN32
#define ITExport __declspec(dllexport)
#else
#define ITExport
#endif