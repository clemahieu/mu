#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine ()
{
}

lambda_p::core::routine::~routine(void)
{
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = declarations.begin (); i != declarations.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::reference *>::const_iterator i = references.begin (); i != references.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::data *>::const_iterator i = data.begin (); i != data.end (); ++i)
	{
		delete *i;
	}
}

::lambda_p::core::statement * lambda_p::core::routine::add_statement ()
{
	statements.push_back (new ::lambda_p::core::statement (this, statements.size ()));
	return statements [statements.size () - 1];
}

::lambda_p::core::data * lambda_p::core::routine::add_data (::std::wstring string, size_t self_statement_a, size_t self_argument_a)
{
	data.push_back (new ::lambda_p::core::data (string, this, self_statement_a, self_argument_a));
	return data [data.size () - 1];
}

::lambda_p::core::declaration * lambda_p::core::routine::add_declaration (size_t self_statement_a, size_t self_argument_a)
{
	declarations.push_back (new ::lambda_p::core::declaration (this, self_statement_a, self_argument_a));
	return declarations [declarations.size () - 1];
}

::lambda_p::core::reference * lambda_p::core::routine::add_reference (size_t target_statement_a, size_t target_argument_a, size_t self_statement_a, size_t self_argument_a)
{
	references.push_back (new ::lambda_p::core::reference (this, target_statement_a, target_argument_a, self_statement_a, self_argument_a));
	return references [references.size () - 1];
}

void lambda_p::core::routine::validate (::std::wostream & problems) const
{	
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = declarations.begin (); i != declarations.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::reference *>::const_iterator i = references.begin (); i != references.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::data *>::const_iterator i = data.begin (); i != data.end (); ++i)
	{
		(*i)->validate (problems);
	}
}