#pragma once

#include <mu/core/errors/error_target.h>

#include <boost/shared_ptr.hpp>

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
		class context;
		namespace debugging
		{
			class trace_target : public mu::core::errors::error_target
			{
			public:
				trace_target (boost::shared_ptr <mu::core::errors::error_target> target_a, mu::script::context & context_a, boost::shared_ptr <mu::io::debugging::mapping> mapping_a);
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				boost::shared_ptr <mu::core::errors::error_target> target;
				mu::script::context & context;
				boost::shared_ptr <mu::io::debugging::mapping> mapping;
			};
		}
	}
}