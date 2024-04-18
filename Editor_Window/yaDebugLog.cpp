#include "yaDebugLog.h"

#include <iostream>
#include <string>
#include <codecvt>

namespace ya 
{
    std::wstring DebugLog::mDebugLog = L"START";

    const std::wstring& DebugLog::GetDebugLog()
    {
        return mDebugLog;
    }

    void DebugLog::PrintDebugLog(const std::wstring& message)
    {
        mDebugLog = message;
    }
}