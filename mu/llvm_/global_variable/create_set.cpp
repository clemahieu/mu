#include <mu/llvm_/global_variable/create_set.h>

#include <mu/llvm_/constant/node.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

#include <gc_cpp.h>

bool mu::llvm_::global_variable::create_set::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::module::node, mu::llvm_::constant::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::constant::node *> (context_a.parameters (1)));
		auto result (new (GC) mu::llvm_::global_variable::node (new llvm::GlobalVariable (two->type->type (), true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, two->constant ()), new (GC) mu::llvm_::pointer_type::node (two->type)));
		one->module->getGlobalList ().push_back (result->global_variable ());
		context_a.push (result);
	}
	return result;
}

std::wstring mu::llvm_::global_variable::create_set::name ()
{
	return std::wstring (L"mu::llvm_::global_variable::create_set");
}