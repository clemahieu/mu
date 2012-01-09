#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	class call;
}
namespace lambda_p_script
{
	namespace runtime
	{
		class routine;
	}
	namespace synthesizer
	{
		class routine;
		class generator
		{
		public:
			generator (lambda_p_script::synthesizer::routine & routine_a);
			boost::shared_ptr <lambda_p_script::runtime::routine> result;
			std::map <boost::shared_ptr <lambda_p::call>, size_t> reservation;
		};
	}
}

