#pragma once

#include <lambda_p/node.h>
#include <lambda_p/visitor.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class cluster;
	class link : public lambda_p::node
	{
	public:
		link (boost::shared_ptr <lambda_p::cluster> cluster_a, size_t index_a);
		void operator () (lambda_p::visitor * visitor_a) override;
		std::wstring name () override;
		boost::shared_ptr <lambda_p::cluster> cluster;
		size_t index;
	};
}

