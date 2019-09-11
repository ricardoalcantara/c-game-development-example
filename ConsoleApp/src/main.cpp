#include "log.hpp"

int main(int argc, char const *argv[])
{
    LOG_INFO("Hello, {}!\n", "world");  // Python-like format string syntax
    LOG_INFO("Hello, {}!\n", "world");  // Python-like format string syntax

    return 0;
}
