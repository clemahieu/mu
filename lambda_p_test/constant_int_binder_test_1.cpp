#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "constant_int_binder_test_1.h"

#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/builder.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_kernel/apply.h>

#include <llvm/LLVMContext.h>
#include <llvm/Constants.h>

lambda_p_test::constant_int_binder_test_1::constant_int_binder_test_1(void)
{
}

lambda_p_test::constant_int_binder_test_1::~constant_int_binder_test_1(void)
{
}

void lambda_p_test::constant_int_binder_test_1::run ()
{
	lambda_p::builder builder;
	builder (L"res; binder context number bits; binder context number bits; res; :;");
	auto nodes (boost::shared_ptr <lambda_p::binder::list> (new lambda_p::binder::list));
	nodes->operator[] (0) = boost::shared_ptr <lambda_p_llvm::constant_int_binder> (new lambda_p_llvm::constant_int_binder);
	nodes->operator[] (1) = boost::shared_ptr <lambda_p_llvm::context> (new lambda_p_llvm::context);
	nodes->operator[] (2) = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (16));
	nodes->operator[] (3) = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (64));
	lambda_p::errors::error_list problems;
	lambda_p_kernel::apply apply;
	lambda_p::binder::list declarations;
	apply.core (builder.routines.routines->operator[] (0), *nodes, problems, declarations);
	assert (problems.errors.empty ());
	assert (declarations.nodes.size () == 1);
	assert (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0]).get () != nullptr);
	assert (boost::static_pointer_cast <lambda_p_llvm::value> (declarations [0])->operator() () != nullptr);
	assert (llvm::isa <llvm::ConstantInt> (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0])->operator() ()));
	assert (llvm::cast <llvm::ConstantInt> (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0])->operator() ())->getBitWidth () == 64);
	assert (llvm::cast <llvm::ConstantInt> (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0])->operator() ())->getValue () == 16);
}