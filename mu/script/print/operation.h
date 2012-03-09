#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace print
		{
			class operation : public mu::script::operation
			{
			public:
				void operator () (mu::script::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
