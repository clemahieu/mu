#include "data_stream_binder.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_repl/data_stream.h>

void lambda_p_repl::data_stream_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			boost::shared_ptr <lambda_p_repl::data_stream> stream (new lambda_p_repl::data_stream (data->string ()));
			nodes [statement->association->declarations [0]] = stream;
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"data"), problems);
		}
	}
}

std::wstring lambda_p_repl::data_stream_binder::binder_name ()
{
	return std::wstring (L"data_stream_binder");
}