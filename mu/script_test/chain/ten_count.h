#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script_test
	{
		namespace chain
		{
			class ten_count : public mu::script::fixed
			{
			public:
				ten_count ();
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				size_t count_m;
			};
		}
	}
}
