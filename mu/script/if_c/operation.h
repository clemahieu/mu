#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace if_c
		{
			class operation : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::wstring name () override;
			};
		}
	}
}
