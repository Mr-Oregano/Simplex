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
    static void Init(const std::string &name);
    static void Shutdown();

    static const auto& Get() { return logger; }
};