#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/struct_type/node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::struct_type::create::perform (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		if (one.get () != nullptr)
		{
			size_t position (1);
			std::vector <boost::shared_ptr <mu::llvm_::type::node>> types;
			for (auto i (context_a.parameters.begin ()), j (context_a.parameters.end ()); i != j && !(*context_a.errors) (); ++i, ++position)
			{
				auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
				if (type.get () != nullptr)
				{
					types.push_back (type);
				}
				else
				{
					invalid_type (context_a.errors, *i, position);
				}
			}
			if (!(*context_a.errors) ())
			{
				context_a.results.push_back (boost::make_shared <mu::llvm_::struct_type::node> (one, types));
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" requires at least one argument";
		(*context_a.errors) (message.str ());
	}
}