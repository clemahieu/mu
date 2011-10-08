#include "literal_value.h"

lambda_p_llvm::literal_value::literal_value(::llvm::Value * value_a)
	: value (value_a)
{
}

::llvm::Value * lambda_p_llvm::literal_value::operator () ()
{
	return value;
}

::llvm::Type const * lambda_p_llvm::literal_value::type ()
{
	return value->getType ();
}