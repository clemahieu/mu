#include "read_from_file.h"

#include <core/errors/error_list.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_io/lexer/istream_input.h>
#include <lambda_p_io/builder.h>
#include <lambda_p_io/ast/cluster.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

void lambda_p_script::ast::read_from_file::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{			
		auto path (::boost::filesystem::initial_path ());
		std::string relative (one->string.begin (), one->string.end ());
		path /= relative;
		std::ifstream stream;
		stream.open (path.string ());
		if (stream.is_open ())
		{
			auto input (boost::shared_ptr <lambda_p_io::lexer::istream_input> (new lambda_p_io::lexer::istream_input (stream)));
			lambda_p_io::builder builder;
			lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
			source (input);
			source ();
			if (builder.errors->errors.empty ())
			{
				if (builder.clusters.size () == 1)
				{
					auto cluster (builder.clusters [0]);
					results.push_back (cluster);
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

size_t lambda_p_script::ast::read_from_file::count ()
{
	return 1;
}