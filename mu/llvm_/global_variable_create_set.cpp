#include <mu/llvm_/global_variable_create_set.h>

#include <mu/llvm_/constant_node.h>
#include <mu/llvm_/global_variable_node.h>
#include <mu/llvm_/type_node.h>
#include <mu/llvm_/pointer_type_node.h>
#include <mu/llvm_/module_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

#include <gc_cpp.h>

bool mu::llvm_::global_variable::create_set::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::module::node, mu::llvm_::constant::node> (context_a));
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

mu::string mu::llvm_::global_variable::create_set::name ()
{
	return mu::string (U"mu::llvm_::global_variable::create_set");
}