#pragma once

#include <lambda_p/visitor.h>

#include <set>
#include <list>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
	class parameters;
	class reference;
	class node;
}
namespace lambda_p_script_io
{
	class order : public lambda_p::visitor
	{
	public:
		order (boost::shared_ptr <lambda_p::call> call_a);
		void operator () (boost::shared_ptr <lambda_p::call> call_a);
		void operator () (lambda_p::call * call_a) override;
		void operator () (lambda_p::parameters * parameters_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::node * node_a) override;
		boost::shared_ptr <lambda_p::node> current;
		std::set <boost::shared_ptr <lambda_p::call>> already;
		std::list <boost::shared_ptr <lambda_p::call>> expressions;
	};
}

