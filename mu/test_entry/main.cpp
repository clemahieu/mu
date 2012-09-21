#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>
#include <boost/thread.hpp>

#include <gtest/gtest.h>

#include <iostream>

#include <gc.h>

int main (int argc, char** argv)
{
    GC_INIT ();
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter();
    testing::InitGoogleTest(&argc, argv);
    auto result (RUN_ALL_TESTS());
    boost::this_thread::sleep (boost::posix_time::milliseconds (500));
	return result;
}