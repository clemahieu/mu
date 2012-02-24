#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <lambda_p_script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/routine.h>
#include <mu/script/cluster/node.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

mu::script::exec::operation::operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void mu::script::exec::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto name (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
		if (name.get () != nullptr)
		{		
			auto path (::boost::filesystem::initial_path ());
			std::string relative (name->string.begin (), name->string.end ());
			path /= relative;
			std::ifstream stream;
			stream.open (path.string ());
			if (stream.is_open ())
			{
				auto input (boost::shared_ptr <mu::io::lexer::istream_input> (new mu::io::lexer::istream_input (stream)));
				lambda_p_script_io::builder builder (extensions);
				mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
				source (input);
				source ();
				if (builder.errors->errors.empty ())
				{
					if (builder.clusters.size () == 1)
					{
						auto cluster (builder.clusters [0]);
						if (cluster->routines.size () > 0)
						{
							auto routine (cluster->routines [0]);
							std::vector <boost::shared_ptr <mu::core::node>> arguments (parameters.begin () + 1, parameters.end ());
							routine->perform (errors_a, arguments, results);
						}
						else
						{
							std::wstringstream message;
							message << L"Cluster does not contain a routine: ";
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
				std::wstringstream message;
				message << L"File could not be opened: ";
				std::string patha (path.string ());
				std::wstring path (patha.begin (), patha.end ());
				message << path;
				(*errors_a) (message.str ());
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

std::wstring mu::script::exec::operation::name ()
{
	return std::wstring (L"mu::script::exec::operation");
}