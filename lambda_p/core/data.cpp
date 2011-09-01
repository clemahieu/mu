#include "data.h"

#include <lambda_p/core/routine.h>

lambda_p::core::data::data(::boost::shared_array <uint8_t> item_a, size_t size_a, ::lambda_p::core::routine * routine_a, size_t statement_a, size_t index_a)
	: routine (routine_a),
	item (item_a),
	size (size_a),
	statement (statement_a),
	index (index_a)
{
}

lambda_p::core::data::~data(void)
{
}

void lambda_p::core::data::validate (::std::iostream & problems)
{
	size_t statement_size (routine->statements.size ());
	if (statement_size > statement)
	{
		size_t arguments_size (routine->statements.size ());
		if (arguments_size > index)
		{
			::lambda_p::core::data * data_l = dynamic_cast < ::lambda_p::core::data *> (routine->statements [statement].arguments [index]);
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
					problems << statement;
					problems << " referencing argument: ";
					problems << index;
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
				problems << statement;
				problems << " referencing argument: ";
				problems << index;
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
			problems << statement;
			problems << " refrences an argument: ";
			problems << index;
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
		problems << statement;
		problems << " that is greater than the max: ";
		problems << statement_size - 1;
		problems << "\n";
	}
}