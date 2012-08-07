#include <mu/llvm_/module/assemble.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::module::assemble::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::context::node, mu::script::astring::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::astring::node *> (context_a.parameters (1)));	
		llvm::SMDiagnostic diagnostic;
		llvm::Module * module (llvm::ParseAssemblyString (two->string.c_str (), nullptr, diagnostic, *one->context));
		if (module != nullptr)
		{
			context_a.push (new (GC) mu::llvm_::module::node (module));
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
			mu::string converted (amessage.begin (), amessage.end ());
			context_a.errors (converted);
			result = false;
		}
	}
	return result;
}

mu::string mu::llvm_::module::assemble::name ()
{
	return mu::string (U"mu::llvm_::module::assemble");
}