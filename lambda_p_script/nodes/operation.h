#pragma once

#include <lambda_p/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error_list;
	}
}
namespace lambda_p_script
{
	class context;
	namespace nodes
	{
		class operation
		{
		public:
			virtual size_t parameter_count () = 0;
			virtual size_t result_count () = 0;
			virtual void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, boost::shared_ptr <lambda_p::errors::error_list> errors_a, std::vector <size_t> parameter_locations, std::vector <size_t> result_locations) = 0;
			void execute (std::vector <boost::shared_ptr <lambda_p::node>> & context, boost::shared_ptr <lambda_p::errors::error_list> errors_a, std::vector <size_t> parameter_locations, std::vector <size_t> result_locations);
		};
	}
}
