#pragma once

#include <mu/script/fixed.h>

namespace mu
{
	namespace script
	{
		namespace values
		{
			class operation : public mu::script::fixed
			{
			public:
				operation ();
				operation (std::vector <boost::shared_ptr <mu::core::node>> values_a);
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				std::vector <boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
