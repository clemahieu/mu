#include <mu/script/ast/read_from_file.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/builder.h>
#include <mu/io/ast/cluster.h>
#include <mu/script/check.h>
#include <mu/io/debugging/error.h>
#include <mu/core/errors/string_error.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>
#include <fstream>

bool mu::script::ast::read_from_file::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (0)));
		auto path (::boost::filesystem::initial_path ());
		std::string relative (one->string.begin (), one->string.end ());
		path /= relative;
		std::ifstream stream;
		stream.open (path.string ().c_str ());
		if (stream.is_open ())
		{
			auto input (boost::shared_ptr <mu::io::lexer::istream_input> (new mu::io::lexer::istream_input (stream)));
			mu::io::builder builder;
			builder (input);
			builder ();
			if (builder.errors->errors.empty ())
			{
				if (builder.cluster != nullptr)
				{
					auto cluster (builder.cluster);
					context_a.push (cluster);
				}
				else
				{
					std::wstringstream message;
					message << L"File did not contain a cluster";
					context_a.errors (message.str ());
					result = false;
				}
			}
			else
			{
				for (auto i (builder.errors->errors.begin ()), j (builder.errors->errors.end ()); i != j; ++i)
				{
					context_a.errors (*i);
				}
				result = false;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"File could not be opened: ";
			std::string patha (path.string ());
			std::wstring path (patha.begin (), patha.end ());
			message << path;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}