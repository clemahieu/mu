#include "fo_value.h"

#include <llvm/Value.h>

lambda_p_llvm::fo_value::fo_value(llvm::Value * value_a)
	: value (value_a)
{
}

llvm::Value * lambda_p_llvm::fo_value::operator () ()
{
	return value;
}

llvm::Type const * lambda_p_llvm::fo_value::type ()
{
	return value->getType ();
}