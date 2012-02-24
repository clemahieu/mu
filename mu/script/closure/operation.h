#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class operation : public mu::script::fixed
			{
			public:
				operation (size_t count_a, boost::shared_ptr <mu::script::operation> operation_a);
				operation (boost::shared_ptr <mu::script::operation> operation_a, std::vector <size_t> & open_a, std::vector <boost::shared_ptr <mu::core::node>> & closed_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				std::wstring name () override;
				boost::shared_ptr <mu::script::operation> operation_m;
				std::vector <size_t> open;
				std::vector <boost::shared_ptr <mu::core::node>> closed;
			};
		}
	}
}
