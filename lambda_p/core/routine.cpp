#include <lambda_p/core/routine.h>

#include <lambda_p/errors/orphan_node.h>
#include <lambda_p/errors/orphan_reference.h>
#include <lambda_p/errors/undefined_reference.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/errors/node_out_of_order.h>

#include <algorithm>

lambda_p::core::routine::routine ()
	: surface (new lambda_p::core::association),
	nodes (0)
{
}

lambda_p::core::routine::~routine(void)
{
	for (std::vector < lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
}

lambda_p::core::statement * lambda_p::core::routine::add_statement ()
{
    lambda_p::core::statement * statement (new lambda_p::core::statement);
	statements.push_back (statement);
	return statement;
}

size_t lambda_p::core::routine::add_data (std::wstring string)
{
    boost::shared_ptr < lambda_p::binder::data> data_l (new lambda_p::binder::data (string));
	size_t result (add_declaration ());
	injected [result] = data_l;
	return result;
}

size_t lambda_p::core::routine::add_declaration ()
{
    size_t declaration (nodes);
	++nodes;
	return declaration;
}

void lambda_p::core::routine::validate (std::vector < lambda_p::errors::error *> & problems) const
{
    size_t current_statement (0);
    for (std::vector < lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        lambda_p::core::statement * statement (*i);
		validate_node (statement->target, current_statement, current_argument, problems);
		++current_argument;		
		for (std::vector < size_t>::const_iterator j = statement->association->results.begin (); j != statement->association->results.end (); ++j, ++current_argument)
		{
			size_t node (*j);
			validate_node (node, current_statement, current_argument, problems);
		}
		for (std::vector < size_t>::const_iterator j = statement->association->parameters.begin (); j != statement->association->parameters.end (); ++j, ++current_argument)
        {
			size_t node (*j);
			validate_node (node, current_statement, current_argument, problems);
        }
    }
	size_t previous (0 - 1);
	size_t statement_number (0 - 1);
	{
		size_t result_number (0);
		for (std::vector < size_t>::const_iterator i = surface->results.begin (); i != surface->results.end (); ++i, ++previous, ++result_number)
		{
			if (*i != previous + 1)
			{
				lambda_p::errors::node_out_of_order * error (new lambda_p::errors::node_out_of_order (statement_number, result_number));
				problems.push_back (error);
			}
		}
	}
	/* Was supposed to make sure nodes on left side are ordered but data creates new nodes on the right side.  Need for this depends on if we want to keep it that way.
	++statement_number;
	for (std::vector < lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++statement_number)
	{
		{
			size_t result_number (0);
			for (std::vector < size_t>::const_iterator j = (*i)->association->results.begin (); j != (*i)->association->results.end (); ++j, ++previous, ++result_number)
			{
				if (*j != previous + 1)
				{
					lambda_p::errors::node_out_of_order * error (new lambda_p::errors::node_out_of_order (statement_number, result_number));
					problems.push_back (error);
				}
			}
		}
	}*/
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
    for (std::vector < lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i, ++current_statement)
    {
        size_t current_argument (0);
        lambda_p::core::statement * statement (*i);
        statement_positions [statement] = current_statement;
		argument_positions [statement->target] = lambda_p::core::position (current_statement, current_argument);
		++current_argument;
		for (std::vector < size_t>::const_iterator j = statement->association->results.begin (); j != statement->association->results.end (); ++j, ++current_argument)
		{
            size_t argument (*j);
            argument_positions [argument] = lambda_p::core::position (current_statement, current_argument);
		}
		for (std::vector < size_t>::const_iterator j = statement->association->parameters.begin (); j != statement->association->parameters.end (); ++j, ++current_argument)
        {
            size_t argument (*j);
            argument_positions [argument] = lambda_p::core::position (current_statement, current_argument);
        }
    }
}