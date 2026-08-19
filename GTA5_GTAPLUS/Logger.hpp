#pragma once

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <format>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>
#include <cstdio>

#pragma warning(disable : 4996)

namespace base
{
    class log
    {
    private:
        std::ofstream m_console{};
        HWND m_console_hwnd{};

    public:
        void attach();
        void detach();
        void init_console_handles();
        void free_console_handles();

    public:
        template <typename... arguments>
        void send(
            const std::string& title,
            const std::string& message,
            arguments&&... args)
        {
            auto get_time = std::time(nullptr);
            auto time_struct = std::localtime(&get_time);

            std::string messageS =
                std::format(
                    "[{:02}:{:02}:{:02}]",
                    time_struct->tm_hour,
                    time_struct->tm_min,
                    time_struct->tm_sec
                )
                + " [" + title + "] "
                + std::vformat(
                    message,
                    std::make_format_args(args...)
                );

            m_console << messageS << std::endl;
        }
    };
    inline log g_log;
}
