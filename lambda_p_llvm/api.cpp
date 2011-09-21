#include "api.h"

#include <lambda_p/binder/structure.h>
#include <lambda_p_llvm/context_binder.h>
#include <lambda_p_llvm/type_binder.h>

#include <string>

lambda_p_llvm::api::api (void)
	: structure (new ::lambda_p::binder::structure)
{
	::std::wstring context_name (L"context");
	::boost::shared_ptr < ::lambda_p_llvm::context_binder> context_binder (new ::lambda_p_llvm::context_binder);
	structure->nodes [context_name] = context_binder;
	::std::wstring type_name (L"type");
	::boost::shared_ptr < ::lambda_p_llvm::type_binder> type_binder (new ::lambda_p_llvm::type_binder);
	structure->nodes [type_name] = type_binder;
}

lambda_p_llvm::api::~api (void)
{
}
