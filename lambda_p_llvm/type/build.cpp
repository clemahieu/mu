#include "build.h"

#include <lambda_p_llvm/integer_type/node.h>
#include <lambda_p_llvm/struct_type/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/array_type/node.h>
#include <lambda_p_llvm/void_type/node.h>
#include <lambda_p_llvm/function_type/node.h>

#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

lambda_p_llvm::type::build::build (boost::shared_ptr <lambda_p_llvm::context::node> context_a, llvm::Type * type_a)
{
	if (type_a->isVoidTy ())
	{
		type = boost::make_shared <lambda_p_llvm::void_type::node> (context_a);
	}
	else
	{
		auto integer_type (llvm::dyn_cast <llvm::IntegerType> (type_a));
		if (integer_type != nullptr)
		{
			type = boost::make_shared <lambda_p_llvm::integer_type::node> (integer_type);
		}
		else
		{
			auto structure_type (llvm::dyn_cast <llvm::StructType> (type_a));
			if (structure_type != nullptr)
			{
				type = boost::make_shared <lambda_p_llvm::struct_type::node> (context_a, structure_type);
			}
			else
			{
				auto pointer_type (llvm::dyn_cast <llvm::PointerType> (type_a));
				if (pointer_type != nullptr)
				{
					type = boost::make_shared <lambda_p_llvm::pointer_type::node> (context_a, pointer_type);
				}
				else
				{
					auto array_type (llvm::dyn_cast <llvm::ArrayType> (type_a));
					if (array_type != nullptr)
					{
						type = boost::make_shared <lambda_p_llvm::array_type::node> (context_a, array_type);
					}
					else
					{
						auto function_type (llvm::dyn_cast <llvm::FunctionType> (type_a));
						if (function_type != nullptr)
						{
							type = boost::make_shared <lambda_p_llvm::function_type::node> (context_a, function_type);
						}
						else
						{
							assert (false);
						}
					}
				}
			}
		}
	}
}