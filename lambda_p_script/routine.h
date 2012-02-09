#pragma once

#include <lambda_p_script/operation.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	class call;
	class remapping;
	class routine : public lambda_p_script::operation
	{
	public:
		routine (boost::shared_ptr <lambda_p_script::remapping> remapping_a);
		void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
		std::wstring name () override;
		boost::shared_ptr <lambda_p_script::remapping> remapping;
		std::vector <boost::shared_ptr <lambda_p_script::call>> calls;
	};
}

