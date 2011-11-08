#include <lambda_p_test/simple_test_1.h>
#include <lambda_p_test/lexer_test_1.h>
#include <lambda_p_test/parser_test_1.h>
#include <lambda_p_test/simple_compile_test_1.h>
#include <lambda_p_test/bind_procedure_test_1.h>
#include <lambda_p_test/package_test_1.h>
#include <lambda_p_test/abort_binder_test_1.h>
#include <lambda_p_test/jit_test_1.h>
#include <lambda_p_test/data_to_string_binder_test_1.h>
#include <lambda_p_test/echo_binder_test.h>
#include <lambda_p_test/constant_int_binder_test_1.h>
#include <lambda_p_test/routine_input_test_1.h>
#include <lambda_p_test/node_list_test_1.h>
#include <lambda_p_test/routine_binder_test.h>
#include <lambda_p_test/unbindable_statement_test.h>
#include <lambda_p_test/generator_test.h>
#include <lambda_p_test/routine_builder_test.h>
#include <lambda_p_test/list_test.h>
#include <lambda_p_test/wistream_input_test.h>
#include <lambda_p_test/filesystem_test.h>
#include <lambda_p_test/istream_input_test.h>
#include <lambda_p_test/node_list_test.h>
#include <lambda_p_test/directory_iterator_test.h>
#include <lambda_p_test/file_stream_test.h>
#include <lambda_p_test/apply_binder_test.h>
#include <lambda_p_test/api_test.h>
#include <lambda_p_test/execution_engine_test.h>
#include <lambda_p_test/overlay_binder_test.h>
#include <lambda_p_test/link_test.h>
#include <lambda_p_test/adata_test.h>
#include <lambda_p_test/cvalue_test.h>
#include <lambda_p_test/times_test.h>
#include <lambda_p_test/number_binder_test.h>
#include <lambda_p_test/loop_test.h>
#include <lambda_p_test/type_inference_test.h>

#include <llvm/Target/TargetSelect.h>

#include <iostream>

using namespace lambda_p_test;

int main ()
{
    llvm::InitializeNativeTarget ();
	{
		simple_test_1 test;
		test.run ();
	}
	{
		lexer_test_1 test;
		test.run ();
	}
	{
		parser_test_1 test;
		test.run ();
	}
	{
		adata_test test;
		test.run ();
	}
	{
		simple_compile_test_1 test;
		test.run ();
	}
	{
		execution_engine_test test;
		test.run ();
	}
	{
		cvalue_test test;
		test.run ();
	}
	{
		overlay_binder_test test;
		test.run ();
	}
	{
		link_test test;
		test.run ();
	}
	{
		node_list_test test;
		test.run ();
	}
	{
		bind_procedure_test_1 test;
		test.run ();
	}
	{
		package_test_1 test;
		test.run ();
	}
    {
        abort_binder_test_1 test;
        test.run ();
    }
    {
        jit_test_1 test;
        test.run ();
    }
    {
        data_to_string_binder_test_1 test;
        test.run ();
    }
    {
        echo_binder_test test;
        test.run ();
    }
	{
		constant_int_binder_test_1 test;
		test.run ();
	}
	{
		wistream_input_test test;
		test.run ();
	}
	{
		routine_input_test_1 test;
		test.run ();
	}
	{
		node_list_test_1 test;
		test.run ();
	}
	{
		routine_binder_test test;
		test.run ();
	}
	{
		unbindable_statement_test test;
		test.run ();
	}
	{
		routine_builder_test test;
		test.run ();
	}
	{
		list_test test;
		test.run ();
	}
	{
		generator_test test;
		test.run ();
	}
	{
		filesystem_test test;
		test.run ();
	}
	{
		istream_input_test test;
		test.run ();
	}
	{
		directory_iterator_test test;
		test.run ();
	}
	{
		file_stream_test test;
		test.run ();
	}
	{
		apply_binder_test test;
		test.run ();
	}
	{
		api_test test;
		test.run ();
	}
	{
		times_test test;
		test.run ();
	}
	{
		number_binder_test test;
		test.run ();
	}
	{
		loop_test test;
		test.run ();
	}
	{
		type_inference_test test;
		test.run ();
	}
	for (size_t i (0); i < 1000; ++i)
	{
		std::wcout << L'-';
	}
	return 0;
}