#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/astring/node.h>
#include <mu/script/check.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/Host.h>
#include <llvm/PassManager.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>

#include <sstream>

void mu::llvm_::compile::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node, mu::script::astring::node> () (context_a))
	{
		auto module (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		auto name (boost::static_pointer_cast <mu::script::astring::node> (context_a.parameters [1]));
		std::string error;
		std::string triple (llvm::sys::getHostTriple ());
		llvm::Target const * target (llvm::TargetRegistry::lookupTarget (triple, error));
		if (error.empty ())
		{
			llvm::TargetMachine * machine (target->createTargetMachine (triple, std::string (), std::string ()));
			llvm::TargetData const * data (machine->getTargetData ());
			llvm::PassManager manager;
			manager.add (new llvm::TargetData (*data));
			std::string error_info;
			auto obj_name (name->string);
			obj_name.append (".obj");
			bool link (false);
			{
				llvm::raw_fd_ostream raw (obj_name.c_str (), error_info, llvm::raw_fd_ostream::F_Binary);
				llvm::formatted_raw_ostream stream (raw);
				if (error_info.empty ())
				{
					bool failed_add (machine->addPassesToEmitFile (manager, stream, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile, llvm::CodeGenOpt::None));
					if (!failed_add)
					{
						manager.run (*module->module);
						link = true;
					}
					else
					{
						context_a (L"Target does not support generation of files of this file type");
					}
				}
				else
				{
					std::wstring message (error_info.begin (), error_info.end ());
					context_a (message);
				}
			}
			if (link)
			{
				std::stringstream command;
				command << "\"c:\\Program Files (x86)\\Microsoft Visual Studio 10.0\\VC\\vcvarsall.bat\" amd64 && link kernel32.lib msvcrt.lib /NOLOGO /SUBSYSTEM:CONSOLE ";
				command << obj_name;
				command << " /OUT:";
				command << name->string;
				command << ".exe";
				std::string cmd (command.str ());
				system (cmd.c_str ());
			}
		}
		else
		{
			std::wstring message (error.begin (), error.end ());
			context_a (message);
		}
	}
}

std::wstring mu::llvm_::compile::operation::name ()
{
	return std::wstring (L"mu::llvm_::compile::operation");
}
