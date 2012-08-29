#include <mu/script/loads_operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/cluster_node.h>
#include <mu/script/string_node.h>
#include <mu/core/check.h>
#include <mu/io/keywording_extensions.h>
#include <mu/script/context.h>
#include <mu/io/lexer_istream_input.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/parser_scope_node.h>

#include <boost/bind.hpp>

#include <gc_cpp.h>

#include <fstream>

bool mu::script::loads::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::core::check <mu::script::string::node> (context_a));
	if (complete)
	{
		auto file (static_cast <mu::script::string::node *> (context_a.parameters (0)));
        mu::script::parser_scope::node scope;
		auto result (core (context_a, &scope, file));
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

bool mu::script::loads_extensions::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::core::check <mu::script::parser_scope::node, mu::script::string::node> (context_a));
	if (complete)
	{
        auto extensions (static_cast <mu::script::parser_scope::node *> (context_a.parameters (0)));
		auto file (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		auto result (mu::script::loads::operation::core (context_a, extensions, file));
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

mu::script::cluster::node * mu::script::loads::operation::core (mu::script::context & context_a, mu::script::parser_scope::node * scope_a, mu::script::string::node * file)
{
    mu::script::cluster::node * result (nullptr);
    std::fstream stream;
    std::string name (file->string.begin (), file->string.end ());
    stream.open (name.c_str ());
    if (!stream.fail ())
    {
        auto input (new (GC) mu::io::lexer::istream_input (stream));
        mu::script::builder builder (scope_a);
        mu::io::process (builder, *input);
        if (!builder.errors ())
        {
            assert (builder.clusters.size () == 1);
            result = builder.clusters [0];
        }
    }
    else
    {
        mu::stringstream message;
        message << U"Unable to open file: ";
        message << file->string;
        context_a.errors (message.str ());
    }
	return result;
}