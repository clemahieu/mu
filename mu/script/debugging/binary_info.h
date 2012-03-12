#pragma once

#include <mu/script/debugging/operation_info.h>

namespace mu
{
	namespace script
	{
		namespace debugging
		{
			class binary_info : public mu::script::debugging::operation_info
			{
			public:
				binary_info (std::type_info const & type_a);
				std::wstring stacktrace_line () override;
				std::type_info const & type;
			};
		}
	}
}