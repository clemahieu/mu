#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace io
	{
		namespace analyzer
        {
            class extensions;
		}
	}
	namespace script
	{
		namespace parser_scope
		{
			class node : public mu::core::node
			{
			public:
				node ();
				node (mu::io::analyzer::extensions * extensions_a);
				mu::io::analyzer::extensions * extensions;
                mu::map <mu::string, mu::core::node *> injected;
			};
		}
	}
}

