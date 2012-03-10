#include <mu/core/errors/error.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error;
		}
	}
	namespace script
	{
		namespace runtime
		{
			class stacktrace_error : public mu::core::errors::error
			{
			public:
				stacktrace_error (std::vector <std::type_info const *> & types_a, boost::shared_ptr <mu::core::errors::error> error_a);
				mu::core::errors::error_id error_type () override;
				void string (std::wostream & stream) override;
				std::vector <std::wstring> types;
				boost::shared_ptr <mu::core::errors::error> error;
			};
		}
	}
}
