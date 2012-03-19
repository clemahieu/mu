#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class errors : public mu::core::errors::error_target
			{
			public:
				errors (boost::shared_ptr <mu::core::errors::error_target> target_a);
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				void operator () (std::wstring error) override;
				void operator () (wchar_t const * error) override;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}