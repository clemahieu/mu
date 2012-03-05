#include "operation.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/builder.h>
#include <mu/script/cluster/node.h>
#include <mu/script/extensions/node.h>
#include <mu/script/package/create_from_cluster.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/ast/cluster.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void mu::script::load::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto file (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (file.get () != nullptr)
	{
		auto result (core (errors_a, file));
		if (result.get () != nullptr)
		{
			results.push_back (result);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [1], 1);
	}
}

size_t mu::script::load::operation::count ()
{
	return 1;
}

boost::shared_ptr <mu::io::ast::cluster> mu::script::load::operation::core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::string::node> file)
{
	boost::shared_ptr <mu::io::ast::cluster> result;
	auto path (boost::filesystem::initial_path ());
	path /= std::string (file->string.begin (), file->string.end ());
	std::ifstream stream;
	stream.open (path.string ());
	if (stream.is_open ())		
	{
		auto input (boost::shared_ptr <mu::io::lexer::istream_input> (new mu::io::lexer::istream_input (stream)));
		mu::io::builder builder;
		mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
		source (input);
		source ();
		if (builder.errors->errors.empty ())
		{
			if (builder.clusters.size () == 1)
			{
				result = builder.clusters [0];
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
	return result;
}