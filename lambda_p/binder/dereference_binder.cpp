#include "dereference_binder.h"

#include <lambda_p/core/declaration.h>
#include <lambda_p/binder/dereference.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/data.h>

#include <sstream>

lambda_p::binder::dereference_binder::dereference_binder(void)
{
}

lambda_p::binder::dereference_binder::~dereference_binder(void)
{
}

void lambda_p::binder::dereference_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count >= 4)
	{
		::lambda_p::core::node_id argument_1_id (statement->arguments [1]->node_type ());
		switch (argument_1_id)
		{
		case ::lambda_p::core::node_declaration:
			{
				::lambda_p::core::node_id argument_2_id (statement->arguments [2]->node_type ());
				switch (argument_2_id)
				{
				case ::lambda_p::core::node_reference:
					{
                        bool good_arguments (true);
						for (size_t i = 3; i < argument_count; ++i)
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
								problems << i;
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
					problems << L"dereference is expecting argument 2 to be a reference, have: ";
					problems << statement->arguments [2]->node_type_name ();
					problems << '\n';
					break;
				}
			}
			break;
		default:
			problems << L"dereference is expecting argument 1 to be declaration, have: ";
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

void lambda_p::binder::dereference_binder::operator () ()
{
}

void lambda_p::binder::dereference_binder::bind_good (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::binder::bound_routine & routine, ::std::wstringstream & problems)
{
    ::lambda_p::core::node * dereferencee_node (statement->arguments [2]);
    ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (dereferencee_node));
    if (search != instances.end ())
    {
        ::boost::shared_ptr < ::lambda_p::binder::node_instance> dereferencee_instance (search->second);
        ::boost::shared_ptr < ::lambda_p::binder::dereference> dereferencee (::boost::dynamic_pointer_cast < ::lambda_p::binder::dereference > (dereferencee_instance));
        if (dereferencee.get () != NULL)
        {
            ::lambda_p::core::data * data (dynamic_cast < ::lambda_p::core::data *> (statement->arguments [3]));
            ::std::wstring string (data->string ());
            ::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (dereferencee->nodes.find (string));
            if (search != dereferencee->nodes.end ())
            {
                instances [statement->arguments [1]] = search->second;
            }
            else
            {
                problems << L"Node has no member named: ";
                problems << string;
                problems << '\n';
            }
        }
        else
        {
            problems << L"Node cannot be dereferenced\n";
        }
    }
    else
    {
        problems << L"Node has no associated node_instance";
    }
}
