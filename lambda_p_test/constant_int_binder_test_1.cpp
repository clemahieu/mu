#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "constant_int_binder_test_1.h"

#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/binder/bind_procedure.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/core/association.h>

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
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	size_t binder = routine->add_declaration ();
	routine->surface->results.push_back (binder);
	::lambda_p::core::statement * statement = routine->add_statement (binder);
	size_t declaration = routine->add_declaration ();
	statement->association->results.push_back (declaration);
	size_t base = routine->add_data (::std::wstring (L"16"));
	statement->association->parameters.push_back (base);
	size_t number = routine->add_data (::std::wstring (L"10"));
	statement->association->parameters.push_back (number);
	size_t bits = routine->add_data (::std::wstring (L"64"));
	statement->association->parameters.push_back (bits);
	::lambda_p::binder::bind_procedure bind_procedure (routine);
	::llvm::LLVMContext llvm_context;
	::lambda_p_llvm::generation_context context (llvm_context, NULL, NULL);
	::boost::shared_ptr < ::lambda_p_llvm::constant_int_binder> constant_int_binder (new ::lambda_p_llvm::constant_int_binder (context));
	bind_procedure.routine->instances [binder] = constant_int_binder;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	bind_procedure (problems);
	assert (problems.empty ());
	assert (bind_procedure.routine->instances [declaration].get () != NULL);
	assert (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (bind_procedure.routine->instances [declaration]).get () != NULL);
	assert (::boost::static_pointer_cast < ::lambda_p_llvm::value> (bind_procedure.routine->instances [declaration])->operator() () != NULL);
	assert (::llvm::isa < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (bind_procedure.routine->instances [declaration])->operator() ()));
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (bind_procedure.routine->instances [declaration])->operator() ())->getBitWidth () == 64);
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (bind_procedure.routine->instances [declaration])->operator() ())->getValue () == 16);
}