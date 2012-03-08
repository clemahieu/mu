#include "print.h"

#include <mu/llvm_/module/node.h>
#include <mu/script/astring/node.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/AssemblyAnnotationWriter.h>
#include <llvm/Module.h>

#include <boost/make_shared.hpp>

void mu::llvm_::module::print::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		auto result (boost::make_shared <mu::script::astring::node> ());
		llvm::raw_string_ostream stream (result->string);
		llvm::AssemblyAnnotationWriter annotation;
		one->module->print (stream, &annotation);
		context_a.results.push_back (result);
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::module::print::count ()
{
	return 1;
}