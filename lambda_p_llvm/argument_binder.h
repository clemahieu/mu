#pragma once

#include <vector>
#include <map>

#include <llvm/DerivedTypes.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace binder
	{
		class routine_instances;
		class instance;
	}
	namespace errors
	{
		class error;
	}
}
namespace lambda_p_kernel
{
	class list;
}
namespace lambda_p_llvm
{
	class argument_binder
	{
	public:
		argument_binder(void);
		void apply (::std::vector < ::llvm::Value *> & argument_values, ::boost::shared_ptr < lambda_p_kernel::list> arguments, ::llvm::FunctionType::param_iterator parameter, ::llvm::FunctionType::param_iterator parameter_end, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
	};
}

