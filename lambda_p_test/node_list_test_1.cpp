#include "node_list_test_1.h"

#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/nodes/data.h>

lambda_p_test::node_list_test_1::node_list_test_1(void)
{
}

lambda_p_test::node_list_test_1::~node_list_test_1(void)
{
}

void lambda_p_test::node_list_test_1::run ()
{
	lambda_p::binder::list nodes;
	boost::shared_ptr <lambda_p_kernel::nodes::data> data (new lambda_p_kernel::nodes::data (std::wstring (L"test")));
	nodes [7] = data;
	assert (nodes.nodes.size () == 8);
	assert (nodes [7].get () != nullptr);
	assert (nodes [6].get () == nullptr);
}
