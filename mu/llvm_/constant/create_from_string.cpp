#include <mu/llvm_/constant/create_from_string.h>

#include <mu/script/string_node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/constant/node.h>
#include <mu/llvm_/array_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <gc_cpp.h>

bool mu::llvm_::constant::create_from_string::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::context::node, mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::string::node *> (context_a.parameters (1)));
		size_t bits (sizeof (wchar_t) * 8);
		auto type (llvm::Type::getIntNTy (*one->context, bits));
		std::vector <llvm::Constant *> elements;
		for (auto i (two->string.begin ()), j (two->string.end ()); i != j; ++i)
		{
			elements.push_back (llvm::ConstantInt::get (type, llvm::APInt (bits, *i)));
		}
		auto array_type (new (GC) mu::llvm_::array_type::node (new (GC) mu::llvm_::integer_type::node (type), elements.size ()));
		auto constant (llvm::ConstantArray::get (array_type->array_type (), elements));
		context_a.push (new (GC) mu::llvm_::constant::node (constant, array_type));
	}
	return result;
}

mu::string mu::llvm_::constant::create_from_string::name ()
{
	return mu::string (U"mu::llvm_::constant::create_from_string");
}