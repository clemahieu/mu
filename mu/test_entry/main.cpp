#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <gtest/gtest.h>

#include <iostream>

int main (int argc, char** argv)
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter();
    testing::InitGoogleTest(&argc, argv);
    auto result (RUN_ALL_TESTS());
	return result;
}