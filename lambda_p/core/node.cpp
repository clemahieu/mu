#include <lambda_p/core/node.h>

#include <lambda_p/core/routine.h>

#include <assert.h>

::lambda_p::core::node::node ()
{
}

::lambda_p::core::node::~node (void)
{
}

::std::wstring lambda_p::core::node_name (::lambda_p::core::node_id id)
{
	::std::wstring result;
	switch (id)
	{
	case ::lambda_p::core::node_data:
		{
			result.append (L"data");
		}
		break;
	case ::lambda_p::core::node_declaration:
		{
			result.append (L"declaration");
		}
		break;
	case ::lambda_p::core::node_reference:
		{
			result.append (L"reference");
		}
		break;
	default:
		assert (false);
		break;
	}

	return result;
}