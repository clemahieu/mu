#include "api.h"

#include <lambda_p/binder/package.h>
#include <lambda_p_llvm/context_binder.h>
#include <lambda_p_llvm/type_binder.h>
#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p_llvm/call_inst_binder.h>

#include <string>

lambda_p_llvm::api::api (::lambda_p_llvm::generation_context & context_a)
	: package (new ::lambda_p::binder::package),
    context (context_a)
{
	::std::wstring context_name (L"context");
	::boost::shared_ptr < ::lambda_p_llvm::context_binder> context_binder (new ::lambda_p_llvm::context_binder);
	package->nodes [context_name] = context_binder;
	::std::wstring type_name (L"type");
	::boost::shared_ptr < ::lambda_p_llvm::type_binder> type_binder (new ::lambda_p_llvm::type_binder);
	package->nodes [type_name] = type_binder;
    ::std::wstring constant_int_name (L"constant_int");
    ::boost::shared_ptr < ::lambda_p_llvm::constant_int_binder> constant_int_binder (new ::lambda_p_llvm::constant_int_binder (context));
    package->nodes [constant_int_name] = constant_int_binder;
	::std::wstring call_inst_name (L"call_inst");
	::boost::shared_ptr < ::lambda_p_llvm::call_inst_binder> call_inst_binder (new ::lambda_p_llvm::call_inst_binder (context));
	package->nodes [call_inst_name] = call_inst_binder;
}

lambda_p_llvm::api::~api (void)
{
}
