#pragma once

#include <mu/script_runtime/operation.h>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace values
		{
			class operation : public mu::script_runtime::operation
			{
			public:
				operation ();
				operation (std::vector <boost::shared_ptr <mu::core::node>> values_a);
				bool operator () (mu::script_runtime::context & context_a) override;
				std::vector <boost::shared_ptr <mu::core::node>> values;
			};
		}
	}
}
