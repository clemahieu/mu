#include "left_square.h"

lambda_p::tokens::token_ids lambda_p::tokens::left_square::token_id ()
{
	return lambda_p::tokens::token_id_left_square;
}

std::wstring lambda_p::tokens::left_square::token_name ()
{
	return std::wstring (L"left square");
}