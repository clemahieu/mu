#include <mu/llvm_/struct_type.create.h>

#include <mu/llvm_/struct_type.node.h>
#include <mu/core/errors.error_target.h>
#include <mu/llvm_/context.node.h>
#include <mu/llvm_/apint.node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::struct_type::create::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (parameters [0]));
		if (one.get () != nullptr)
		{
			size_t position (1);
			std::vector <boost::shared_ptr <mu::llvm_::type::node>> types;
			for (auto i (parameters.begin ()), j (parameters.end ()); i != j && !(*errors_a) (); ++i, ++position)
			{
				auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
				if (type.get () != nullptr)
				{
					types.push_back (type);
				}
				else
				{
					invalid_type (errors_a, *i, position);
				}
			}
			if (!(*errors_a) ())
			{
				results.push_back (boost::make_shared <mu::llvm_::struct_type::node> (one, types));
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}
