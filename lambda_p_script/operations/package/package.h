#pragma once

#include <lambda_p_script/nodes/fixed.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	namespace operations
	{
		namespace package
		{
			class package : public lambda_p_script::nodes::fixed
			{
			public:
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
				std::wstring name () override;
				size_t count () override;
				std::map <std::wstring, boost::shared_ptr <lambda_p::node>> items;
			};
		}
	}
}

