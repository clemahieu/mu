#include "node_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_result_count.h>
#include <lambda_p/errors/unexpected_argument_count.h>
#include <lambda_p/errors/unexpected_node_type.h>
#include <lambda_p/errors/binder_string_error.h>

#include <sstream>

lambda_p::binder::node_binder::node_binder(void)
{
}

lambda_p::binder::node_binder::~node_binder(void)
{
}

void lambda_p::binder::node_binder::check_count_only_references (size_t result_count, size_t argument_count, ::lambda_p::core::statement * statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (result_count, argument_count, statement, problems);
	check_only_references (statement, problems);
}

void lambda_p::binder::node_binder::check_only_references (::lambda_p::core::statement * statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	size_t position (1);
	for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i, ++position)
	{
        ::lambda_p::core::node * node (*i);
		::lambda_p::core::node_id type (node->node_type ());
		switch (type)
		{
		case ::lambda_p::core::node_reference:
				// Reference is what we're looking for
			break;
		case ::lambda_p::core::node_data:
			{
				::boost::shared_ptr < ::lambda_p::errors::error> problem (new ::lambda_p::errors::unexpected_node_type (binder_name (), position, type));
				problems.push_back (problem);
			}
			break;
		default:
			{
				// Should only have references or data at this point
				::boost::shared_ptr < ::lambda_p::errors::error> problem (new ::lambda_p::errors::unexpected_node_type (binder_name (), position, type));
				problems.push_back (problem);
				assert (false);
			}
			break;
		}
	}
}

void lambda_p::binder::node_binder::check_count (size_t result_count, size_t argument_count, ::lambda_p::core::statement * statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	if (statement->association->results.size () != result_count)
	{
		::boost::shared_ptr < ::lambda_p::errors::unexpected_result_count> problem (new ::lambda_p::errors::unexpected_result_count (binder_name (), statement->association->results.size (), result_count));
		problems.push_back (problem);
	}
	if (statement->association->parameters.size () != argument_count)
	{
		::boost::shared_ptr < ::lambda_p::errors::unexpected_argument_count> problem (new ::lambda_p::errors::unexpected_argument_count (binder_name (), statement->association->parameters.size (), argument_count));
		problems.push_back (problem);
	}
}

void lambda_p::binder::node_binder::add_error (::std::wstring message, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (binder_name (), message)));
}

