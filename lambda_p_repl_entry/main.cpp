#include <lambda_p_repl/repl.h>

#include <llvm/Target/TargetSelect.h>

int main ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter ();
	lambda_p_repl::repl repl;
	repl.run ();
	return 0;
}