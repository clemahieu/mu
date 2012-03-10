#include <typeinfo>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class frame;
			class trace_registration
			{
			public:
				trace_registration (std::vector <std::type_info const *> & stack_a, std::type_info const * info_a);
				~trace_registration ();
				std::vector <std::type_info const *> & stack;
			};
		}
	}
}