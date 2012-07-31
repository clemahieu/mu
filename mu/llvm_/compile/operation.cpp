#include <mu/llvm_/compile/operation.h>

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

bool mu::llvm_::compile::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::module::node, mu::script::astring::node> () (context_a));
	if (valid)
	{
		auto module (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto name (static_cast <mu::script::astring::node *> (context_a.parameters (1)));
		std::string error;
		std::string triple (llvm::sys::getDefaultTargetTriple ());
		llvm::Target const * target (llvm::TargetRegistry::lookupTarget (triple, error));
		if (error.empty ())
		{
			llvm::TargetMachine * machine (target->createTargetMachine (triple, llvm::StringRef (), llvm::StringRef (), llvm::TargetOptions ()));
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
						context_a.errors (U"Target does not support generation of files of this file type");
						valid = false;
					}
				}
				else
				{
					mu::string message (error_info.begin (), error_info.end ());
					context_a.errors (message);
					valid = false;
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
			mu::string message (error.begin (), error.end ());
			context_a.errors (message);
			valid = false;
		}
	}
	return valid;
}

mu::string mu::llvm_::compile::operation::name ()
{
	return mu::string (U"mu::llvm_::compile::operation");
}
