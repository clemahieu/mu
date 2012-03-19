#pragma once

#include <mu/script_runtime/operation.h>

namespace mu
{
	namespace script
	{
		namespace print
		{
			class operation : public mu::script_runtime::operation
			{
			public:
				bool operator () (mu::script_runtime::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
