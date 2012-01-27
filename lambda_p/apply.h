#pragma once

#include <lambda_p/segment.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	namespace apply
	{
		void merge (lambda_p::segment <boost::shared_ptr <lambda_p::node>> target, lambda_p::segment <boost::shared_ptr <lambda_p::node>> source);
	}
}
