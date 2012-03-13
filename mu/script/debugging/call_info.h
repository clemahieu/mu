#pragma once

#include <string>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class call_info
			{
			public:
				virtual ~call_info ();
				virtual std::wstring stacktrace_line () = 0;
			};
		}
	}
}