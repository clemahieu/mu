#pragma once

#include <mu/core/visitor.h>

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class reference;
		class node;
		class expression;
	}
	namespace script
	{
		namespace topology
		{
			class node;
			class core : public mu::core::visitor
			{
			public:
				core (mu::core::expression * expression_a);
                void perform (mu::core::expression * expression_a);
				void operator () (mu::core::cluster * cluster_a) override;
				void operator () (mu::core::expression * expression_a) override;
				void operator () (mu::core::parameters * parameters_a) override;
				void operator () (mu::core::reference * reference_a) override;
				void operator () (mu::core::node * node_a) override;
				void operator () (mu::core::routine * routine_a) override;
				mu::core::node * current;
				std::set <mu::core::expression *, std::less <mu::core::expression *>, gc_allocator <mu::core::expression *>> already;
				std::set <mu::core::expression *, std::less <mu::core::expression *>, gc_allocator <mu::core::expression *>> path;
				mu::script::topology::node * topology;
				bool acyclic;
			};
		}
	}
}
