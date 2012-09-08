#pragma once

namespace mu
{
    namespace script
    {
        namespace parser_scope
        {
            class node;
        }
    }
    namespace repl
    {
        class repl;
        class api
        {
        public:            
            static auto core (mu::repl::repl & repl_a) -> mu::script::parser_scope::node *;
        };
    }
}