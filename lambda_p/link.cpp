#include "link.h"

#include <lambda_p/visitor.h>

lambda_p::link::link (boost::shared_ptr <lambda_p::cluster> cluster_a, size_t index_a)
	: cluster (cluster_a),
	index (index_a)
{
}

void lambda_p::link::operator () (lambda_p::visitor * visitor_a)
{
	(*visitor_a) (this);
}

std::wstring lambda_p::link::name ()
{
	return std::wstring (L"lambda_p::link");
}
