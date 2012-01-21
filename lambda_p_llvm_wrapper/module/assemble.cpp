#include "assemble.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm_wrapper/context/node.h>
#include <lambda_p_script/astring/node.h>
#include <lambda_p_llvm_wrapper/module/node.h>

#include <llvm/Assembly/Parser.h>
#include <llvm/Support/SourceMgr.h>

#include <sstream>

void lambda_p_llvm_wrapper::module::assemble::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm_wrapper::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{			
			llvm::SMDiagnostic diagnostic;
			llvm::Module * module (llvm::ParseAssemblyString (two->string.c_str (), nullptr, diagnostic, one->context));
			if (module != nullptr)
			{
				results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::node (module)));
			}
			else
			{
				std::wstringstream message;
				std::string amessage (diagnostic.getMessage ());
				std::wstring converted;
				converted.resize (amessage.size ());
				std::copy (amessage.begin (), amessage.end (), converted.begin ());
				message << L"Unable to assemble data:\n";
				message << converted;
				(*errors_a) (message.str ());
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

size_t lambda_p_llvm_wrapper::module::assemble::count ()
{
	return 2;
}

std::wstring lambda_p_llvm_wrapper::module::assemble::name ()
{
	return std::wstring (L"lambda_p_llvm_wrapper::module::assemble");
}