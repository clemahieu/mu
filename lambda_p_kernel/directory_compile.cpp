#include "directory_compile.h"

#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_repl/file_stream.h>
#include <lambda_p_kernel/builder.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/errors/error_list.h>

#include <boost/filesystem.hpp>

#include <sstream>
#include <iostream>

void lambda_p_kernel::directory_compile::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto directory (boost::dynamic_pointer_cast <lambda_p_kernel::nodes::data> (nodes [statement->association->references [0]]));
		if (directory.get () != nullptr)
		{			
			auto path (boost::filesystem3::initial_path () /= directory->string ());
			try
			{
				boost::shared_ptr <lambda_p_kernel::package> package (new lambda_p_kernel::package);
				boost::filesystem3::directory_iterator directory (path);
				package_directory (problems, package, directory);	
				nodes [statement->association->declarations [0]] = package;
			}
			catch (boost::filesystem3::filesystem_error const & error)
			{
				std::wstringstream message;
				message << L"Exception while recursively iterating: ";
				message << directory->string ();
				add_error (message.str (), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, L"data", problems);
		}
	}
}

void lambda_p_kernel::directory_compile::package_directory (lambda_p::errors::error_list & problems, boost::shared_ptr <lambda_p_kernel::package> & package, boost::filesystem3::directory_iterator & directory)
{
	for (; directory != boost::filesystem3::directory_iterator (); ++directory)
	{
		std::wstring item_name (directory->path ().filename ().wstring ());
		try
		{
			boost::filesystem3::directory_iterator subdir (directory->path ());
			boost::shared_ptr <lambda_p_kernel::package> subpackage (new lambda_p_kernel::package);
			package->nodes [item_name] = subpackage;
			package_directory (problems, subpackage, subdir);
		}
		catch (boost::filesystem3::filesystem_error & error)
		{
			boost::shared_ptr <lambda_p::lexer::character_stream> stream (new lambda_p_repl::file_stream (directory->path ().wstring ()));
			std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
			lambda_p_kernel::builder input;
			input (stream);
			if (input.routines.routines->size () == 1)
			{
				package->nodes [item_name] = input.routines.routines->operator[] (0);
			}
			else
			{
				std::wstringstream message;
				message << L"No routine in file: ";
				message << directory->path ().wstring ();
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_kernel::directory_compile::binder_name ()
{
	return std::wstring (L"directory_compile");
}