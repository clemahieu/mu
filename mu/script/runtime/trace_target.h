#include <mu/core/errors/error_target.h>

#include <typeinfo>
#include <vector>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_target;
		}
	}
	namespace script
	{
		namespace runtime
		{
			class trace_target : public mu::core::errors::error_target
			{
			public:
				trace_target (std::vector <std::type_info const *> & types_a, boost::shared_ptr <mu::core::errors::error_target> target_a);				
				void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				std::vector <std::type_info const *> & types;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}