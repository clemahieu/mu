#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class scatter : public lambda_p::core::target
		{
		public:
			scatter ();
			void set_required (size_t required_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::target>> & operator [] (size_t index);
		private:
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::target>>> targets;
			size_t required;
		};
	}
}

