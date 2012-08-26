#pragma once

#include <mu/core/node.h>

namespace mu
{
	namespace io
	{
		namespace keywording
        {
            class extensions;
		}
	}
	namespace script
	{
		namespace extensions
		{
			class node : public mu::core::node
			{
			public:
				node ();
				node (mu::io::keywording::extensions * extensions_a);
				mu::io::keywording::extensions * extensions;
				mu::string name () override;
			};
		}
	}
}

