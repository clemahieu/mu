#pragma once

#include <lambda_p_io/analyzer/declaration.h>

namespace lambda_p
{
	class scatter;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class individual : public lambda_p_io::analyzer::declaration
		{
		public:
			individual (boost::shared_ptr <lambda_p::scatter> scatter_a, size_t index_a);
			void operator () (boost::shared_ptr <lambda_p::target> target_a) override;
			boost::shared_ptr <lambda_p::scatter> scatter;
			size_t index;
		};
	}
}

