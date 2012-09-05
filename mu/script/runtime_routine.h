#pragma once

#include <mu/script/operation.h>

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
			class definite_expression;
			class routine : public mu::script::operation
			{
			public:
				routine ();
				bool operator () (mu::script::context & context_a) override;
				mu::vector <mu::script::runtime::definite_expression *> expressions;
			};
		}
	}
}