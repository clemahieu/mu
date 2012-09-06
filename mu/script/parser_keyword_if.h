#pragma once

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
            class if_expression;
        }
        namespace parser
        {
            class routine;
            enum class keyword_if_state
            {
                initial,
                predicate,
                true_branch,
                false_branch,
                name,
                have_name,
                elements
            };
            class keyword_if : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                keyword_if (mu::script::parser::routine & routine_a, mu::script::ast::if_expression * expression_a);
                void operator () (mu::io::tokens::token * token_a) override;
				void operator () (mu::io::tokens::divider const & token) override;
				void operator () (mu::io::tokens::identifier const & token) override;
				void operator () (mu::io::tokens::left_square const & token) override;
				void operator () (mu::io::tokens::right_square const & token) override;
				void operator () (mu::io::tokens::stream_end const & token) override;
                void operator () (mu::io::tokens::value const & token) override;
                void process_left_square (mu::core::node_list & nodes_a);
                void process_value (mu::io::tokens::value const & token, mu::core::node_list & nodes_a);
                mu::script::parser::routine & routine;
                keyword_if_state state;
                mu::script::ast::if_expression * expression;
                size_t element;
            };
        }
    }
}