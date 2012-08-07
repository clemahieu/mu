#include <mu/script/load/operation.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/ast/builder.h>
#include <mu/script/extensions/node.h>
#include <mu/script/package/create_from_cluster.h>
#include <mu/io/ast/cluster.h>
#include <mu/script/check.h>
#include <mu/io/source.cpp>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>
#include <fstream>

#include <gc_cpp.h>

bool mu::script::load::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::script::check <mu::script::string::node> (context_a));
	if (complete)
	{
		auto file (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		auto result (core (context_a, file));
		if (result != nullptr)
		{
			context_a.push (result);
		}
		else
		{
			complete = false;
		}
	}
	return complete;
}

mu::io::ast::cluster * mu::script::load::operation::core (mu::script::context & context_a, mu::script::string::node * file)
{
	mu::io::ast::cluster * result (nullptr);
	auto path (boost::filesystem::initial_path ());
	path /= std::string (file->string.begin (), file->string.end ());
	std::ifstream stream;
	stream.open (path.string ().c_str ());
	if (stream.is_open ())		
	{
		mu::io::ast::builder builder;
        mu::io::process (builder, stream);
		if (builder.errors.errors.empty ())
		{
			result = builder.cluster;
		}
		else
		{
			for (auto i (builder.errors.errors.begin ()), j (builder.errors.errors.end ()); i != j; ++i)
			{
				context_a.errors (*i);
			}
		}
	}
	else
	{
		mu::stringstream message;
		message << L"File could not be opened: ";
		std::string patha (path.string ());
		mu::string path (patha.begin (), patha.end ());
		message << path;
		context_a.errors (message.str ());
	}
	return result;
}