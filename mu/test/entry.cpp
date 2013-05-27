#include <gtest/gtest.h>
#include <gc.h>

#include <llvm/Support/TargetSelect.h>

int main (int argc, char ** argv)
{
    GC_INIT ();
    llvm::InitializeNativeTarget ();
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}