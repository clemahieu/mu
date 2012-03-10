#include <typeinfo>

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
				trace_registration (mu::script::runtime::frame & frame_a, std::type_info const * info_a);
				~trace_registration ();
				mu::script::runtime::frame & frame;
			};
		}
	}
}