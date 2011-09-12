#include "echo.h"

#include <iostream>

lambda_p_repl::echo::echo(::std::wstring string_a)
	: string (string_a)
{
}

lambda_p_repl::echo::~echo(void)
{
}

void lambda_p_repl::echo::operator () ()
{
	::std::wcout << string;
}
