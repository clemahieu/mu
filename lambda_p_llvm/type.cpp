#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "type.h"

lambda_p_llvm::type::type (llvm::Type const * type_a)
	: type_m (type_a)
{
}

lambda_p_llvm::type::~type (void)
{
}
