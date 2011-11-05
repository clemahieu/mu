#include "routine_builder_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_repl/entry_routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/lexer/istream_input.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/builder.h>
#include <lambda_p_kernel/builder.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/errors/error_list.h>

#include <fstream>
#include <sstream>

void lambda_p_repl::routine_builder_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::lexer::character_stream> stream (boost::dynamic_pointer_cast <lambda_p::lexer::character_stream> (nodes [statement->association->references [0]]));
		if (stream.get () != nullptr)
		{
			core (statement, nodes, problems, stream);
		}
		else
		{
			problems (new lambda_p::errors::unexpected_binder_type (binder_name (), 0, std::wstring (L"data")));
		}
	}
}

void lambda_p_repl::routine_builder_binder::core (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems, boost::shared_ptr <lambda_p::lexer::character_stream> stream)
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
	lambda_p_kernel::builder input;
	input (stream);
	if (!input.error ())
	{
		nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (input.routines.routines->operator[] (0)));
	}
	else
	{
		std::wstring message;
		message.append (L"Unable to parse stream");
		problems (new lambda_p::errors::binder_string_error (binder_name (), message));
	}
}

std::wstring lambda_p_repl::routine_builder_binder::binder_name ()
{
	return std::wstring (L"routine_builder_binder");
}