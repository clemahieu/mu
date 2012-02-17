#pragma once

#include <lambda_p_script/fixed.h>
#include <lambda_p_llvm/analyzer/operation.h>

namespace lambda_p_llvm
{
	namespace synthesizer
	{
		class operation : public lambda_p_script::fixed
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;			
			lambda_p_llvm::analyzer::operation analyzer;
		};
	}
}

