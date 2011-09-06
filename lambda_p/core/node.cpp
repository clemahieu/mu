#include <lambda_p/core/node.h>

#include <lambda_p/core/routine.h>

::lambda_p::core::node::node ()
{
}

::lambda_p::core::node::~node (void)
{
}

void ::lambda_p::core::node::validate_argument (char const * self_name, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a, ::std::iostream & problems) const
{
	size_t statements_count (routine_a->statements.size ());
	bool valid = statements_count > self_statement_a;
	if (valid)
	{
		size_t argument_count (routine_a->statements [self_statement_a]->arguments.size ());
		valid = argument_count > self_argument_a;
		if (valid)
		{
			valid = routine_a->statements [self_statement_a]->arguments [self_argument_a] == this;
			if (valid)
			{
			}
			else
			{					
				problems << self_name;
				problems << this;
				problems << " referencing routine: ";
				problems << routine_a;
				problems << " referencing self statement: ";
				problems << self_statement_a;
				problems << " referencing self argument: ";
				problems << self_argument_a;
				problems << " does not reference this object\n";
			}
		}
		else
		{
			problems << self_name;
			problems << this;
			problems << " referencing routine: ";
			problems << routine_a;
			problems << " referencing self statement: ";
			problems << self_statement_a;
			problems << " references a self argument greater than the max: ";
			problems << self_argument_a;
			problems << "\n";
		}
	}
	else
	{			
		problems << self_name;
		problems << this;
		problems << " referencing routine: ";
		problems << routine_a;
		problems << " references a self statement: ";
		problems << self_statement_a;
		problems << " that is greater than the max: ";
		problems << statements_count;
		problems << "\n";
	}
}