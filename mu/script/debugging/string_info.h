#pragma once

#include <mu/script/debugging/operation_info.h>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class string_info : public mu::script::debugging::operation_info
			{
			public:
				string_info (std::wstring string_a);
				std::wstring stacktrace_line () override;
				std::wstring string;
			};
		}
	}
}