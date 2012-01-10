#pragma once

#include <lambda_p_io/analyzer/extension.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class global : public lambda_p_io::analyzer::extension
		{
		public:
			global (boost::shared_ptr <lambda_p::node> node_a);
			boost::shared_ptr <lambda_p::node> node;
			void operator () (lambda_p_io::analyzer::expression & expression_a) override;
		};
	}
}

