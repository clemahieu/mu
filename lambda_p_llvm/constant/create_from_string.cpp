#include "create_from_string.h"

#include <lambda_p_script/string/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/constant/node.h>
#include <lambda_p_llvm/array_type/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::constant::create_from_string::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			size_t bits (sizeof (wchar_t) * 8);
			auto type (llvm::Type::getIntNTy (*one->context, bits));
			std::vector <llvm::Constant *> elements;
			for (auto i (two->string.begin ()), j (two->string.end ()); i != j; ++i)
			{
				elements.push_back (llvm::ConstantInt::get (type, llvm::APInt (bits, *i)));
			}
			auto array_type (boost::make_shared <lambda_p_llvm::array_type::node> (boost::make_shared <lambda_p_llvm::integer_type::node> (type), elements.size ()));
			auto constant (llvm::ConstantArray::get (array_type->array_type (), elements));
			results.push_back (boost::make_shared <lambda_p_llvm::constant::node> (constant, array_type));
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::constant::create_from_string::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::constant::create_from_string::name ()
{
	return std::wstring (L"lambda_p_llvm::constant::create_from_string");
}