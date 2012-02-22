#include "create.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_llvm/global_variable/create_set.h>
#include <lambda_p_llvm/constant/create_from_string.h>
#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/array_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

void lambda_p_llvm::constant_string::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{		
				std::vector <boost::shared_ptr <lambda_p::node>> v1;
				v1.push_back (one);
				v1.push_back (boost::make_shared <lambda_p_script::string::node> (three->string));
				std::vector <boost::shared_ptr <lambda_p::node>> v2;
				lambda_p_llvm::constant::create_from_string create;
				v2.push_back (two);
				create.perform (errors_a, v1, v2);
				std::vector <boost::shared_ptr <lambda_p::node>> v3;
				lambda_p_llvm::global_variable::create_set set;
				set.perform (errors_a, v2, v3);
				if (! (*errors_a) ())
				{
					auto global (boost::static_pointer_cast <lambda_p_llvm::global_variable::node> (v3 [0]));
					auto var (global->global_variable ());
					auto pointer_type (boost::static_pointer_cast <lambda_p_llvm::pointer_type::node> (global->type));
					auto array_type (boost::static_pointer_cast <lambda_p_llvm::array_type::node> (pointer_type->element));
					auto result (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantExpr::getBitCast (var, llvm::PointerType::get (array_type->element->type (), 0)), boost::make_shared <lambda_p_llvm::pointer_type::node> (array_type->element)));
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

size_t lambda_p_llvm::constant_string::create::count ()
{
	return 3;
}