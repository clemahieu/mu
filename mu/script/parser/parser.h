#pragma once

#include <boost/function.hpp>

#include <mu/core/types.h>
#include <mu/io/debugging/context.h>

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
    }
    namespace script
    {
        namespace ast
        {
            class cluster;
        }
        namespace parser
        {
            class state;
            class parser
            {
            public:
                parser (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::ast::cluster *)> target_a);
                mu::core::errors::error_target & errors;
                boost::function <void (mu::script::ast::cluster *)> target;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a);
                mu::stack <mu::script::parser::state *> state;
            };
        }
    }
}