#pragma once

#include <lambda_p/core/target.h>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class scatter : public lambda_p::core::target
		{
		public:
			scatter (boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void set_required (size_t required_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::target>> & operator [] (size_t index);
		private:
			void perform (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments);
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::target>>> targets;
			size_t required;
		};
	}
}

