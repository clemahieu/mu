#include <mu/llvm_/constant_string/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/string_node.h>
#include <mu/llvm_/global_variable/create_set.h>
#include <mu/llvm_/constant/create_from_string.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/array_type/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <gc_cpp.h>

bool mu::llvm_::constant_string::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::context::node, mu::llvm_::module::node, mu::script::string::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::module::node *> (context_a.parameters (1)));
		auto three (static_cast <mu::script::string::node *> (context_a.parameters (2)));
		context_a.push (new (GC) mu::llvm_::constant::create_from_string);
		context_a.push (one);
		context_a.push (new (GC) mu::script::string::node (three->string));
		auto valid (context_a ());
		assert (valid);
		context_a.slide ();
		context_a.push (new (GC) mu::llvm_::global_variable::create_set);
		context_a.push (two);
		context_a.push (context_a.locals_begin (), context_a.locals_end ());
		valid = context_a ();
		if (valid)
		{
			auto global (static_cast <mu::llvm_::global_variable::node *> (context_a.working (0)));
			auto var (global->global_variable ());
			auto pointer_type (static_cast <mu::llvm_::pointer_type::node *> (global->type));
			auto array_type (static_cast <mu::llvm_::array_type::node *> (pointer_type->element));
			auto result (new (GC) mu::llvm_::value::node (llvm::ConstantExpr::getBitCast (var, llvm::PointerType::get (array_type->element->type (), 0)), new (GC) mu::llvm_::pointer_type::node (array_type->element)));
			context_a.drop ();
			context_a.push (result);
		}
	}
	return valid;
}