#include "singleline_comment.h"

lambda_p::serialization::lexer::singleline_comment::singleline_comment(void)
{
}

lambda_p::serialization::lexer::singleline_comment::~singleline_comment(void)
{
}

::lambda_p::serialization::lexer::state_id lambda_p::serialization::lexer::singleline_comment::state_type ()
{
	return ::lambda_p::serialization::lexer::state_id::state_singleline_comment;
}
