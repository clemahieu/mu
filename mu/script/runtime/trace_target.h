#include <mu/core/errors/error_target.h>

#include <typeinfo>
#include <vector>

namespace mu
{
	namespace script
	{
		class context;
		namespace runtime
		{
			class trace_target : public mu::core::errors::error_target
			{
			public:
				trace_target (mu::script::context & context_a, boost::shared_ptr <mu::core::errors::error_target> target_a);				
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				mu::script::context & context;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}