#pragma once

#include <mu/script/operation.h>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace values
		{
			class operation : public mu::script::operation
			{
			public:
				operation ();
				operation (std::vector <mu::core::node *> values_a);
				bool operator () (mu::script::context & context_a) override;
				std::vector <mu::core::node *> values;
			};
		}
	}
}
