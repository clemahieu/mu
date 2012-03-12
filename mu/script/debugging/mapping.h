#include <mu/core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class operation;
		namespace debugging
		{
			class operation_info;
			class mapping : public mu::core::node
			{
			public:
				virtual boost::shared_ptr <mu::script::debugging::operation_info> operation_info (boost::shared_ptr <mu::script::operation> operation_a) = 0;
			};
		}
	}
}