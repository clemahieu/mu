#pragma once

#include <lambda_p/target.h>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
	class scatter : public lambda_p::target
	{
	public:
		scatter (size_t required_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a);
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) override;
		std::vector <boost::shared_ptr <lambda_p::target>> & operator [] (size_t index);
	private:
		void perform (std::vector <boost::shared_ptr <lambda_p::node>> arguments);
		boost::shared_ptr <lambda_p::errors::error_target> errors;
		std::vector <std::vector <boost::shared_ptr <lambda_p::target>>> targets;
		size_t required;
	};
}

