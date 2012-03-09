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
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

void mu::llvm_::constant_string::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::context::node, mu::llvm_::module::node, mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [1]));
		auto three (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [2]));
		std::vector <boost::shared_ptr <mu::core::node>> v1;
		v1.push_back (one);
		v1.push_back (boost::make_shared <mu::script::string::node> (three->string));
		std::vector <boost::shared_ptr <mu::core::node>> v2;
		mu::llvm_::constant::create_from_string create;
		v2.push_back (two);
        auto ctx (mu::script::context (context_a.errors, v1, v2));
		create (ctx);
		std::vector <boost::shared_ptr <mu::core::node>> v3;
		mu::llvm_::global_variable::create_set set;
        auto ctx2 (mu::script::context (context_a.errors, v2, v3));
		set (ctx2);
		if (! (*context_a.errors) ())
		{
			auto global (boost::static_pointer_cast <mu::llvm_::global_variable::node> (v3 [0]));
			auto var (global->global_variable ());
			auto pointer_type (boost::static_pointer_cast <mu::llvm_::pointer_type::node> (global->type));
			auto array_type (boost::static_pointer_cast <mu::llvm_::array_type::node> (pointer_type->element));
			auto result (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantExpr::getBitCast (var, llvm::PointerType::get (array_type->element->type (), 0)), boost::make_shared <mu::llvm_::pointer_type::node> (array_type->element)));
			context_a.results.push_back (result);
		}
	}
}