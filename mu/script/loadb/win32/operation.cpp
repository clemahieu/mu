#include <mu/script/loadb/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>
#include <mu/script/check.h>
#include <mu/script/debugging/mapping.h>

#include <Windows.h>

#include <sstream>

#include <boost/filesystem.hpp>

void mu::script::loadb::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [0]));
		auto path (boost::filesystem::initial_path ());
		path /= std::string (one->string.begin (), one->string.end ());
		auto library (LoadLibrary (path.string ().c_str ()));
		if (library != NULL)
		{
			auto version_address (GetProcAddress (library, "version_554bc0f73fa23e91"));
			if (version_address != NULL)
			{
				auto version_pointer ((boost::uint64_t *) (version_address));
				auto version (* version_pointer);
				switch (version)
				{
				case 0x6d6ecf1f10200f:
					{
						auto extensions_address (GetProcAddress (library, "extensions"));
						if (extensions_address != nullptr)
						{
							auto extensions_function ((void (*) (mu::script::extensions::node **, mu::script::debugging::mapping **)) (extensions_address));
							mu::script::extensions::node * extensions;
							mu::script::debugging::mapping * debug_info;
							extensions_function (&extensions, &debug_info);
							boost::shared_ptr <mu::script::extensions::node> result (extensions);
							context_a.results.push_back (result);
							boost::shared_ptr <mu::script::debugging::mapping> mapping (debug_info);
							context_a.results.push_back (mapping);
						}
						else
						{
							std::wstringstream message;
							message << L"Function: 'extensions' does not exist in library: ";
							message << path.string ().c_str ();
							context_a (message.str ());
						}
					}
					break;
				default:
					context_a (L"Unrecognized version number");
					break;
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Library did not have version function: ";
				message << path.wstring ();
				context_a (message.str ());
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Library could not be loaded: ";
			std::string patha (path.string ());
			std::wstring path (patha.begin (), patha.end ());
			message << path;
			context_a (message.str ());
		}
	}
}