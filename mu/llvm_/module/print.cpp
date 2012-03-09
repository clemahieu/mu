#include "print.h"

#include <mu/llvm_/module/node.h>
#include <mu/script/astring/node.h>
#include <mu/script/check.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/AssemblyAnnotationWriter.h>
#include <llvm/Module.h>

#include <boost/make_shared.hpp>

void mu::llvm_::module::print::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		auto result (boost::make_shared <mu::script::astring::node> ());
		llvm::raw_string_ostream stream (result->string);
		llvm::AssemblyAnnotationWriter annotation;
		one->module->print (stream, &annotation);
		context_a.results.push_back (result);
	}
}