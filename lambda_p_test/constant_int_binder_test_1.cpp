#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "constant_int_binder_test_1.h"

#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/number.h>

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

	boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t binder = routine->add_declaration ();
	routine->surface->results.push_back (binder);
	lambda_p::core::statement * statement = routine->add_statement ();
	statement->target = binder;
	size_t declaration = routine->add_declaration ();
	statement->association->results.push_back (declaration);
	size_t number = routine->add_declaration ();
	statement->association->parameters.push_back (number);
	size_t bits = routine->add_declaration ();
	statement->association->parameters.push_back (bits);
	llvm::LLVMContext llvm_context;
	lambda_p_llvm::generation_context context (llvm_context, nullptr, nullptr);
	boost::shared_ptr < lambda_p_llvm::constant_int_binder> constant_int_binder (new lambda_p_llvm::constant_int_binder (context));
	lambda_p::binder::node_list nodes;
	nodes [binder] = constant_int_binder;
	nodes [number] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (16));
	nodes [bits] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (64));
	lambda_p::errors::error_list problems;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [declaration].get () != nullptr);
	assert (boost::dynamic_pointer_cast <lambda_p_llvm::value> (nodes [declaration]).get () != nullptr);
	assert (boost::static_pointer_cast <lambda_p_llvm::value> (nodes [declaration])->operator() () != nullptr);
	assert (llvm::isa <llvm::ConstantInt> (boost::static_pointer_cast <lambda_p_llvm::value> (nodes [declaration])->operator() ()));
	assert (llvm::cast <llvm::ConstantInt> (boost::static_pointer_cast <lambda_p_llvm::value> (nodes [declaration])->operator() ())->getBitWidth () == 64);
	assert (llvm::cast <llvm::ConstantInt> (boost::static_pointer_cast <lambda_p_llvm::value> (nodes [declaration])->operator() ())->getValue () == 16);
}