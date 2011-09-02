#include "data.h"

#include <lambda_p/core/routine.h>

lambda_p::core::data::data(::boost::shared_array <uint8_t> item_a, size_t size_a, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a)
	: routine (routine_a),
	item_m (item_a),
	size (size_a),
	self_statement (self_statement_a),
	self_argument (self_argument_a)
{
}

lambda_p::core::data::~data(void)
{
}

void lambda_p::core::data::validate (::std::iostream & problems)
{
	size_t statement_size (routine->statements.size ());
	if (statement_size > self_statement)
	{
		size_t arguments_size (routine->statements.size ());
		if (arguments_size > self_argument)
		{
			::lambda_p::core::data * data_l = dynamic_cast < ::lambda_p::core::data *> (routine->statements [self_statement].arguments [self_argument]);
			if (data_l != NULL)
			{
				if (data_l == this)
				{
				}
				else
				{
					problems << "data: ";
					problems << this;
					problems << " referencing routine: ";
					problems << &routine;
					problems << " referencing statement: ";
					problems << self_statement;
					problems << " referencing argument: ";
					problems << self_argument;
					problems << " does not reference this object\n";
				}
			}
			else
			{				
				problems << "data: ";
				problems << this;
				problems << " referencing routine: ";
				problems << &routine;
				problems << " referencing statement: ";
				problems << self_statement;
				problems << " referencing argument: ";
				problems << self_argument;
				problems << " is not actually a data object\n";
			}
		}
		else
		{
			problems << "data: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << self_statement;
			problems << " refrences an argument: ";
			problems << self_argument;
			problems << " that is greater than the max: ";
			problems << arguments_size - 1;
			problems << "\n";
		}
	}
	else
	{		
		problems << "data: ";
		problems << this;
		problems << " referencing routine: ";
		problems << &routine;
		problems << " references a statement: ";
		problems << self_statement;
		problems << " that is greater than the max: ";
		problems << statement_size - 1;
		problems << "\n";
	}
}

::boost::shared_array <uint8_t> lambda_p::core::data::item () const
{
    return item_m;
}