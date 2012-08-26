#include <mu/script/loads/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/core/check.h>
#include <mu/io/keywording_extensions.h>
#include <mu/script/context.h>
#include <mu/io/lexer_istream_input.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>

#include <boost/bind.hpp>

#include <gc_cpp.h>

#include <fstream>

bool mu::script::loads::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::core::check <mu::script::string::node> (context_a));
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

mu::script::cluster::node * mu::script::loads::operation::core (mu::script::context & context_a, mu::script::string::node * file)
{
    std::fstream stream;
    std::string name (file->string.begin (), file->string.end ());
    stream.open (name.c_str ());
    auto input (new (GC) mu::io::lexer::istream_input (stream));
    mu::script::builder builder;
    mu::io::process (builder, *input);
    mu::script::cluster::node * result (nullptr);
    if (!builder.errors ())
    {
        assert (builder.clusters.size () == 1);
        result = builder.clusters [0];
    }
    builder.errors.print(std::wcerr);
	return result;
}