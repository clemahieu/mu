#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script_test
	{
		namespace chain
		{
			class ten_count : public mu::script::operation
			{
			public:
				ten_count ();
				bool operator () (mu::script::context & context_a) override;
				size_t count_m;
			};
		}
	}
}
