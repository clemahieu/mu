#include "stream_read_entry_routine_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/entry_routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_repl/istream_input.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/errors/binder_string_error.h>

#include <fstream>
#include <sstream>

lambda_p_repl::stream_read_entry_routine_binder::stream_read_entry_routine_binder(void)
{
}

lambda_p_repl::stream_read_entry_routine_binder::~stream_read_entry_routine_binder(void)
{
}

void lambda_p_repl::stream_read_entry_routine_binder::bind (::lambda_p::core::statement * statement, ::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::data> data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [0]]));
		if (data.get () != NULL)
		{
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
				problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (binder_name (), message)));
			}
		}
		else
		{
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_binder_type (binder_name (), 0, ::std::wstring (L"data"))));
		}
	}
}

::std::wstring lambda_p_repl::stream_read_entry_routine_binder::binder_name ()
{
	return ::std::wstring (L"stream_read_entry_routine_binder");
}