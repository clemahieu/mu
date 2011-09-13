#include "structure.h"

#include <lambda_p/core/declaration.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/data.h>

#include <sstream>

lambda_p::binder::structure::structure(void)
{
}

lambda_p::binder::structure::~structure(void)
{
}

void lambda_p::binder::structure::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count >= 3)
	{
		::lambda_p::core::node_id argument_1_id (statement->arguments [1]->node_type ());
		switch (argument_1_id)
		{
		case ::lambda_p::core::node_declaration:
		case ::lambda_p::core::node_reference:
			{
                bool good_arguments (true);
				for (size_t i = 2; i < argument_count; ++i)
				{
					::lambda_p::core::node_id argument_x_id (statement->arguments [i]->node_type ());
					switch (argument_x_id)
					{
					case ::lambda_p::core::node_data:
						break;
					default:
                        good_arguments = false;
						problems << L"dereference expects every argument >= 3 to be data, have: ";
						problems << statement->arguments [i]->node_type_name ();
						problems << L" at position";
						problems << i + 1;
						problems << '\n';
					}
				}
                if (good_arguments)
                {
                    bind_good (statement, instances, routine, problems);
                }
			}
			break;
		default:
			problems << L"dereference is expecting argument 1 to be declaration or reference, have: ";
			problems << statement->arguments [1]->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"deference is expecting three or more argument, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p::binder::structure::operator () ()
{
}

void lambda_p::binder::structure::bind_good (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	::boost::shared_ptr < ::lambda_p::binder::node_instance> node (instances [statement->arguments [0]]);
	::boost::shared_ptr < ::lambda_p::binder::structure> intermediate (::boost::dynamic_pointer_cast < ::lambda_p::binder::structure> (node));
	for (size_t i = 2; i < argument_count - 1 && node.get () != NULL; ++i)
	{
		if (intermediate.get () != NULL)
		{
			::lambda_p::core::data * data (static_cast < ::lambda_p::core::data *> (statement->arguments [i]));
			fetch_child (intermediate, node, i, data, instances, problems);
		}
		else
		{
			node.reset ();
			problems << L"Node at argument: ";
			problems << i;
			problems << L" is not a structure\n";
		}
	}
	if (node.get () != NULL)
	{
		::lambda_p::core::data * data (static_cast < ::lambda_p::core::data *> (statement->arguments [argument_count - 1]));
		::lambda_p::core::node_id node_type (statement->arguments [1]->node_type ());
		switch (node_type)
		{
		case ::lambda_p::core::node_declaration:
			fetch_child (intermediate, node, argument_count - 1, data, instances, problems);
			if (node.get () != NULL)
			{
				instances [statement->arguments [1]] = node;
			}
			break;
		case ::lambda_p::core::node_reference:
			intermediate->nodes [data->string ()] = instances [statement->arguments [1]];
			break;
		default:
			assert (false);
		}
	}
}

void lambda_p::binder::structure::fetch_child (::boost::shared_ptr < ::lambda_p::binder::structure> & intermediate, ::boost::shared_ptr < ::lambda_p::binder::node_instance> & node, size_t argument_number, ::lambda_p::core::data * data, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	::std::wstring string (data->string ());
	::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (intermediate->nodes.find (string));
	if (search != intermediate->nodes.end ())
	{
		node = search->second;
		intermediate = ::boost::dynamic_pointer_cast < ::lambda_p::binder::structure> (node);
	}
	else
	{
		node.reset ();
		intermediate.reset ();
		problems << L"Node at argument: ";
		problems << argument_number;
		problems << L" has no member named: ";
		problems << string;
		problems << '\n';
	}
}