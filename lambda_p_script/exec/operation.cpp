#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_io/lexer/istream_input.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/cluster.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

lambda_p_script::exec::operation::operation (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void lambda_p_script::exec::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto name (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [0]));
		if (name.get () != nullptr)
		{		
			auto path (::boost::filesystem::initial_path ());
			std::string relative (name->string.begin (), name->string.end ());
			path /= relative;
			std::ifstream stream;
			stream.open (path.string ());
			auto input (boost::shared_ptr <lambda_p_io::lexer::istream_input> (new lambda_p_io::lexer::istream_input (stream)));
			lambda_p_script_io::builder builder (extensions);
			lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
			source (input);
			source ();
			if (builder.errors->errors.empty ())
			{
				if (builder.clusters.size () == 1)
				{
					auto cluster (builder.clusters [0]);
					if (cluster->routines.size () == 1)
					{
						auto routine (cluster->routines [0]);
						std::vector <boost::shared_ptr <lambda_p::node>> arguments (parameters.begin () + 1, parameters.end ());
						routine->perform (errors_a, arguments, results);
					}
					else
					{
						std::wstringstream message;
						message << L"Cluster does not contain one routine: ";
						message << cluster->routines.size ();
						(*errors_a) (message.str ());
					}
				}
				else
				{
					std::wstringstream message;
					message << L"File did not contain one cluster: ";
					message << builder.clusters.size ();
					(*errors_a) (message.str ());
				}
			}
			else
			{
				for (auto i (builder.errors->errors.begin ()), j (builder.errors->errors.end ()); i != j; ++i)
				{
					(*errors_a) ((*i).first, (*i).second);
				}
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
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