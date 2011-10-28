#include "routine_builder_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/entry_routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_repl/istream_input.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/routine_builder.h>
#include <lambda_p_repl/routine_input.h>
#include <lambda_p_kernel/routine.h>

#include <fstream>
#include <sstream>

void lambda_p_repl::routine_builder_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & instances, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr < lambda_p_repl::character_stream> stream (boost::dynamic_pointer_cast <lambda_p_repl::character_stream> (instances [statement->association->parameters [0]]));
		if (stream.get () != NULL)
		{
			::lambda_p_repl::routine_input input;
			input (stream);
			if (!input.error ())
			{
				instances [statement->association->results [0]] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (input.routines.routines->operator[] (0)));
			}
			else
			{
				std::wstring message;
				message.append (L"Unable to parse stream");
				problems (new lambda_p::errors::binder_string_error (binder_name (), message));
			}
		}
		else
		{
			problems (new lambda_p::errors::unexpected_binder_type (binder_name (), 0, std::wstring (L"data")));
		}
	}
}

std::wstring lambda_p_repl::routine_builder_binder::binder_name ()
{
	return std::wstring (L"routine_builder_binder");
}