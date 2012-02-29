#include "operation.h"

#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/script_io/builder.h>
#include <mu/script/cluster/node.h>
#include <mu/script/extensions/node.h>
#include <mu/script/package/create_from_cluster.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/runtime/routine.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void mu::script::loads::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto file (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
	if (extensions.get () != nullptr)
	{
		if (file.get () != nullptr)
		{
			auto path (boost::filesystem::initial_path ());
			path /= std::string (file->string.begin (), file->string.end ());
			std::ifstream stream;
			stream.open (path.string ());
			if (stream.is_open ())		
			{
				auto input (boost::shared_ptr <mu::io::lexer::istream_input> (new mu::io::lexer::istream_input (stream)));
				mu::script_io::builder builder (extensions->extensions);
				mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
				source (input);
				source ();
				if (builder.errors->errors.empty ())
				{
					if (builder.clusters.size () == 1)
					{
						auto result (boost::make_shared <mu::script::extensions::node> ());
						auto cluster (builder.clusters [0]);
						for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
						{
							result->extensions->extensions_m [i->first] = boost::make_shared <mu::io::analyzer::extensions::global> (i->second);
						}
						results.push_back (result);
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
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::loads::operation::count ()
{
	return 2;
}