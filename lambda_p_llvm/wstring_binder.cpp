#include "wstring_binder.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/type.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

void lambda_p_llvm::wstring_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		auto module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		check_binder (module, 0, L"module", problems);
		auto data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [1]]));
		check_binder (data, 1, L"data", problems);
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (nodes [statement->association->references [2]]));
		check_binder (type, 2, L"type", problems);
		if (problems.errors.empty ())
		{ 
			if (type->type_m->isIntegerTy ())
			{
				boost::shared_ptr <lambda_p_llvm::value> value;
				core (module, data, type, value);
				nodes [statement->association->declarations [0]] = value;
			}
			else
			{
				add_error (L"Type must be an IntegerType", problems);
			}
		}
	}
}

void lambda_p_llvm::wstring_binder::core (boost::shared_ptr <lambda_p_llvm::module> module, boost::shared_ptr <lambda_p::binder::data> data, boost::shared_ptr <lambda_p_llvm::type> type, boost::shared_ptr <lambda_p_llvm::value> & value)
{
	auto string_type (llvm::ArrayType::get (type->type_m, data->string ().size () + 1));
	std::vector <llvm::Constant *> string_initializer;
	for (auto i = data->string ().begin (); i != data->string ().end (); ++i)
	{
		string_initializer.push_back (llvm::ConstantInt::get (type->type_m, *i));
	}
	string_initializer.push_back (llvm::ConstantInt::get (type->type_m, 0));
	auto string_array (llvm::ConstantArray::get (string_type, string_initializer));
	auto string_global (new llvm::GlobalVariable (string_type, true, llvm::GlobalValue::ExternalLinkage, string_array));
	module->module_m->getGlobalList ().push_back (string_global);
	value = boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (llvm::ConstantExpr::getPointerCast (string_global, llvm::PointerType::get (type->type_m, 0))));
}

std::wstring lambda_p_llvm::wstring_binder::binder_name ()
{
	return std::wstring (L"wstring_binder");
}