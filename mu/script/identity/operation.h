#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace identity
		{
			class operation : public mu::script::operation
			{
			public:
				void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				std::wstring name () override;
			};
		}
	}
}
