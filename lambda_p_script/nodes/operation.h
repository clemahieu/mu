#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	namespace nodes
	{
		class operation : public lambda_p::node
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) = 0;
			virtual std::wstring name () = 0;
			bool check_count (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, size_t expected);
			void invalid_type (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t position);
		};
	}
}

