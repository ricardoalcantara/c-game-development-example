#ifndef PATH_H
#define PATH_H

#include <string>


class Path
{
public:
    static std::string GetExecutablePath();
    static std::string GetExecutableDir();
};
#endif