#include "connection.h"

#include <lambda_p/gather.h>

lambda_p::connection::connection (boost::shared_ptr <lambda_p::gather> gather_a, size_t number_a)
	: gather (gather_a),
	number (number_a)
{
}

void lambda_p::connection::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	(*gather) (arguments, number);
}