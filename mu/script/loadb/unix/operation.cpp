#include <mu/script/loadb/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <dlfcn.h>

#include <sstream>

#include <boost/filesystem.hpp>

bool mu::script::loadb::operation::operator () (mu::script::context & context_a)
{
    auto valid (false);
    if (mu::core::check <mu::script::string::node> (context_a))
    {
        auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		auto path (boost::filesystem::initial_path ());
		path /= std::string (one->string.begin (), one->string.end ());
		auto library (dlopen (path.string ().c_str (), RTLD_NOW | RTLD_GLOBAL));
		if (library != NULL)
		{
			auto version_address (dlsym (library, "version_554bc0f73fa23e91"));
			if (version_address != NULL)
			{
				auto version_pointer ((boost::uint64_t *) (version_address));
				auto version (* version_pointer);
				switch (version)
				{
				case 0x6d6ecf1f10200f:
					{
						auto extensions_address (dlsym (library, "extensions"));
						if (extensions_address != nullptr)
						{
							auto extensions_function ((mu::script::extensions::node * (*) ()) (extensions_address));
							auto extensions (extensions_function ());
                            mu::script::extensions::node * result (extensions);
							context_a.push (result);
                            valid = true;
						}
						else
						{
							mu::stringstream message;
							message << L"Function: 'extensions' does not exist in library: ";
							message << path.string ().c_str ();
							context_a.errors (message.str ());
						}
					}
					break;
				default:
					context_a.errors (U"Unrecognized version number");
					break;
				}
			}
			else
			{
				mu::stringstream message;
				message << L"Library did not have version function: ";
                auto str (path.wstring ());
				message << mu::string (str.begin (), str.end ());;
				context_a.errors (message.str ());
			}
		}
		else
		{
			mu::stringstream message;
			message << L"Library could not be loaded: ";
			std::string patha (path.string ());
			mu::string path (patha.begin (), patha.end ());
			message << path;
			context_a.errors (message.str ());
		}
	}
    
    return valid;
}