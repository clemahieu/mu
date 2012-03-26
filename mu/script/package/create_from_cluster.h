#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace package
		{
			class create_from_cluster : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
			};
		}
	}
}

