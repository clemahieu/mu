#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/check.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::integer_type::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::context::node, mu::llvm_::apint::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::apint::node> (context_a.parameters [1]));
		auto bits (two->value->getLimitedValue ());
		if (bits >= llvm::IntegerType::MIN_INT_BITS && bits <= llvm::IntegerType::MAX_INT_BITS)
		{
			context_a.results.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (*one->context, bits)));
		}
		else
		{
			std::wstringstream message;
			message << L"Bits is not within bounds: ";
			message << llvm::IntegerType::MIN_INT_BITS;
			message << L" <= ";
			message << two->value;
			message << L" <= ";
			message << llvm::IntegerType::MAX_INT_BITS;
			(*context_a.errors) (message.str ());
		}
	}
}

size_t mu::llvm_::integer_type::create::count ()
{
	return 2;
}

std::wstring mu::llvm_::integer_type::create::name ()
{
	return std::wstring (L"mu::llvm_::integer_type::create");
}