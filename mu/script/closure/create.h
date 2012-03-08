#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class create : public mu::script::fixed
			{
			public:
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::wstring name () override;
			};
		}
	}
}