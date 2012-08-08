#include <mu/script/ast/read_from_file.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/builder.h>
#include <mu/io/ast/cluster.h>
#include <mu/core/check.h>
#include <mu/core/errors/string_error.h>
#include <mu/io/source.h>
#include <mu/script/context.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>
#include <fstream>

#include <gc_cpp.h>

bool mu::script::ast::read_from_file::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		auto path (::boost::filesystem::initial_path ());
		std::string relative (one->string.begin (), one->string.end ());
		path /= relative;
		std::ifstream stream;
		stream.open (path.string ().c_str ());
		if (stream.is_open ())
		{
			mu::io::builder builder;
            mu::io::process (builder, stream);
			if (builder.errors.errors.empty ())
			{
				if (builder.cluster != nullptr)
				{
					auto cluster (builder.cluster);
					context_a.push (cluster);
				}
				else
				{
					mu::stringstream message;
					message << L"File did not contain a cluster";
					context_a.errors (message.str ());
					result = false;
				}
			}
			else
			{
				for (auto i (builder.errors.errors.begin ()), j (builder.errors.errors.end ()); i != j; ++i)
				{
					context_a.errors (*i);
				}
				result = false;
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
			result = false;
		}
	}
	return result;
}