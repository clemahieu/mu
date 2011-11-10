#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p_kernel
{
	class package;
}
namespace lambda_p_llvm
{
	class api
	{
	public:
		boost::shared_ptr <lambda_p_kernel::package> operator () ();
	};
}

