#include "cluster.h"

lambda_p_script::cluster::cluster (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a)
	: routines (routines_a)
{
}

lambda_p_script::cluster::cluster (std::map <std::wstring, size_t> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a)
	: names (names_a),
	routines (routines_a)
{
}