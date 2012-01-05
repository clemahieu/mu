#pragma once

#include <lambda_p_io/analyzer/extension.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
}
namespace lambda_p_script
{
	namespace nodes
	{
		class parameters;
	}
	namespace extensions
	{
		class parameters : public lambda_p_io::analyzer::extension
		{
		public:
			void operator () (lambda_p_io::analyzer::expression & expression_a) override;
			void count_checked (lambda_p_io::analyzer::expression & expression_a);
			std::map <boost::shared_ptr <lambda_p::expression>, boost::shared_ptr <lambda_p_script::nodes::parameters>> counts;
		};
	}
}

