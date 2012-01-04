#include "connection.h"

#include <lambda_p/core/gather.h>

lambda_p::core::connection::connection (boost::shared_ptr <lambda_p::core::gather> gather_a, size_t number_a)
	: gather (gather_a),
	number (number_a)
{
}

void lambda_p::core::connection::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	(*gather) (arguments, number);
}