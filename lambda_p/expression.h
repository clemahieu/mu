#pragma once

#include <lambda_p/node.h>
#include <lambda_p/context.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression : public lambda_p::node
	{
	public:
		expression (lambda_p::context context_a);
		lambda_p::context context;
		std::vector <boost::shared_ptr <lambda_p::node>> dependencies;
		void operator () (lambda_p::visitor * visitor_a) override;
	};
}

