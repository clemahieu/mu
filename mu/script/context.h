#include <mu/core/context.h>

namespace mu
{
    namespace script
    {
        class context : public mu::core::context
        {
        public:
			context ();
			context (mu::core::errors::error_target & errors_a);
			bool operator () ();
			void enter ();
			void leave ();
        };
    }
}