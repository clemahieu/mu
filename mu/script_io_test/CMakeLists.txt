cmake_minimum_required (VERSION 2.8)
project (script_io_test)

add_library (mu_script_io_test STATIC
	builder.cpp
	call.cpp
	lambda.cpp
	routine.cpp
	synthesizer.cpp
	tests.cpp)