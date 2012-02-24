#include <mu/repl/repl.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

int main ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeAllAsmPrinters();
	mu::repl::repl repl;
	repl.run ();
	return 0;
}