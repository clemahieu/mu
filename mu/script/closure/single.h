#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class single : public mu::script::operation
			{
			public:
				single (boost::shared_ptr <mu::script::operation> operation_a);
				single (std::vector <boost::shared_ptr <mu::core::node>> & closed_a, boost::shared_ptr <mu::script::operation> operation_a);
				void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				std::wstring name () override;
				boost::shared_ptr <mu::script::operation> operation_m;
				std::vector <boost::shared_ptr <mu::core::node>> closed;
			};
		}
	}
}
