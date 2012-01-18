#pragma once

#include <lambda_p_script/operation.h>

#include <map>

namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class extension;
		}
	}
}
namespace lambda_p_script
{
	namespace exec
	{
		class operation : public lambda_p_script::operation
		{
		public:
			std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> * extensions;
			void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			std::wstring name () override;
		};
	}
}

