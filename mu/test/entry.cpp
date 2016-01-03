#include <gtest/gtest.h>

#include <llvm/Support/TargetSelect.h>

extern "C" void LLVMLinkInMCJIT();

int main (int argc, char ** argv)
{
    llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter ();
	LLVMLinkInMCJIT ();
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}