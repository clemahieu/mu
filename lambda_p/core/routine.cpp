#include <lambda_p/core/routine.h>

#include <lambda_p/errors/orphan_node.h>
#include <lambda_p/errors/orphan_reference.h>
#include <lambda_p/errors/undefined_reference.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/errors/node_out_of_order.h>

#include <algorithm>

lambda_p::core::routine::routine ()
	: surface (new lambda_p::core::association),
	nodes (0),
	injected_surface (new lambda_p::core::association)
{
}

lambda_p::core::routine::~routine(void)
{
	for (auto i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
	delete surface;
	delete injected_surface;
}

lambda_p::core::statement * lambda_p::core::routine::add_statement ()
{
    lambda_p::core::statement * statement (new lambda_p::core::statement);
	statements.push_back (statement);
	return statement;
}

size_t lambda_p::core::routine::inject_declaration (boost::shared_ptr <lambda_p::binder::node> node_a)
{
	size_t result (add_declaration ());
	injected [result] = node_a;
	return result;
}

size_t lambda_p::core::routine::add_declaration ()
{
    size_t declaration (nodes);
	++nodes;
	return declaration;
}

void lambda_p::core::routine::validate (std::vector <lambda_p::errors::error *> & problems) const
{
    size_t current_statement (0);
    for (auto i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        lambda_p::core::statement * statement (*i);
		validate_node (statement->target, current_statement, current_argument, problems);
		++current_argument;		
		for (auto j = statement->association->declarations.begin (); j != statement->association->declarations.end (); ++j, ++current_argument)
		{
			size_t node (*j);
			validate_node (node, current_statement, current_argument, problems);
		}
		for (auto j = statement->association->references.begin (); j != statement->association->references.end (); ++j, ++current_argument)
        {
			size_t node (*j);
			validate_node (node, current_statement, current_argument, problems);
        }
    }
}

void lambda_p::core::routine::validate_node (size_t node, size_t current_statement, size_t current_argument, std::vector < lambda_p::errors::error *> & problems) const
{
    if (node >= nodes)
    {
        lambda_p::errors::orphan_node * error (new lambda_p::errors::orphan_node (lambda_p::core::position (current_statement, current_argument)));
        problems.push_back (error);
    }
}

void lambda_p::core::routine::placement (std::map < size_t, lambda_p::core::position> & argument_positions, std::map < lambda_p::core::statement const *, size_t> & statement_positions) const
{
    size_t current_statement (0);
    for (auto i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        lambda_p::core::statement * statement (*i);
        statement_positions [statement] = current_statement;
		argument_positions [statement->target] = lambda_p::core::position (current_statement, current_argument);
		++current_argument;
		for (auto j = statement->association->declarations.begin (); j != statement->association->declarations.end (); ++j, ++current_argument)
		{
            size_t argument (*j);
            argument_positions [argument] = lambda_p::core::position (current_statement, current_argument);
		}
		for (auto j = statement->association->references.begin (); j != statement->association->references.end (); ++j, ++current_argument)
        {
            size_t argument (*j);
            argument_positions [argument] = lambda_p::core::position (current_statement, current_argument);
        }
    }
}