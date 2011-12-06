#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class list_binder : public lambda_p::binder::binder
		{
		public:
			void bind (lambda_p::core::expression * expression, std::map <lambda_p::core::expression *, boost::shared_ptr <lambda_p::binder::node>> & nodes, lambda_p::errors::error_list & problems) override;
			std::wstring binder_name () override;
		};
	}
}
