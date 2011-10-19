#include <lambda_p/lexer/multiline_comment.h>

lambda_p::lexer::multiline_comment::multiline_comment(void)
	: have_pound (false)
{
}

lambda_p::lexer::multiline_comment::~multiline_comment(void)
{
}

lambda_p::lexer::state_id lambda_p::lexer::multiline_comment::state_type ()
{
	return lambda_p::lexer::state_multiline_comment;
}
