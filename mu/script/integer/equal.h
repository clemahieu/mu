#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace integer
		{
			class equal : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				std::wstring name () override;
				size_t count () override;
			};
		}
	}
}