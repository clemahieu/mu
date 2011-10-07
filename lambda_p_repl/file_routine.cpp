#include "file_routine.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_repl/routine_input.h>
#include <lambda_p_repl/istream_input.h>
#include <lambda_p/binder/routine.h>

#include <fstream>
#include <sstream>

lambda_p_repl::file_routine::file_routine(void)
{
}


void lambda_p_repl::file_routine::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::data> data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [0]]));
		if (data.get () != NULL)
		{
			::std::fstream file;
			file.open (data->string ());
			if (file.is_open ())
			{
				::lambda_p_repl::routine_input input;
				::lambda_p_repl::istream_input stream (file);
				input (stream);
				if (!input.error ())
				{
					if (input.routines.routines->size () == 1)
					{
						::boost::shared_ptr < ::lambda_p::binder::routine> routine (new ::lambda_p::binder::routine (input.routines.routines->operator[] (0)));
						instances [statement->association->results [0]] = routine;
					}
					else
					{
						::std::wstringstream message;
						message << L"Unable to parse 1 routine from file: ";
						message << data->string ();
						add_error (message.str (), problems);
					}
				}
				else
				{
					::std::wstring message;
					input.error_message (message);
					add_error (message, problems);
				}
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"data"), problems);
		}
	}
}

::std::wstring lambda_p_repl::file_routine::binder_name ()
{
	return ::std::wstring (L"file_routine_binder");
}