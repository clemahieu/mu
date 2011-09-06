#include <lambda_p/serialization/lexer/multiline_comment.h>

lambda_p::serialization::lexer::multiline_comment::multiline_comment(void)
	: have_semicolon (false)
{
}

lambda_p::serialization::lexer::multiline_comment::~multiline_comment(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::multiline_comment::state_type ()
{
	return ::lambda_p::serialization::lexer::state_multiline_comment;
}
