#pragma once
#include <string>

namespace ya
{
	class DebugLog
	{
	public:
		static const std::wstring& GetDebugLog();
		static void PrintDebugLog(const std::wstring& message);

	private:
		static std::wstring mDebugLog;
	};
}