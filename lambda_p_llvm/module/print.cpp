#include "print.h"

#include <lambda_p_llvm/module/node.h>
#include <mu/script/astring/node.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/AssemblyAnnotationWriter.h>
#include <llvm/Module.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::module::print::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto result (boost::make_shared <mu::script::astring::node> ());
		llvm::raw_string_ostream stream (result->string);
		llvm::AssemblyAnnotationWriter annotation;
		one->module->print (stream, &annotation);
		results.push_back (result);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::module::print::count ()
{
	return 1;
}