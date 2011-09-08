#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine(size_t parameters_a)
	: parameters (parameters_a)
{
}

lambda_p::core::routine::~routine(void)
{
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::parameter_ref *>::const_iterator i = parameter_refs.begin (); i != parameter_refs.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = results.begin (); i != results.end (); ++i)
	{
		delete *i;
	}
	for (::std::vector < ::lambda_p::core::reference *>::const_iterator i = result_refs.begin (); i != result_refs.end (); ++i)
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

::lambda_p::core::data * lambda_p::core::routine::add_data (::boost::shared_array <uint8_t> item_a, size_t size_a, size_t self_statement_a, size_t self_argument_a)
{
	data.push_back (new ::lambda_p::core::data (item_a, size_a, this, self_statement_a, self_argument_a));
	return data [data.size () - 1];
}

::lambda_p::core::parameter_ref * lambda_p::core::routine::add_parameter_ref (size_t target_parameter_a, size_t self_statement_a, size_t self_argument_a)
{
	parameter_refs.push_back (new ::lambda_p::core::parameter_ref (this, target_parameter_a, self_statement_a, self_argument_a));
	return parameter_refs [parameter_refs.size () - 1];
}

::lambda_p::core::declaration * lambda_p::core::routine::add_result (size_t self_statement_a, size_t self_argument_a)
{
	results.push_back (new ::lambda_p::core::declaration (this, self_statement_a, self_argument_a));
	return results [results.size () - 1];
}

::lambda_p::core::reference * lambda_p::core::routine::add_result_ref (size_t target_statement_a, size_t target_argument_a, size_t self_statement_a, size_t self_argument_a)
{
	result_refs.push_back (new ::lambda_p::core::reference (this, target_statement_a, target_argument_a, self_statement_a, self_argument_a));
	return result_refs [result_refs.size () - 1];
}

void lambda_p::core::routine::validate (::std::iostream & problems) const
{	
	for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = statements.begin (); i != statements.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::parameter_ref *>::const_iterator i = parameter_refs.begin (); i != parameter_refs.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::declaration *>::const_iterator i = results.begin (); i != results.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::reference *>::const_iterator i = result_refs.begin (); i != result_refs.end (); ++i)
	{
		(*i)->validate (problems);
	}
	for (::std::vector < ::lambda_p::core::data *>::const_iterator i = data.begin (); i != data.end (); ++i)
	{
		(*i)->validate (problems);
	}
}