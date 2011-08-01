#include <lambda-p_test/simple_test_1.h>
#include <lambda-p_test/simple_test_2.h>

int main ()
{
	{
		::lambda_p_test::simple_test_1 test;
		test.run ();
	}
	{
		::lambda_p_test::simple_test_2 test;
		test.run ();
	}
}