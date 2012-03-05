#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/string/node.h>
#include <mu/llvm_/global_variable/create_set.h>
#include <mu/llvm_/constant/create_from_string.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/array_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

void mu::llvm_::constant_string::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{		
				std::vector <boost::shared_ptr <mu::core::node>> v1;
				v1.push_back (one);
				v1.push_back (boost::make_shared <mu::script::string::node> (three->string));
				std::vector <boost::shared_ptr <mu::core::node>> v2;
				mu::llvm_::constant::create_from_string create;
				v2.push_back (two);
				create.perform (errors_a, v1, v2);
				std::vector <boost::shared_ptr <mu::core::node>> v3;
				mu::llvm_::global_variable::create_set set;
				set.perform (errors_a, v2, v3);
				if (! (*errors_a) ())
				{
					auto global (boost::static_pointer_cast <mu::llvm_::global_variable::node> (v3 [0]));
					auto var (global->global_variable ());
					auto pointer_type (boost::static_pointer_cast <mu::llvm_::pointer_type::node> (global->type));
					auto array_type (boost::static_pointer_cast <mu::llvm_::array_type::node> (pointer_type->element));
					auto result (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantExpr::getBitCast (var, llvm::PointerType::get (array_type->element->type (), 0)), boost::make_shared <mu::llvm_::pointer_type::node> (array_type->element)));
					results.push_back (result);
				}
			}
			else
			{
				invalid_type (errors_a, parameters [2], 2);
			}
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

size_t mu::llvm_::constant_string::create::count ()
{
	return 3;
}