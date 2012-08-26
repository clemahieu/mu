#pragma once

#include <mu/io/tokens_token.h>

namespace mu
{
    namespace core
    {
        class node;
    }
    namespace io
    {
        namespace tokens
        {
            class value : public mu::io::tokens::token
            {
            public:
                value (mu::io::context const & context_a, mu::core::node * node_a);
				mu::string token_name () override;
				void operator () (mu::io::tokens::visitor * visitor_a) override;
                mu::core::node * node;
            };
        }
    }
}