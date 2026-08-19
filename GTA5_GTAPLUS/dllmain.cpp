// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "sigscan.h"
#include "script_global.h"

int* m_bypass_gta_plus;
bool* m_is_session_started;

DWORD Mainthread(LPVOID lp)
{
    pattern_batch main_batch;
    main_batch.add("script_globals", "48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8", [=](ptr_manage ptr)
    {
        m_script_globals = ptr.add(7).add(3).rip().as<std::int64_t**>();
    });
    main_batch.add("bypass_gta_plus", "48 8D 15 ? ? ? ? 41 B8 18 02 00 00 E8", [=](ptr_manage ptr)
    {
        m_bypass_gta_plus = ptr.add(3).rip().as<int*>();
    });
    main_batch.add("is_session_started", "0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A", [=](ptr_manage ptr)
    {
        m_is_session_started = ptr.add(3).rip().as<bool*>();
    });
    main_batch.run();
    while (true)
    {
        if (*m_is_session_started)
        {
            *script_global(1970586).as<int*>() = 1;
            *m_bypass_gta_plus = 0;
        }
    }
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, static_cast<LPTHREAD_START_ROUTINE>(Mainthread), hModule, NULL, NULL);
        break;
    }
    return TRUE;
}

