#include "get_type.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void mu::llvm_::value::get_type::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters_a [0]));
	if (one.get () != nullptr)
	{
		mu::llvm_::type::build build (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()), one->value ()->getType ());
		results_a.push_back (build.type);
	}
	else
	{
		invalid_type (errors_a, parameters_a [0], 0);
	}
}

size_t mu::llvm_::value::get_type::count ()
{
	return 1;
}