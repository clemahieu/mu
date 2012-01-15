#pragma once

#include <lambda_p_io/analyzer/extension.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_io
{
	class lambda : public lambda_p_io::analyzer::extension
	{
	public:
		void operator () (lambda_p_io::analyzer::expression & expression_a) override;
		void add (lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <lambda_p::routine> routine_a);
	};
}

