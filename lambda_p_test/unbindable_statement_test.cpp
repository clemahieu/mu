#include "unbindable_statement_test.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error_list.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::unbindable_statement_test::run ()
{
	boost::shared_ptr <lambda_p::binder::data> data (new lambda_p::binder::data (std::wstring ()));
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	boost::shared_ptr <lambda_p::binder::node_list> nodes (new lambda_p::binder::node_list);
	(*nodes) [declaration] = data;
	boost::shared_ptr <lambda_p_kernel::routine> target (new lambda_p_kernel::routine (routine));
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	apply.core (*target, *nodes, problems);
	assert (problems.errors.size () == 1);
}