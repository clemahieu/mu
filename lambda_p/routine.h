#pragma once

#include <lambda_p/context.h>
#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
	class routine : public lambda_p::node
	{
	public:
		routine (lambda_p::context context_a);
		routine (boost::shared_ptr <lambda_p::expression> body_a);
		void operator () (lambda_p::visitor * visitor_a) override;
		std::wstring name () override;
		boost::shared_ptr <lambda_p::expression> body;
	};
}

