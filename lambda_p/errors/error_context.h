#pragma once

#include <lambda_p/errors/error_target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_context : public lambda_p::errors::error_target
		{
		public:
			error_context (boost::shared_ptr <lambda_p::errors::error_target> target_a, lambda_p::context context_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error> error, lambda_p::context context_a) override;
			bool operator () () override;
			void operator () (std::wstring error) override;
			void operator () (wchar_t const * error) override;
			boost::shared_ptr <lambda_p::errors::error_target> target;
			lambda_p::context context;
		};
	}
}

