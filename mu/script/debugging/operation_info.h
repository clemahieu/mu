#pragma once

#include <string>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class operation_info
			{
			public:
				virtual ~operation_info ();
				virtual std::wstring stacktrace_line () = 0;
			};
		}
	}
}