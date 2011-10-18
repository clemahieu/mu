#include "file_stream_binder.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_repl/file_stream.h>
#include <lambda_p/binder/list.h>

#include <boost/filesystem.hpp>

void lambda_p_repl::file_stream_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::list> list (::boost::dynamic_pointer_cast < ::lambda_p::binder::list> (instances [statement->association->parameters [0]]));
		if (list.get () != NULL)
		{
			auto path (boost::filesystem::initial_path ());
			for (auto i = list->instances.begin (); i != list->instances.end (); ++i)
			{
				::boost::shared_ptr < ::lambda_p::binder::data> data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (*i));
				if (data.get () != nullptr)
				{
					path /= data->string ();
				}
				else
				{
					add_error (::std::wstring (L"Expecting all list element to be data"), problems);
				}
			}
			if (problems.empty ())
			{
				::boost::shared_ptr < ::lambda_p_repl::file_stream> stream (new ::lambda_p_repl::file_stream (path.wstring ()));
				instances [statement->association->results [0]] = stream;
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"data"), problems);
		}
	}
}

::std::wstring lambda_p_repl::file_stream_binder::binder_name ()
{
	return ::std::wstring (L"file_stream_binder");
}