#include "operation.h"

#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/script_io/builder.h>
#include <mu/script/cluster/node.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

mu::script::load::operation::operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void mu::script::load::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto path (boost::filesystem::initial_path ());
		path /= std::string (one->string.begin (), one->string.end ());
		std::ifstream stream;
		stream.open (path.string ());
		if (stream.is_open ())
		{
			auto input (boost::shared_ptr <mu::io::lexer::istream_input> (new mu::io::lexer::istream_input (stream)));
			mu::script_io::builder builder (extensions);
			mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
			source (input);
			source ();
			if (builder.errors->errors.empty ())
			{
				if (builder.clusters.size () == 1)
				{
					results.push_back (builder.clusters [0]);
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

size_t mu::script::load::operation::count ()
{
	return 1;
}