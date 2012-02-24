#pragma once

#include <mu/script/operation.h>
#include <lambda_p_llvm/execution_engine/node.h>

namespace llvm
{
	class Function;
}
namespace lambda_p_llvm
{
	namespace execution_engine
	{
		class node;
		class run_function : public mu::script::operation
		{
		public:
			void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
			void perform_internal (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <lambda_p_llvm::execution_engine::node> one, llvm::Function * function, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results);
			std::wstring name () override;
		};
	}
}

