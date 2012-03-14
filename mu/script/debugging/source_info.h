#pragma once

#include <mu/script/debugging/call_info.h>
#include <mu/io/debugging/context.h>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class source_info : public mu::script::debugging::call_info
			{
			public:
				source_info (mu::io::debugging::context context_a);
				std::wstring stacktrace_line () override;
				mu::io::debugging::context context;
			};
		}
	}
}