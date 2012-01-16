#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/data/node.h>
#include <lambda_p_io/lexer/istream_input.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

void lambda_p_script::exec::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto name (boost::dynamic_pointer_cast <lambda_p_script::data::node> (parameters [0]));
		if (name.get () != nullptr)
		{		
			auto path (::boost::filesystem::initial_path ());
			std::string relative (name->string.begin (), name->string.end ());
			path /= relative;
			std::ifstream stream;
			stream.open (path.string ());
			auto input (boost::shared_ptr <lambda_p_io::lexer::istream_input> (new lambda_p_io::lexer::istream_input (stream)));
			lambda_p_script_io::builder builder;
			lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
			source (input);
			source ();
			if (builder.errors->errors.empty ())
			{
				if (builder.routines.size () == 1)
				{
					auto routine (builder.routines [0]);
					std::vector <boost::shared_ptr <lambda_p::node>> arguments (parameters.begin () + 1, parameters.end ());
					routine->perform (errors_a, arguments, results);
				}
				else
				{
					std::wstringstream message;
					message << L"File did not contain exactly one routine: ";
					message << builder.routines.size ();
					(*errors_a) (message.str ());
				}
			}
			else
			{
				for (auto i (builder.errors->errors.begin ()), j (builder.errors->errors.end ()); i != j; ++i)
				{
					(*errors_a) (*i);
				}
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_script::exec::operation::name ()
{
	return std::wstring (L"lambda_p_script::exec::operation");
}