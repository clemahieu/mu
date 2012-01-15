#pragma once

#include <lambda_p/visitor.h>

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class reference;
	class node;
	class expression;
}
namespace lambda_p_script_io
{
	class order : public lambda_p::visitor
	{
	public:
		order (boost::shared_ptr <lambda_p::expression> expression_a, boost::shared_ptr <lambda_p::expression> parameters);
		void operator () (boost::shared_ptr <lambda_p::expression> expression_a);
		void operator () (lambda_p::set * set_a) override;
		void operator () (lambda_p::call * call_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::node * node_a) override;
		boost::shared_ptr <lambda_p::node> current;
		std::set <boost::shared_ptr <lambda_p::expression>> already;
		std::vector <boost::shared_ptr <lambda_p::expression>> expressions;
	};
}

