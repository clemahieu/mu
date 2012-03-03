#include <mu/llvm_/linker.link_modules.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/module.node.h>

#include <llvm/Linker.h>

void mu::llvm_::linker::link_modules::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			std::string message;
			bool result (llvm::Linker::LinkModules (one->module, two->module, llvm::Linker::DestroySource, &message));
			if (result)
			{
				std::wstring message_l (message.begin (), message.end ());
				(*errors_a) (message_l);
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

size_t mu::llvm_::linker::link_modules::count ()
{
	return 2;
}

std::wstring mu::llvm_::linker::link_modules::name ()
{
	return std::wstring (L"mu::llvm_::linker::link_modules");
}
