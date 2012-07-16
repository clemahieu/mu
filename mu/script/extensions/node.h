#pragma once

#include <mu/core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class extensions;
			}
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
				node (mu::io::analyzer::extensions::extensions * extensions_a);
				mu::io::analyzer::extensions::extensions * extensions;
				mu::string name () override;
			};
		}
	}
}

