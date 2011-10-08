#include "function.h"

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>

lambda_p_llvm::function::function (::llvm::Function * function_a)
	: function_m (function_a)
{
}

::llvm::FunctionType const * lambda_p_llvm::function::function_type ()
{
	return function_m->getFunctionType ();
}

::llvm::Type const * lambda_p_llvm::function::type ()
{
	return function_m->getType ();
}