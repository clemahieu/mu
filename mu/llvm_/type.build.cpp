#include <mu/llvm_/type.build.h>

#include <mu/llvm_/integer_type.node.h>
#include <mu/llvm_/struct_type.node.h>
#include <mu/llvm_/pointer_type.node.h>
#include <mu/llvm_/array_type.node.h>
#include <mu/llvm_/void_type.node.h>
#include <mu/llvm_/function_type.node.h>

#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

mu::llvm_::type::build::build (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::Type const * type_a)
{
	if (type_a->isVoidTy ())
	{
		type = boost::make_shared <mu::llvm_::void_type::node> (context_a);
	}
	else
	{
		auto integer_type (llvm::dyn_cast <llvm::IntegerType> (type_a));
		if (integer_type != nullptr)
		{
			type = boost::make_shared <mu::llvm_::integer_type::node> (integer_type);
		}
		else
		{
			auto structure_type (llvm::dyn_cast <llvm::StructType> (type_a));
			if (structure_type != nullptr)
			{
				type = boost::make_shared <mu::llvm_::struct_type::node> (context_a, structure_type);
			}
			else
			{
				auto pointer_type (llvm::dyn_cast <llvm::PointerType> (type_a));
				if (pointer_type != nullptr)
				{
					type = boost::make_shared <mu::llvm_::pointer_type::node> (context_a, pointer_type);
				}
				else
				{
					auto array_type (llvm::dyn_cast <llvm::ArrayType> (type_a));
					if (array_type != nullptr)
					{
						type = boost::make_shared <mu::llvm_::array_type::node> (context_a, array_type);
					}
					else
					{
						auto function_type (llvm::dyn_cast <llvm::FunctionType> (type_a));
						if (function_type != nullptr)
						{
							type = boost::make_shared <mu::llvm_::function_type::node> (context_a, function_type);
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
