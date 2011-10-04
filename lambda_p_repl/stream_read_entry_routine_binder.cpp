#include "stream_read_entry_routine_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_repl/entry_routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/data.h>
#include <lambda_p_repl/istream_input.h>
#include <lambda_p/errors/unexpected_node_type.h>
#include <lambda_p/errors/binder_string_error.h>

#include <fstream>
#include <sstream>

lambda_p_repl::stream_read_entry_routine_binder::stream_read_entry_routine_binder(void)
{
}

lambda_p_repl::stream_read_entry_routine_binder::~stream_read_entry_routine_binder(void)
{
}

void lambda_p_repl::stream_read_entry_routine_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::node * node (statement->association->parameters [0]);
		::lambda_p::core::node_id node_type (node->node_type ());
		switch (node_type)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::core::data * data (static_cast < ::lambda_p::core::data *> (node));
				::std::fstream file;
				file.open (data->string ());
				if (file.is_open ())
				{
					::lambda_p_repl::istream_input input (file);
					::lambda_p_repl::entry_routine routine (input, ::std::wcout);
					routine ();
				}
				else
				{
					::std::wstring message;
					message.append (L"Unable to open file: ");
					message.append (data->string ());
					problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"stream_read_entry_routine_binder"), message)));
				}
			}
			break;
		default:
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (::std::wstring (L"stream_read_entry_routine_binder"), 0, node_type)));
			break;
		}
	}
}

::std::wstring lambda_p_repl::stream_read_entry_routine_binder::binder_name ()
{
	return ::std::wstring (L"stream_read_entry_routine_binder");
}