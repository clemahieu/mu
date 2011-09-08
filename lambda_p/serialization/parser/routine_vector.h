#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace serialization
	{
		namespace parser
		{
			class routine_vector
			{
			public:
				routine_vector (void);
				~routine_vector (void);
				void operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine);
				::std::vector < ::boost::shared_ptr < ::lambda_p::core::routine> > routines;
			};
		}
	}
}