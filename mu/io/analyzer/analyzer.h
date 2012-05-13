#pragma once

#include <mu/io/debugging/context.h>
#include <mu/core/cluster.h>
#include <mu/io/ast/visitor.h>

#include <boost/shared_ptr.hpp>
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
				analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a);
				analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
				void input (boost::shared_ptr <mu::io::ast::cluster> node_a);
				void operator () (mu::io::ast::cluster * cluster_a) override;
				void operator () (mu::io::ast::parameters * parameters_a) override;
				void operator () (mu::io::ast::expression * expression_a) override;
				void operator () (mu::io::ast::identifier * identifier_a) override;
				void mark_used (std::wstring name_a, boost::shared_ptr <mu::io::debugging::node> node_info_a);
				void back_resolve (std::wstring name_a, boost::shared_ptr <mu::core::node> node_a);
				void resolve_routine (std::wstring name_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <mu::io::debugging::routine> routine_info_a);
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
				boost::function <void (boost::shared_ptr <mu::core::cluster>)> target;
				std::multimap <std::wstring, boost::shared_ptr <mu::io::debugging::node>> used_names;
				std::multimap <std::wstring, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::io::debugging::context>> unresolved;
				boost::shared_ptr <mu::core::errors::error_target> errors;
				boost::shared_ptr <mu::core::cluster> cluster;
				boost::shared_ptr <mu::io::debugging::cluster> cluster_info;
				boost::shared_ptr <mu::io::debugging::mapping> mapping;
			};
		}
	}
}
