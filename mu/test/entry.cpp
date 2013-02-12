#include <gtest/gtest.h>
#include <gc.h>

int main (int argc, char ** argv)
{
    GC_INIT ();
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}