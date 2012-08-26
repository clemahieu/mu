#include <mu/llvm_/module_print.h>

#include <mu/llvm_/module_node.h>
#include <mu/script/astring_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/AssemblyAnnotationWriter.h>
#include <llvm/Module.h>

#include <gc_cpp.h>

bool mu::llvm_::module::print::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::module::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto result (new (GC) mu::script::astring::node);
		llvm::raw_string_ostream stream (result->string);
		llvm::AssemblyAnnotationWriter annotation;
		one->module->print (stream, &annotation);
		context_a.push (result);
	}
	return valid;
}