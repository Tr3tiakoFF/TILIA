#include "Log.h"

namespace Tilia {
    
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
    
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("TILIA");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    inline std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
    {
        return s_CoreLogger;
    }
    inline std::shared_ptr<spdlog::logger>& Log::GetClientLogger()
    {
        return s_ClientLogger;
    }
}
