#pragma once

#include <lambda_p_script/fixed.h>

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	class routine;
	class cluster : public lambda_p_script::fixed
	{
	public:
		cluster (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a);
		cluster (std::map <std::wstring, size_t> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a);
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
		size_t count () override;
		std::map <std::wstring, size_t> names;
		std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	};
}

