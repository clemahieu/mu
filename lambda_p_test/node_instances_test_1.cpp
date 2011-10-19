#include "node_instances_test_1.h"

#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/binder/data.h>

lambda_p_test::node_instances_test_1::node_instances_test_1(void)
{
}

lambda_p_test::node_instances_test_1::~node_instances_test_1(void)
{
}

void lambda_p_test::node_instances_test_1::run ()
{
	lambda_p::binder::routine_instances instances;
	boost::shared_ptr < lambda_p::binder::data> data (new lambda_p::binder::data (std::wstring (L"test")));
	instances [7] = data;
	assert (instances.instances.size () == 8);
	assert (instances [7].get () != NULL);
	assert (instances [6].get () == NULL);
}
