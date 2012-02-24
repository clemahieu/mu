#include "create.h"

#include <mu/llvm_/context/value.h>

void mu::llvm_::context::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::context::value));
}

size_t mu::llvm_::context::create::count ()
{
	return 0;
}

std::wstring mu::llvm_::context::create::name ()
{
	return std::wstring (L"mu::llvm_::context::create");
}