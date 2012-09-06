#include <mu/llvm_/integer_type_create.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context_node.h>
#include <mu/llvm_/apint_node.h>
#include <mu/llvm_/integer_type_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::integer_type::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::context::node, mu::llvm_::apint::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::apint::node *> (context_a.parameters (1)));
		auto bits (two->value->getLimitedValue ());
		if (bits >= llvm::IntegerType::MIN_INT_BITS && bits <= llvm::IntegerType::MAX_INT_BITS)
		{
			context_a.push (new (GC) mu::llvm_::integer_type::node (llvm::IntegerType::get (*one->context, bits)));
		}
		else
		{
			mu::stringstream message;
			message << U"Bits is not within bounds: ";
			message << llvm::IntegerType::MIN_INT_BITS;
			message << U" <= ";
			message << two->value;
			message << U" <= ";
			message << llvm::IntegerType::MAX_INT_BITS;
			context_a.errors (message.str ());
			valid = false;
		}
	}
	return valid;
}

mu::string mu::llvm_::integer_type::create::name ()
{
	return mu::string (U"mu::llvm_::integer_type::create");
}