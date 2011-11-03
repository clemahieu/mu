#include "exec_binder.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_repl/file_stream.h>
#include <lambda_p_repl/builder.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/errors/error_list.h>

#include <boost/filesystem.hpp>

#include <sstream>

lambda_p_repl::exec_binder::exec_binder ()
{
}

void lambda_p_repl::exec_binder::set (boost::shared_ptr <lambda_p::binder::node> environment_a, boost::shared_ptr <lambda_p::binder::node> exec_a)
{
	environment = environment_a;
	exec = exec_a;
}

void lambda_p_repl::exec_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes_a, lambda_p::errors::error_list & problems)
{
	check_count (0, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes_a [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			auto path (boost::filesystem::initial_path () /= data->string ());
			auto stream (boost::shared_ptr <lambda_p::lexer::character_stream> (new lambda_p_repl::file_stream (path.wstring ())));
			lambda_p_repl::builder input (environment, exec);
			input (std::wstring (L";;\n"));
			input (stream);
			if (!input.error ())
			{
				if (input.routines.routines->size () > 0)
				{
					lambda_p_kernel::apply binder;
					lambda_p::binder::node_list nodes;
					lambda_p::binder::node_list declarations;
					binder.core (lambda_p_kernel::routine (input.routines.routines->operator[] (0)), nodes, problems, declarations);
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
				add_error (L"unable to parse stream", problems);
			}			
		}
		else
		{
			unexpected_binder_type_error (0, L"data", problems);
		}
	}
}

std::wstring lambda_p_repl::exec_binder::binder_name ()
{
	return std::wstring (L"exec_binder");
}