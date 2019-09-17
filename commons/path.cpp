#include "path.hpp"

#if _WIN32
#include <windows.h>
#elif _LINUX
#include <limits.h>
#include <unistd.h>
#endif

std::string Path::GetExecutablePath()
{
    #if _WIN32
    char result[ 256 ];
    return std::string( result, GetModuleFileName(NULL, result, sizeof(result)));
    #elif _LINUX
    char result[ 256 ];
    ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
    return std::string(result, (count > 0) ? count : 0 );
    #endif
}

std::string Path::GetExecutableDir()
{
    const std::string path = GetExecutablePath();
    return path.substr(0, path.find_last_of("/"));
}