#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

namespace mu
{
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class extension;
				class extensions
				{
				public:
                    virtual ~extensions ();
					extensions ();
					extensions (std::map <std::wstring, mu::io::analyzer::extensions::extension *, std::less <std::wstring>, gc_allocator <std::pair <std::wstring, mu::io::analyzer::extensions::extension *>>> extensions_a);
					std::map <std::wstring, mu::io::analyzer::extensions::extension *, std::less <std::wstring>, gc_allocator <std::pair <std::wstring, mu::io::analyzer::extensions::extension *>>> extensions_m;
				};
			}
		}
	}
}
