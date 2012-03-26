#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class mapping;
		}
	}
	namespace script
	{
		namespace synthesizer
		{
			class operationd : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				void map (boost::shared_ptr <mu::io::debugging::mapping> source_a, boost::shared_ptr <mu::io::debugging::mapping> target_a, boost::shared_ptr <mu::core::node> original_a, boost::shared_ptr <mu::core::node> new_a);
			};
		}
	}
}