#include "right_square.h"

lambda_p_serialization::tokens::token_ids lambda_p_serialization::tokens::right_square::token_id ()
{
	return lambda_p_serialization::tokens::token_id_right_square;
}

std::wstring lambda_p_serialization::tokens::right_square::token_name ()
{
	return std::wstring (L"right square");
}