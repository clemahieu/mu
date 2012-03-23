#pragma once

#include <mu/script/operation.h>
#include <mu/core/visitor.h>

#include <map>

namespace mu
{
	namespace script
	{
		namespace cluster
		{
			class remap : public mu::script::operation, public mu::core::visitor
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				void operator () (mu::core::cluster * cluster_a) override;
				void operator () (mu::core::expression * expression_a) override;
				void operator () (mu::core::parameters * parameters_a) override;
				void operator () (mu::core::reference * reference_a) override;
				void operator () (mu::core::node * node_a) override;
				void operator () (mu::core::routine * routine_a) override;
				std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> mapping;
			};
		}
	}
}