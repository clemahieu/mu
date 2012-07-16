#pragma once

#include <mu/core/types.h>

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
					extensions (std::map <mu::string, mu::io::analyzer::extensions::extension *, std::less <mu::string>, gc_allocator <std::pair <mu::string, mu::io::analyzer::extensions::extension *>>> extensions_a);
                    mu::io::analyzer::extensions::extension * operator () (mu::string const & string);
                    bool operator () (mu::string const & string, mu::io::analyzer::extensions::extension * extension);
                private:
					std::map <mu::string, mu::io::analyzer::extensions::extension *, std::less <mu::string>, gc_allocator <std::pair <mu::string, mu::io::analyzer::extensions::extension *>>> extensions_m;
				};
			}
		}
	}
}
