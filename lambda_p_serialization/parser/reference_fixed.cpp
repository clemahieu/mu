#include "reference_fixed.h"

#include <lambda_p/core/fixed.h>

lambda_p_serialization::parser::reference_fixed::reference_fixed (boost::shared_ptr <lambda_p::core::entry> entry_a, std::vector <boost::shared_ptr <lambda_p::core::expression>> expressions_a)
	: entry (entry_a),
	expressions (expressions_a)
{
}

void lambda_p_serialization::parser::reference_fixed::operator () (boost::shared_ptr <lambda_p::core::target> target_a)
{
	boost::shared_ptr <lambda_p::core::fixed> fixed (new lambda_p::core::fixed);
	fixed->arguments = expressions;
	fixed->target = target_a;
}