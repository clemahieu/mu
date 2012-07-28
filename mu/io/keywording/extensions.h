#pragma once

#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

#include <mu/core/types.h>

#include <map>

#include <gc_allocator.h>
#include <gc_cpp.h>

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace io
	{
        namespace keywording
        {
            class keywording;
            class state;
            typedef boost::function <mu::io::keywording::state * (mu::io::keywording::keywording &)> extension_factory;
            typedef boost::tuple <extension_factory, bool> extension_definition;
            class extensions
            {
            public:
                virtual ~extensions ();
                extensions ();
                extensions (std::map <mu::string, extension_definition, std::less <mu::string>, gc_allocator <std::pair <mu::string, extension_definition>>> extensions_a);
                extension_factory operator () (mu::string const & string);
                template <typename T>
                bool add (mu::string const & string)
                {
                    (*this) (string,
                             [] (mu::io::keywording::keywording & keywording_a)
                             {
                                 return new (GC) T (keywording_a);
                             }, T::dominating);
                }
                bool operator () (mu::string const & string, mu::io::keywording::extension_factory extension, bool dominating_a);
                bool operator () (mu::string const & string, mu::core::node * node_a);
            private:
                std::map <mu::string, extension_definition, std::less <mu::string>, gc_allocator <std::pair <mu::string, extension_definition>>> extensions_m;
            };
		}
	}
}
