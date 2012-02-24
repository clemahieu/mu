#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace package
		{
			class add : public mu::script::fixed
			{
			public:
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				std::wstring name () override;
				size_t count () override;
			};
		}
	}
}
