#include <lambda_p/serialization/simple.h>

::lambda_p::serialization::simple::simple(void)
{
}

::lambda_p::serialization::simple::~simple(void)
{
}

void ::lambda_p::serialization::simple::function (::lambda_p::core::function *function_a)
{
	*target << function_a->name;
	*target << "\n";
	for (::std::vector <::lambda_p::core::node>::iterator i = function_a->input.begin (); i != function_a->input.end (); ++i)
	{
		*target << " ";
		node (&*i);
		*target << "\n";
	}
	*target << ".\n";
	for (::std::vector <::lambda_p::core::node>::iterator i = function_a->output.begin (); i != function_a->output.end (); ++i)
	{
		*target < " ";
		node (&*i);
		*target << "\n";
	}
	*target << ".\n";
}

void ::lambda_p::serialization::simple::body (::lambda_p::core::body *body_a)
{
	for (::std::vector <::lambda_p::core::statement>::iterator i = body_a->statements.begin (); i != body_a->statements.end (); ++i)
	{
		*target << " ";
		statement (&*i);
		*target << "\n";
	}
}

void ::lambda_p::serialization::simple::statement (::lambda_p::core::statement *statement_a)
{
	*target << statement_a->name;
	*target << "\n";
	for (::std::vector <::lambda_p::core::node*>::iterator i = statement_a->output.begin (); i != statement_a->output.end (); ++i)
	{
		*target << " ";
		node (*i);
		*target << "\n";
	}
	*target << ".\n";
	for (::std::vector <::lambda_p::core::node*>::iterator i = statement_a->input.begin (); i != statement_a->input.end (); ++i)
	{
		*target << " ";
		node (*i);
		*target << "\n";
	}
	*target << ".\n";
}

void ::lambda_p::serialization::simple::node (::lambda_p::core::node *node_a)
{
	::std::string escaped (node_a->name);
	escaped.replace (escaped.begin (), escaped.end (), ".", ".\\");
	*target << escaped;
}