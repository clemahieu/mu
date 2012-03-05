cmake_minimum_required (VERSION 2.8)
project (script_io)

add_library (mu_script_io STATIC
	builder.cpp
	cluster.cpp
	expression.cpp
	lambda.cpp
	lambda_single.cpp
	reference.cpp
	routine.cpp
	script.cpp
	synthesizer.cpp)