#include "hello_world.h"

#include <iostream>

lambda_p_repl::hello_world::hello_world(void)
{
}

lambda_p_repl::hello_world::~hello_world(void)
{
}

void lambda_p_repl::hello_world::operator () ()
{
	::std::wcout << L"Hello world!\n";
}