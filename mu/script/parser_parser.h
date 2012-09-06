#pragma once

#include <boost/function.hpp>

#include <mu/core/types.h>
#include <mu/io/context.h>

namespace mu
{
    namespace core
    {
        class node;
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
        namespace parser_scope
        {
            class node;
        }
        namespace parser
        {
            class state;
            class parser
            {
            public:
                parser (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::ast::cluster *)> target_a, mu::script::parser_scope::node * scope_a);
                mu::core::errors::error_target & errors;
                boost::function <void (mu::script::ast::cluster *)> target;
                void operator () (mu::io::tokens::token const & token_a);
                mu::stack <mu::script::parser::state *> state;
                mu::script::parser_scope::node * scope;
            };
        }
    }
}