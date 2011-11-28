#include "adata_test.h"

#include <lambda_p_kernel/builder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/adata_binder.h>
#include <lambda_p_kernel/nodes/adata.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/routine.h>

void lambda_p_test::adata_test::run ()
{
	run_1 ();
}

void lambda_p_test::adata_test::run_1 ()
{
	lambda_p_kernel::builder builder;
	builder (L"test ;adata; adata ` test; test; :;");
	assert (builder.routines.routines->size () == 1);
	lambda_p::binder::list list;
	list [0] = boost::shared_ptr <lambda_p_kernel::adata_binder> (new lambda_p_kernel::adata_binder);
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	boost::shared_ptr <lambda_p::core::routine> routine (builder.routines.routines->operator[] (0));
	apply.core (routine, list, problems, declarations);
	assert (problems.errors.empty ());
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::nodes::adata> adata (boost::dynamic_pointer_cast <lambda_p_kernel::nodes::adata> (declarations [0]));
	assert (adata.get () != nullptr);
	assert (adata->string.compare ("test") == 0);
}