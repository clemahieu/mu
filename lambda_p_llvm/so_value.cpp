#include "so_value.h"

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>

lambda_p_llvm::so_value::so_value (llvm::Function * function_a)
	: function (function_a)
{
}

llvm::Type const * lambda_p_llvm::so_value::type ()
{
	return function->getFunctionType ()->getReturnType ();
}