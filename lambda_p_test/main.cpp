#include <lambda_p_test/simple_test_1.h>
#include <lambda_p_test/simple_lexer_test_1.h>
#include <lambda_p_test/simple_parser_test_1.h>
#include <lambda_p_test/simple_compile_test_1.h>

using namespace lambda_p_test;

int main ()
{
	{
		simple_test_1 test;
		test.run ();
	}
	{
		simple_lexer_test_1 test;
		test.run ();
	}
	{
		simple_parser_test_1 test;
		test.run ();
	}
	{
		simple_compile_test_1 test;
		test.run ();
	}
	return 0;
}