#include <lambda_p/core/statement.h>

#include <lambda_p/core/routine.h>

lambda_p::core::statement::statement ()
{
}

lambda_p::core::statement::~statement (void)
{
}

void lambda_p::core::statement::add_argument (::lambda_p::core::node * node_a)
{
    arguments.push_back (node_a);
}