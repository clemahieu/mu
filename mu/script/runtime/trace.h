#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class operation;
		class context;
		namespace runtime
		{
			class trace
			{
			public:
				trace (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> node_a);
				~trace ();
				mu::script::context & context;
			};
		}
	}
}