#pragma once

#include <mu/io/keywording/state.h>

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
        namespace keywording
        {
            class keywording;
        }
		namespace ast
		{
			class node;
			class cluster;
		}
	}
	namespace script
	{
		namespace ast
		{
			class extension : public mu::io::keywording::state
			{
			public:
                extension (mu::io::keywording::keywording & keywording_a);
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
				mu::io::ast::cluster * core (mu::core::errors::error_target & errors_a, mu::io::ast::node * node_a);
                mu::io::keywording::keywording & keywording;
			};
		}
	}
}
