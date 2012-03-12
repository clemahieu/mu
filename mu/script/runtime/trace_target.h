#include <mu/core/errors/error_target.h>

#include <typeinfo>
#include <vector>

namespace mu
{
	namespace script
	{
		class context;
		namespace debugging
		{
			class mapping;
		}
		namespace runtime
		{
			class trace_target : public mu::core::errors::error_target
			{
			public:
				trace_target (mu::script::context & context_a, mu::script::debugging::mapping & mapping_a, boost::shared_ptr <mu::core::errors::error_target> target_a);				
				void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				mu::script::debugging::mapping & mapping;
				mu::script::context & context;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}