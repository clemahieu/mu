#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class context;
        namespace debugging
        {
            class call_info;
        }
		namespace runtime
		{
			class trace
			{
			public:
				trace (mu::script::context & context_a, boost::shared_ptr <mu::script::debugging::call_info> node_a);
				~trace ();
				mu::script::context & context;
			};
		}
	}
}