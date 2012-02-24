#pragma once

#include <lambda_p_script/fixed.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	class routine;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	class routine;
}
namespace lambda_p_script_io
{
	class synthesizer : public lambda_p_script::fixed
	{
	public:
		void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
		size_t count () override;
		std::wstring name () override;
	};
}
