#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>
#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class statement;
	}
	namespace errors
	{
		class error;
		class error_list;
	}
	namespace binder
	{
		class binder;
		class node;
		class node_list;
	}
}
namespace lambda_p_kernel
{
	class bind_procedure
	{
	public:
		bind_procedure (boost::shared_ptr <lambda_p::core::routine> routine_a, lambda_p::binder::node_list & nodes_a);
		~bind_procedure (void);
		void operator () (lambda_p::errors::error_list & problems);
		std::map <size_t, size_t> unbound_statements;
		boost::shared_ptr <lambda_p::core::routine> routine;
		lambda_p::binder::node_list & nodes;
	private:
		void bind_statement (size_t statement, lambda_p::errors::error_list & problems);
		void populate_unbound (size_t statement, boost::shared_ptr <lambda_p::binder::binder> & binder, lambda_p::errors::error_list & problems);
		void retry_bind (size_t statement, lambda_p::errors::error_list & problems);
		void copy_declaration_binder (boost::shared_ptr <lambda_p::binder::node> & binder, size_t node);
	};
}

