#pragma once

#include <mu/script/debugging/operation_info.h>
#include <mu/core/context.h>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class source_info : public mu::script::debugging::operation_info
			{
			public:
				source_info (mu::core::context context_a);
				std::wstring stacktrace_line () override;
				mu::core::context context;
			};
		}
	}
}