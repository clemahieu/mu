#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class null : public mu::core::errors::error_target
			{
			public:
				null ();
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				void operator () (std::wstring error) override;
				void operator () (wchar_t const * error) override;
				bool had_error;
			};
		}
	}
}