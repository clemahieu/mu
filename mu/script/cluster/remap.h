#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace core
	{
		class cluster;
		class routine;
		class expression;
		class reference;
	}
	namespace script
	{
		namespace cluster
		{
			class remap : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				void operator () (mu::core::cluster * source, mu::core::cluster * target);
				void operator () (mu::core::routine * source, mu::core::routine * target);
				void operator () (mu::core::expression * source, mu::core::expression * target);
				void operator () (mu::core::reference * source, mu::core::reference * target);
				virtual mu::core::node * operator () (mu::core::node * node_a) = 0;
			};
		}
	}
}