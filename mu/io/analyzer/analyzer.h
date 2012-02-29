#pragma once

#include <mu/core/context.h>
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
				void input (boost::shared_ptr <mu::io::ast::node> node_a);
				void operator () (mu::io::ast::parameters * parameters_a) override;
				void operator () (mu::io::ast::expression * expression_a) override;
				void operator () (mu::io::ast::identifier * identifier_a) override;
				void operator () (mu::io::ast::end * end_a) override;
				void mark_used (std::wstring name_a, mu::core::context context_a);
				void back_resolve (std::wstring name_a, boost::shared_ptr <mu::core::node> node_a);
				void resolve_routine (std::wstring name_a, boost::shared_ptr <mu::core::routine> routine_a, mu::core::context context_a);
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
				boost::function <void (boost::shared_ptr <mu::core::cluster>)> target;
				std::multimap <std::wstring, mu::core::context> used_names;
				std::multimap <std::wstring, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::core::context>> unresolved;
				boost::shared_ptr <mu::core::errors::error_target> errors;
				boost::shared_ptr <mu::core::cluster> cluster;
			};
		}
	}
}