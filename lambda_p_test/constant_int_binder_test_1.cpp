#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "constant_int_binder_test_1.h"

#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/binder/routine_binder.h>
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
	::lambda_p::core::declaration * binder = routine->add_declaration ();
	routine->surface->results.push_back (binder);
	::lambda_p::core::statement * statement = routine->add_statement (binder);
	::lambda_p::core::declaration * declaration = routine->add_declaration ();
	statement->association->results.push_back (declaration);
	::lambda_p::core::declaration * base = routine->add_data (::std::wstring (L"16"));
	statement->association->parameters.push_back (base);
	::lambda_p::core::declaration * number = routine->add_data (::std::wstring (L"10"));
	statement->association->parameters.push_back (number);
	::lambda_p::core::declaration * bits = routine->add_data (::std::wstring (L"64"));
	statement->association->parameters.push_back (bits);
	::lambda_p::binder::routine_binder routine_binder (routine);
	::llvm::LLVMContext llvm_context;
	::lambda_p_llvm::generation_context context (llvm_context, NULL, NULL);
	::boost::shared_ptr < ::lambda_p_llvm::constant_int_binder> constant_int_binder (new ::lambda_p_llvm::constant_int_binder (context));
	routine_binder.instances [binder] = constant_int_binder;
	routine_binder ();
	assert (!routine_binder.error ());
	assert (routine_binder.instances.find (declaration) != routine_binder.instances.end ());
	assert (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration]).get () != NULL);
	assert (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m != NULL);
	assert (::llvm::isa < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m));
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m)->getBitWidth () == 64);
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m)->getValue () == 16);
}