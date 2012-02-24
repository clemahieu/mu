#include "create.h"

#include <boost/make_shared.hpp>

#include <mu/llvm_/synthesizer/operation.h>

void mu::llvm_::synthesizer::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.push_back (boost::make_shared <mu::llvm_::synthesizer::operation> ());
}

size_t mu::llvm_::synthesizer::create::count ()
{
	return 0;
}