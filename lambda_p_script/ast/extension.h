#pragma once

#include <io/analyzer/extensions/extension.h>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class node;
			class cluster;
		}
	}
}
namespace lambda_p_script
{
	namespace ast
	{
		class extension : public mu::io::analyzer::extensions::extension
		{
		public:
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a) override;
			boost::shared_ptr <mu::io::ast::cluster> core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::io::ast::node> node_a);
		};
	}
}

