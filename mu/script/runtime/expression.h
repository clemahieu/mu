#pragma once

#include <mu/script/operation.h>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class reference;
			class expression : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				std::vector <mu::script::operation *> dependencies;
			};
		}
	}
}