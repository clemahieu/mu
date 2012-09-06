#pragma once

#include <boost/function.hpp>

#include <mu/script/parser_state.h>
#include <mu/io/tokens_visitor.h>

namespace mu
{
    namespace core
    {
        class node_list;
    }
    namespace script
    {
        namespace ast
        {
            class definite_expression;
        }
        namespace parser
        {
            enum class expression_state
            {
                values,
                name,
                have_name,
                elements
            };
            class routine;
            class expression : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                expression (mu::script::parser::routine & routine_a, mu::script::ast::definite_expression * expression_a);
                mu::script::ast::definite_expression * expression_m;
                mu::script::parser::expression_state state;
                mu::script::parser::routine & routine;
                size_t element;
                void operator () (mu::io::tokens::token * token_a) override;
				void operator () (mu::io::tokens::divider const & token) override;
				void operator () (mu::io::tokens::identifier const & token) override;
				void operator () (mu::io::tokens::left_square const & token) override;
				void operator () (mu::io::tokens::right_square const & token) override;
				void operator () (mu::io::tokens::stream_end const & token) override;
                void operator () (mu::io::tokens::value const & token) override;
            };
        }
    }
}