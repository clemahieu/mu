#pragma once

#include <lambda_p_script/fixed.h>

#include <map>

namespace lambda_p_script
{
	namespace bool_c
	{
		class create : public lambda_p_script::fixed
		{
		public:
			create ();
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			std::wstring name () override;
			std::map <std::wstring, boost::shared_ptr <lambda_p::node>> values;
		};
	}
}

