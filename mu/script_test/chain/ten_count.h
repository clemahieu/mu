#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script_test
	{
		namespace chain
		{
			class ten_count : public mu::script::fixed
			{
			public:
				ten_count ();
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				size_t count_m;
			};
		}
	}
}
