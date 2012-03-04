#include <mu/llvm_/module.assemble.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/context.node.h>
#include <mu/script/astring.node.h>
#include <mu/llvm_/module.node.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

#include <sstream>

void mu::llvm_::module::assemble::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{			
			llvm::SMDiagnostic diagnostic;
			llvm::Module * module (llvm::ParseAssemblyString (two->string.c_str (), nullptr, diagnostic, *one->context));
			if (module != nullptr)
			{
				results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::module::node (module)));
			}
			else
			{
				std::stringstream message;
				message << L"Unable to assemble data:\n";
				std::string msg (diagnostic.getMessage ());
				message << msg;
				message << ": (";
				message << diagnostic.getLineNo ();
				message << ",";
				message << diagnostic.getColumnNo ();
				message << "): ";
				message << diagnostic.getLineContents ();
				std::string amessage (message.str ());
				std::wstring converted (amessage.begin (), amessage.end ());
				(*errors_a) (converted);
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

size_t mu::llvm_::module::assemble::count ()
{
	return 2;
}

std::wstring mu::llvm_::module::assemble::name ()
{
	return std::wstring (L"mu::llvm_::module::assemble");
}
