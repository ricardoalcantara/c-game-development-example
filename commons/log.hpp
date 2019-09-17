// #define USE_SPDLOG
#ifdef USE_SPDLOG
#include <spdlog/spdlog.h>
#define LOG_INIT()              spdlog::set_level(spdlog::level::debug);
#define LOG_INFO(...)           spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...)          spdlog::debug(__VA_ARGS__)
#define LOG_ERROR(...)          spdlog::error(__VA_ARGS__)
#else
#include <fmt/core.h>
#include <iostream>
#define LOG_INIT()
#define LOG_INFO(...)                std::cout << "[INFO] " << fmt::format(__VA_ARGS__) << std::endl;
#define LOG_DEBUG(...)               std::cout << "[DEBUG] " << fmt::format(__VA_ARGS__) << std::endl;
#define LOG_ERROR(...)               std::cerr << "[ERROR] " << fmt::format(__VA_ARGS__) << std::endl;
#endif