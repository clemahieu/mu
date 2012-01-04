#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	namespace core
	{
		class scatter : public lambda_p::core::target
		{
		public:
			scatter (size_t required_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::target>> & operator [] (size_t index);
		private:
			void perform (std::vector <boost::shared_ptr <lambda_p::core::node>> arguments);
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::target>>> targets;
			size_t required;
		};
	}
}

