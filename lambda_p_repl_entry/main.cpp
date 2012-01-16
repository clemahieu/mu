#include <lambda_p_repl/repl.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

int main ()
{
	llvm::InitializeNativeTarget ();
	lambda_p_repl::repl repl;
	repl.run ();
	return 0;
}