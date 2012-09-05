#pragma once

#include <mu/io/context.h>

#include <boost/function.hpp>

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
        namespace analyzer
        {
            class extensions;
            class state;
            class analyzer
            {
            public:
                analyzer (mu::core::errors::error_target & errors_a, boost::function <void (mu::io::tokens::token *)> target_a, mu::io::analyzer::extensions * extensions_a);
                void operator () (mu::io::tokens::token * token_a);
                boost::function <void (mu::io::tokens::token *)> target;
                mu::stack <mu::io::analyzer::state *> state;
				mu::io::analyzer::extensions * extensions;
                mu::core::errors::error_target & errors;
            };
        }
    }
}