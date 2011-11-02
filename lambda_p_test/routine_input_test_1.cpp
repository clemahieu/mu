#include "routine_input_test_1.h"

#include <lambda_p_repl/routine_input.h>
#include <lambda_p/lexer/wistream_input.h>

#include <sstream>


void lambda_p_test::routine_input_test_1::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::routine_input_test_1::run_1 ()
{
	std::wstringstream input;
	input << "environment = ; environment constant_int = number; #;";
	boost::shared_ptr <lambda_p::lexer::wistream_input> input2 (new lambda_p::lexer::wistream_input (input));
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
	lambda_p_repl::routine_input routine (injected_parameters);
	routine (input2);
}

void lambda_p_test::routine_input_test_1::run_2 ()
{
	std::wstringstream input;
	input << L"";
	boost::shared_ptr <lambda_p::lexer::wistream_input> input2 (new lambda_p::lexer::wistream_input (input));
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
	lambda_p_repl::routine_input routine (injected_parameters);
	routine (input2);
}