#include <mu/llvm_/pointer_type.create.h>

#include <mu/llvm_/pointer_type.node.h>
#include <mu/core/errors.error_target.h>
#include <mu/llvm_/context.node.h>
#include <mu/llvm_/apint.node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::pointer_type::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::type::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <mu::llvm_::pointer_type::node> (one));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::pointer_type::create::count ()
{
	return 1;
}
