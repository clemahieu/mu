#pragma once

#include <mu/script/fixed.h>
#include <lambda_p_llvm/analyzer/operation.h>

namespace lambda_p_llvm
{
	namespace synthesizer
	{
		class operation : public mu::script::fixed
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			size_t count () override;			
			lambda_p_llvm::analyzer::operation analyzer;
		};
	}
}

