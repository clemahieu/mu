#pragma once

#include <lambda_p_io/analyzer/extension.h>

#include <map>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class bool_c;
	}
	namespace extensions
	{
		class bool_c : public lambda_p_io::analyzer::extensions
		{
		public:
			bool_c ();
			std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a) override;	
			std::map <std::wstring, boost::shared_ptr <lambda_p_kernel::nodes::bool_c>> map;
		};
	}
}

