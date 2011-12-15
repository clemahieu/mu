#include "sequence.h"


lambda_p::core::sequence::sequence (boost::shared_ptr <lambda_p::core::gather> gather_a, size_t number_a)
	: gather (gather_a),
	number (number_a)
{
}

void lambda_p::core::sequence::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
}