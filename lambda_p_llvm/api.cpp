#include "api.h"

#include <lambda_p/binder/structure.h>
#include <lambda_p_llvm/context_binder.h>
#include <lambda_p_llvm/type_binder.h>
#include <lambda_p_llvm/constant_int_binder.h>

#include <string>

lambda_p_llvm::api::api (::lambda_p_llvm::generation_context & context_a)
	: structure (new ::lambda_p::binder::structure),
    context (context_a)
{
	::std::wstring context_name (L"context");
	::boost::shared_ptr < ::lambda_p_llvm::context_binder> context_binder (new ::lambda_p_llvm::context_binder);
	structure->nodes [context_name] = context_binder;
	::std::wstring type_name (L"type");
	::boost::shared_ptr < ::lambda_p_llvm::type_binder> type_binder (new ::lambda_p_llvm::type_binder);
	structure->nodes [type_name] = type_binder;
    ::std::wstring constant_int_name (L"constant_int");
    ::boost::shared_ptr < ::lambda_p_llvm::constant_int_binder> constant_int_binder (new ::lambda_p_llvm::constant_int_binder (context));
    structure->nodes [constant_int_name] = constant_int_binder;
}

lambda_p_llvm::api::~api (void)
{
}
