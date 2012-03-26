#include <mu/llvm_/constant/create_from_string.h>

#include <mu/script/string/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/constant/node.h>
#include <mu/llvm_/array_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/check.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <boost/make_shared.hpp>

bool mu::llvm_::constant::create_from_string::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::context::node, mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (1)));
		size_t bits (sizeof (wchar_t) * 8);
		auto type (llvm::Type::getIntNTy (*one->context, bits));
		std::vector <llvm::Constant *> elements;
		for (auto i (two->string.begin ()), j (two->string.end ()); i != j; ++i)
		{
			elements.push_back (llvm::ConstantInt::get (type, llvm::APInt (bits, *i)));
		}
		auto array_type (boost::make_shared <mu::llvm_::array_type::node> (boost::make_shared <mu::llvm_::integer_type::node> (type), elements.size ()));
		auto constant (llvm::ConstantArray::get (array_type->array_type (), elements));
		context_a.push (boost::make_shared <mu::llvm_::constant::node> (constant, array_type));
	}
	return result;
}

std::wstring mu::llvm_::constant::create_from_string::name ()
{
	return std::wstring (L"mu::llvm_::constant::create_from_string");
}