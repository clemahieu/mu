#pragma once

#include <mu/script/operation.h>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace topology
		{
			class node;
		}
		namespace runtime
		{
			class expression;
			class routine : public mu::script::operation
			{
			public:
				routine (mu::script::runtime::expression * parameters_a);
				bool operator () (mu::script::context & context_a) override;
				mu::script::runtime::expression * parameters;
				std::vector <mu::script::runtime::expression *> expressions;
			};
		}
	}
}