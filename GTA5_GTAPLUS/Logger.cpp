#include "pch.h"
#include "Logger.hpp"

namespace base
{
    void log::attach()
    {
        init_console_handles();
        g_log.send("Log", "Attached");
    }

    void log::detach()
    {
        g_log.send("Log", "Detached");
        free_console_handles();
    }

    void log::init_console_handles()
    {
        if (!AttachConsole(GetCurrentProcessId()))
            AllocConsole();

        SetConsoleTitleA("GTA5");

        FILE* file = nullptr;
        freopen_s(&file, "CONOUT$", "w", stdout);

        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);

        std::this_thread::sleep_for(std::chrono::milliseconds(40));

        m_console_hwnd = FindWindowA(nullptr, "GTA5");

        m_console.open("CONOUT$");
    }

    void log::free_console_handles()
    {
        if (m_console.is_open())
            m_console.close();

        fclose(stdout);
        FreeConsole();
    }
}
