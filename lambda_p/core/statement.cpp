#include <lambda_p/core/statement.h>

#include <lambda_p/core/routine.h>

lambda_p::core::statement::statement (::lambda_p::core::routine * routine_a, size_t index_a)
: routine (routine_a),
index (index_a)
{
}

lambda_p::core::statement::~statement (void)
{
}

void lambda_p::core::statement::add_argument (::lambda_p::core::node * node_a)
{
    arguments.push_back (node_a);
}

void lambda_p::core::statement::validate (::std::iostream & problems)
{
	size_t statement_size (routine->statements.size ());
	bool valid (statement_size > index);
	if (valid)
	{
		if (&routine->statements [index] != this)
		{
			problems << "statement: ";
			problems << this;
			problems << " referencing routine: ";
			problems << &routine;
			problems << " referencing statement: ";
			problems << index;
			problems << " does not reference this object\n";
		}
	}
	else
	{		
		problems << "statement: ";
		problems << this;
		problems << " referencing routine: ";
		problems << &routine;
		problems << " references a statement: ";
		problems << index;
		problems << " that is greater than the max: ";
		problems << statement_size - 1;
		problems << "\n";
	}
}