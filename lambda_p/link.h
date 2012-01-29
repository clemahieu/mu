#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
	class link : public lambda_p::node
	{
	public:
		link (boost::shared_ptr <lambda_p::routine> routine_a);
		void operator () (lambda_p::visitor * visitor_a) override;
		std::wstring name () override;
		boost::shared_ptr <lambda_p::routine> routine;
	};
}

