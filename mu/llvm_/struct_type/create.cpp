#include <mu/llvm_/struct_type/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/struct_type/node.h>
#include <mu/script/check.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <gc_cpp.h>
#include <gc_allocator.h>

bool mu::llvm_::struct_type::create::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (dynamic_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		if (one != nullptr)
		{
			size_t position (1);
			std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> types;
			for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j && valid; ++i, ++position)
			{
				auto type (dynamic_cast <mu::llvm_::type::node *> (*i));
				if (type != nullptr)
				{
					types.push_back (type);
				}
				else
				{
					mu::script::invalid_type (context_a, *i, typeid (mu::llvm_::type::node), position);
					valid = false;
				}
			}
			if (valid)
			{
				context_a.push (new (GC) mu::llvm_::struct_type::node (one, types));
			}
		}
		else
		{
			mu::script::invalid_type (context_a, context_a.parameters (0), typeid (mu::llvm_::context::node), 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" requires at least one argument";
		context_a.errors (message.str ());
		valid = false;
	}
	return valid;
}