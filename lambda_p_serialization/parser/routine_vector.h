#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_serialization
{
	namespace parser
	{
		class routine_vector
		{
		public:
			routine_vector ();
			void operator () (boost::shared_ptr <lambda_p::core::routine> routine);
			boost::shared_ptr <std::vector <boost::shared_ptr <lambda_p::core::routine>>> routines;
		};
	}
}
