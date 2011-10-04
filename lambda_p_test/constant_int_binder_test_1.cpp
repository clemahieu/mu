#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "constant_int_binder_test_1.h"

#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/data.h>
#include <lambda_p/core/reference.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>

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
	::lambda_p::core::statement * parameters = routine->add_statement ();
	::lambda_p::core::declaration * binder = routine->add_declaration ();
	parameters->add_argument (binder);
	::lambda_p::core::statement * statement = routine->add_statement ();
	::lambda_p::core::reference * reference = routine->add_reference (binder);
	statement->add_argument (reference);
	::lambda_p::core::declaration * declaration = routine->add_declaration ();
	statement->add_argument (declaration);
	::lambda_p::core::data * base = routine->add_data (::std::wstring (L"16"));
	statement->add_argument (base);
	::lambda_p::core::data * number = routine->add_data (::std::wstring (L"10"));
	statement->add_argument (number);
	::lambda_p::binder::routine_binder routine_binder;
	::llvm::LLVMContext llvm_context;
	::lambda_p_llvm::generation_context context (llvm_context, NULL, NULL);
	::boost::shared_ptr < ::lambda_p_llvm::constant_int_binder> constant_int_binder (new ::lambda_p_llvm::constant_int_binder (context));
	routine_binder.instances [binder] = constant_int_binder;
	routine_binder (routine);
	assert (!routine_binder.error ());
	assert (routine_binder.instances.find (declaration) != routine_binder.instances.end ());
	assert (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration]).get () != NULL);
	assert (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m != NULL);
	assert (::llvm::isa < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m));
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m)->getBitWidth () == 64);
	assert (::llvm::cast < ::llvm::ConstantInt> (::boost::static_pointer_cast < ::lambda_p_llvm::value> (routine_binder.instances [declaration])->value_m)->getValue () == 16);
}