#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

#include <memory>
#include <string>

class Log
{
private:
    inline static std::shared_ptr<spdlog::logger> logger = nullptr;

public:
    static void Init();
    static void Shutdown();

    template<typename... Args>
    static void Info(const std::string &fmt, Args &&...args)
    {
        logger->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void Warn(const std::string &fmt, Args &&...args)
    {
        logger->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void Error(const std::string &fmt, Args &&...args)
    {
        logger->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void Critical(const std::string &fmt, Args &&...args)
    {
        logger->critical(fmt, std::forward<Args>(args)...);
    }
};