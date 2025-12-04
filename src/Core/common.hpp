#pragma once

#ifdef _WIN32
#define ISExport __declspec(dllexport)
#else
#define ISExport
#endif