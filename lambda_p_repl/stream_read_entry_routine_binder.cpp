#include "stream_read_entry_routine_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/binder/string_instance.h>
#include <lambda_p_repl/entry_routine.h>

#include <fstream>
#include <sstream>

lambda_p_repl::stream_read_entry_routine_binder::stream_read_entry_routine_binder(void)
{
}

lambda_p_repl::stream_read_entry_routine_binder::~stream_read_entry_routine_binder(void)
{
}

void lambda_p_repl::stream_read_entry_routine_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 2)
	{
		::lambda_p::core::node_id node_type (statement->arguments [1]->node_type ());
		switch (node_type)
		{
		case ::lambda_p::core::node_reference:
			{
				::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (statement->arguments [1]));
				assert (search != instances.end ());
				::boost::shared_ptr < ::lambda_p::binder::string_instance> string (::boost::dynamic_pointer_cast < ::lambda_p::binder::string_instance> (search->second));
				if (string.get () != NULL)
				{
					::std::wfstream file;
					file.open (string->string);
					if (file.is_open ())
					{
						::lambda_p_repl::entry_routine routine (file, ::std::wcout);
						routine ();
					}
					else
					{
						problems << L"Unable to open file: ";
						problems << string->string;
						problems << '\n';
					}
				}
				else
				{
					problems << L"argument 1 is not a string_instance\n";
				}
			}
			break;
		default:
			problems << L"stream_read_entry_routine_binder expects argument 1 to be a reference, have: ";
			problems << statement->arguments [1]->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"stream_read_entry_routine_binder expects 1 argument, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::stream_read_entry_routine_binder::operator () ()
{
}