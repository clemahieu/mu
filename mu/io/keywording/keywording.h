#pragma once

#include <mu/io/debugging/context.h>

#include <boost/function.hpp>

#include <stack>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
    namespace io
    {
        namespace tokens
        {
            class token;
        }
        namespace keywording
        {
            class extensions;
            class state;
            class keywording
            {
            public:
                keywording (mu::core::errors::error_target & errors_a, boost::function <void (mu::io::tokens::token *, mu::io::debugging::context)> target_a, mu::io::keywording::extensions * extensions_a);
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
                boost::function <void (mu::io::tokens::token *, mu::io::debugging::context)> target;
                std::stack <mu::io::keywording::state *> state;
				mu::io::keywording::extensions * extensions;
                mu::core::errors::error_target & errors;
            };
        }
    }
}