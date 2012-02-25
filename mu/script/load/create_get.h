#pragma once

#include <mu/script/fixed.h>

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
		namespace load
		{
			class create_get : public mu::script::fixed
			{
			public:
				create_get (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
			};
		}
	}
}

