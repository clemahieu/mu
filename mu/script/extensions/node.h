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
				node (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
				std::wstring name () override;
			};
		}
	}
}

