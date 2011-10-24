#include "exec_binder.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_repl/file_stream.h>
#include <lambda_p/routine_builder.h>
#include <lambda_p_repl/routine_input.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/routine.h>

#include <boost/filesystem.hpp>

#include <sstream>

lambda_p_repl::exec_binder::exec_binder (lambda_p::binder::routine_instances instances_a)
	: instances (instances_a)
{
}

void lambda_p_repl::exec_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances_a, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.empty ())
	{
		auto data (boost::dynamic_pointer_cast <lambda_p::binder::data> (instances_a [statement->association->parameters [0]]));
		if (data.get () != nullptr)
		{
			auto path (boost::filesystem::initial_path () /= data->string ());
			auto stream (boost::shared_ptr <lambda_p_repl::character_stream> (new lambda_p_repl::file_stream (path.wstring ())));
			lambda_p_repl::routine_input input;
			input (std::wstring (L"environment quit exec = ;\n"));
			input (stream);
			if (!input.error ())
			{
				if (input.routines.routines->size () > 0)
				{
					lambda_p_kernel::apply binder;
					binder.core (lambda_p_kernel::routine (input.routines.routines->operator[] (0)), instances, problems);
				}
				else
				{
					std::wstringstream message;
					message << L"File: ";
					message << data->string ();
					message << L" doesn't contain a routine";
					add_error (message.str (), problems);
				}
			}
			else
			{
				add_error (std::wstring (L"unable to parse stream"), problems);
			}			
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"data"), problems);
		}
	}
}

std::wstring lambda_p_repl::exec_binder::binder_name ()
{
	return std::wstring (L"exec_binder");
}