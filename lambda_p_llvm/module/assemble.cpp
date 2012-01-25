#include "assemble.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_script/astring/node.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

#include <sstream>

void lambda_p_llvm::module::assemble::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{			
			llvm::SMDiagnostic diagnostic;
			llvm::Module * module (llvm::ParseAssemblyString (two->string.c_str (), nullptr, diagnostic, one->context));
			if (module != nullptr)
			{
				results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::node (module)));
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

size_t lambda_p_llvm::module::assemble::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::module::assemble::name ()
{
	return std::wstring (L"lambda_p_llvm::module::assemble");
}