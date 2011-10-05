#include <lambda_p/core/routine.h>

#include <lambda_p/errors/orphan_node.h>
#include <lambda_p/errors/orphan_reference.h>
#include <lambda_p/errors/undefined_reference.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/core/declaration.h>

lambda_p::core::routine::routine ()
	: surface (new ::lambda_p::core::association)
{
}

lambda_p::core::routine::~routine(void)
{
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = declarations.begin (); i != declarations.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::binder::data *>::const_iterator i = data.begin (); i != data.end (); ++i)
	{
		delete *i;
	}
}

::lambda_p::core::statement * lambda_p::core::routine::add_statement (::lambda_p::core::declaration * target_a)
{
    ::lambda_p::core::statement * statement (new ::lambda_p::core::statement (target_a));
	statements.push_back (statement);
	return statement;
}

::lambda_p::binder::data * lambda_p::core::routine::add_data (::std::wstring string)
{
    ::lambda_p::binder::data * data_l (new ::lambda_p::binder::data (string));
	data.push_back (data_l);
	return data_l;
}

::lambda_p::core::declaration * lambda_p::core::routine::add_declaration ()
{
    ::lambda_p::core::declaration * declaration (new ::lambda_p::core::declaration);
	declarations.push_back (declaration);
	return declaration;
}

void lambda_p::core::routine::validate (::std::vector < ::lambda_p::errors::error *> & problems) const
{
    size_t current_statement (0);
    for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        ::lambda_p::core::statement * statement (*i);
		validate_node (statement->target, current_statement, current_argument, problems);
		++current_argument;		
		for (::std::vector < ::lambda_p::core::declaration *>::const_iterator j = statement->association->results.begin (); j != statement->association->results.end (); ++j, ++current_argument)
		{
			::lambda_p::core::node * node (*j);
			validate_node (node, current_statement, current_argument, problems);
		}
		for (::std::vector < ::lambda_p::core::node *>::const_iterator j = statement->association->parameters.begin (); j != statement->association->parameters.end (); ++j, ++current_argument)
        {
			::lambda_p::core::node * node (*j);
			validate_node (node, current_statement, current_argument, problems);
        }
    }
}

void lambda_p::core::routine::validate_node (::lambda_p::core::node * node, size_t current_statement, size_t current_argument, ::std::vector < ::lambda_p::errors::error *> & problems) const
{
    ::lambda_p::core::node_id node_id (node->node_type ());
    switch (node_id)
    {
        case ::lambda_p::core::node_declaration:
        {
            ::lambda_p::core::declaration * declaration (static_cast < ::lambda_p::core::declaration *> (node));
            if (::std::find (declarations.begin (), declarations.end (), declaration) == declarations.end ())
            {
                ::lambda_p::errors::orphan_node * error (new ::lambda_p::errors::orphan_node (::lambda_p::core::position (current_statement, current_argument)));
                problems.push_back (error);
            }
        }
            break;
        case ::lambda_p::core::node_data:
        {
            ::lambda_p::binder::data * data_l (static_cast < ::lambda_p::binder::data *> (node));
            if (::std::find (data.begin (), data.end (), data_l) == data.end ())
            {
                ::lambda_p::errors::orphan_node * error (new ::lambda_p::errors::orphan_node (::lambda_p::core::position (current_statement, current_argument)));
                problems.push_back (error);
            }
        }
            break;
        default:
            assert (false);
            break;
    }
}

void lambda_p::core::routine::placement (::std::map < ::lambda_p::core::node const *, ::lambda_p::core::position> & argument_positions, ::std::map < ::lambda_p::core::statement const *, size_t> & statement_positions) const
{
    size_t current_statement (0);
    for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        ::lambda_p::core::statement * statement (*i);
        statement_positions [statement] = current_statement;
		argument_positions [statement->target] = ::lambda_p::core::position (current_statement, current_argument);
		++current_argument;
		for (::std::vector < ::lambda_p::core::declaration *>::const_iterator j = statement->association->results.begin (); j != statement->association->results.end (); ++j, ++current_argument)
		{
            ::lambda_p::core::node * argument (*j);
            argument_positions [argument] = ::lambda_p::core::position (current_statement, current_argument);
		}
		for (::std::vector < ::lambda_p::core::node *>::const_iterator j = statement->association->parameters.begin (); j != statement->association->parameters.end (); ++j, ++current_argument)
        {
            ::lambda_p::core::node * argument (*j);
            argument_positions [argument] = ::lambda_p::core::position (current_statement, current_argument);
        }
    }
}