#pragma once

#include <mu/script_runtime/operation.h>

namespace mu
{
	namespace script_test
	{
		namespace chain
		{
			class ten_count : public mu::script_runtime::operation
			{
			public:
				ten_count ();
				bool operator () (mu::script_runtime::context & context_a) override;
				size_t count_m;
			};
		}
	}
}
