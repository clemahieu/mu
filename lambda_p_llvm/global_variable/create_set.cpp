#include "create_set.h"

#include <lambda_p_llvm/constant/node.h>
#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/module/node.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

void lambda_p_llvm::global_variable::create_set::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::constant::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		auto result (boost::make_shared <lambda_p_llvm::global_variable::node> (new llvm::GlobalVariable (two->type->type (), true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, two->constant ()), boost::make_shared <lambda_p_llvm::pointer_type::node> (two->type)));
		one->module->getGlobalList ().push_back (result->global_variable ());
		results.push_back (result);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::global_variable::create_set::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::global_variable::create_set::name ()
{
	return std::wstring (L"lambda_p_llvm::global_variable::create_set");
}