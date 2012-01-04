#include "identity.h"

#include <lambda_p/identity.h>
#include <lambda_p/container.h>

void lambda_p_test::identity::run ()
{
	run_1 ();
}

void lambda_p_test::identity::run_1 ()
{
	boost::shared_ptr <lambda_p::identity> identity (new lambda_p::identity);
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (identity);
	(*identity) (arguments, container);
	assert (container->results.empty ());
}
