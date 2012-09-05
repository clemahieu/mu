#pragma once

#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

#include <mu/core/types.h>

#include <gc_cpp.h>

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace io
	{
        namespace analyzer
        {
            class analyzer;
            class state;
            typedef boost::function <mu::io::analyzer::state * (mu::io::analyzer::analyzer &)> extension_factory;
            typedef boost::tuple <extension_factory, bool> extension_definition;
            class extensions
            {
            public:
                extensions ();
                extensions (mu::map <mu::string, extension_definition> extensions_a);
                boost::tuple <extension_factory, mu::string> operator () (mu::string const & string);
                template <typename T>
                bool add (mu::string const & string)
                {
                    auto result ((*this) (string,
                                        []
                                        (mu::io::analyzer::analyzer & analyzer_a)
                                        {
                                            return new (GC) T (analyzer_a);
                                        }, T::dominating));
                    return result;
                }
                bool operator () (mu::string const & string, mu::io::analyzer::extension_factory extension, bool dominating_a);
                bool operator () (mu::string const & string, mu::core::node * node_a);
                mu::map <mu::string, extension_definition> extensions_m;
            };
		}
	}
}
