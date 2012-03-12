#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class operation;
		namespace debugging
		{
			class mapping
			{
			public:
				virtual std::wstring stacktrace (boost::shared_ptr <mu::script::operation> operation_a) = 0;
			};
		}
	}
}