#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/script/check.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::function_type::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::context::node, mu::script::values::operation, mu::script::values::operation> () (context_a))
	{
		auto context (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		auto one (boost::static_pointer_cast <mu::script::values::operation> (context_a.parameters [1]));
		auto two (boost::static_pointer_cast <mu::script::values::operation> (context_a.parameters [2]));
		std::vector <boost::shared_ptr <mu::llvm_::type::node>> arguments;
		std::vector <boost::shared_ptr <mu::llvm_::type::node>> results;
		for (auto i (one->values.begin ()), j (one->values.end ()); i != j; ++i)
		{
			auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
			if (type.get () != nullptr)
			{
				arguments.push_back (type);
			}
			else
			{
				std::wstringstream message;
				message << L"Expecting type, have: ";
				message << (*i)->name ();
				context_a (message.str ());
			}
		}
		for (auto i (two->values.begin ()), j (two->values.end ()); i != j; ++i)
		{
			auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
			if (type.get () != nullptr)
			{
				results.push_back (type);
			}
			else
			{
				std::wstringstream message;
				message << L"Expecting type, have: ";
				message << (*i)->name ();
				context_a (message.str ());
			}
		}
		if (results.size () == 0)
		{				
			context_a.results.push_back (boost::make_shared <mu::llvm_::function_type::node> (context, arguments, boost::make_shared <mu::llvm_::void_type::node> (context)));
		}
		else if (results.size () == 1)
		{
			context_a.results.push_back (boost::make_shared <mu::llvm_::function_type::node> (context, arguments, results [0]));
		}
		else
		{
			context_a.results.push_back (boost::make_shared <mu::llvm_::function_type::node> (context, arguments, boost::make_shared <mu::llvm_::set_type::node> (context, results)));
		}
	}
}

std::wstring mu::llvm_::function_type::create::name ()
{
	return std::wstring (L"mu::llvm_::function_type::create");
}