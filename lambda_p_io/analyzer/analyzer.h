#pragma once

#include <lambda_p/context.h>
#include <lambda_p/cluster.h>
#include <lambda_p_io/ast/visitor.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <set>

namespace lambda_p
{
	class cluster;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
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
		class analyzer : public lambda_p_io::ast::visitor
		{
		public:
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::cluster>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			analyzer (boost::function <void (boost::shared_ptr <lambda_p::cluster>)> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions_a);
			void input (boost::shared_ptr <lambda_p_io::ast::node> node_a);
			void operator () (lambda_p_io::ast::parameters * parameters_a) override;
			void operator () (lambda_p_io::ast::expression * expression_a) override;
			void operator () (lambda_p_io::ast::identifier * identifier_a) override;
			void operator () (lambda_p_io::ast::end * end_a) override;
			void mark_used (std::wstring name_a, lambda_p::context context_a);
			void back_resolve (std::wstring name_a, boost::shared_ptr <lambda_p::node> node_a);
			void resolve_routine (std::wstring name_a, boost::shared_ptr <lambda_p::routine> routine_a, lambda_p::context context_a);
			boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions;
			boost::function <void (boost::shared_ptr <lambda_p::cluster>)> target;
			std::multimap <std::wstring, lambda_p::context> used_names;
			std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p_io::analyzer::resolver>, lambda_p::context>> unresolved;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			boost::shared_ptr <lambda_p::cluster> cluster;
		};
	}
}

