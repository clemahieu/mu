#pragma once

#include <lambda_p_script/fixed.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_llvm
{
	namespace function_pointer
	{
		class node;
	}
	class cluster : public lambda_p_script::fixed
	{
	public:
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
		size_t count () override;
		std::map <std::wstring, size_t> names;
		std::vector <boost::shared_ptr <lambda_p_llvm::function_pointer::node>> routines;
	};
}

