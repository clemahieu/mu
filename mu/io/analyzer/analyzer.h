#pragma once

#include <mu/io/debugging/context.h>
#include <mu/core/cluster.h>
#include <mu/io/ast/visitor.h>
#include <mu/io/analyzer/name_map.h>

#include <boost/function.hpp>

#include <set>

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
			class node;
		}
		namespace debugging
		{
			class mapping;
			class cluster;
			class node;
			class routine;
		}
		namespace analyzer
		{
			class resolver;
			namespace extensions
			{
				class extensions;
				class extension;
			}
			class analyzer : public mu::io::ast::visitor
			{
			public:
				analyzer (boost::function <void (mu::core::cluster *)> target_a, mu::core::errors::error_target & errors_a);
				void input (mu::io::ast::cluster * node_a);
				void operator () (mu::io::ast::cluster * cluster_a) override;
				void operator () (mu::io::ast::parameters * parameters_a) override;
				void operator () (mu::io::ast::expression * expression_a) override;
				void operator () (mu::io::ast::identifier * identifier_a) override;
				void operator () (mu::io::ast::value * value_a) override;
				boost::function <void (mu::core::cluster *)> target;
                mu::io::analyzer::name_map names;
				mu::core::errors::error_target & errors;
				mu::core::cluster * cluster;
			};
		}
	}
}
