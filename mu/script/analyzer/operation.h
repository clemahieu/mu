#pragma once

#include <mu/script/operation.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class cluster;
        namespace errors
        {
            class error_target;
        }
	}
	namespace io
	{
		namespace ast
		{
			class cluster;
		}
	}
	namespace script
	{
		namespace cluster
		{
			class node;
		}
		namespace extensions
		{
			class node;
		}
		namespace analyzer
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				mu::core::cluster * core (mu::script::context & context_a, mu::io::ast::cluster * ast);
				void build (mu::core::cluster ** result_a, mu::core::cluster * cluster_a);
			};
		}
	}
}
