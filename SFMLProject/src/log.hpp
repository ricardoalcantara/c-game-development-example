// #define LOG
#ifdef LOG
#include <spdlog/spdlog.h>
#define LOG_INIT()              spdlog::set_level(spdlog::level::debug);
#define LOG_INFO(...)           spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...)          spdlog::debug(__VA_ARGS__)
#define LOG_ERROR(...)          spdlog::error(__VA_ARGS__)
#else
#define LOG_INIT()
#define LOG_INFO
#define LOG_DEBUG
#define LOG_ERROR
#endif