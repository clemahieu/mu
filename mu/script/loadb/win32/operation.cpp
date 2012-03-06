#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/extensions/node.h>

#include <Windows.h>

#include <sstream>

#include <boost/filesystem.hpp>

void mu::script::loadb::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{		
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
							auto extensions_function ((mu::script::extensions::node * (*) ()) (extensions_address));
							auto extensions (extensions_function ());
							boost::shared_ptr <mu::script::extensions::node> result (extensions);
							results.push_back (result);
						}
						else
						{
							std::wstringstream message;
							message << L"Function: 'extensions' does not exist in library: ";
							message << path.string ().c_str ();
							(*errors_a) (message.str ());
						}
					}
					break;
				default:
					(*errors_a) (L"Unrecognized version number");
					break;
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Library did not have version function: ";
				message << path.wstring ();
				(*errors_a) (message.str ());
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Library could not be loaded: ";
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

size_t mu::script::loadb::operation::count ()
{
	return 1;
}