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
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				std::vector <boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
