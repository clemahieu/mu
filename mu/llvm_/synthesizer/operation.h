#pragma once

#include <mu/script/fixed.h>
#include <mu/llvm_/analyzer/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace synthesizer
		{
			class operation : public mu::script::fixed
			{
			public:
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;			
				mu::llvm_::analyzer::operation analyzer;
			};
		}
	}
}
