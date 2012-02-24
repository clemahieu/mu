#pragma once

#include <io/source.h>
#include <io/lexer/lexer.h>
#include <io/parser/parser.h>
#include <io/analyzer/analyzer.h>
#include <io/ast/visitor.h>

#include <vector>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_list;
		}
	}
	namespace io
	{
		namespace ast
		{
			class node;
			class cluster;
		}
		class builder : public mu::io::ast::visitor
		{
		public:
			builder ();
			boost::shared_ptr <mu::core::errors::error_list> errors;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void add (boost::shared_ptr <mu::io::ast::node> node_a);
			void operator () (mu::io::ast::parameters * parameters_a) override;
			void operator () (mu::io::ast::expression * expression_a) override;
			void operator () (mu::io::ast::identifier * identifier_a) override;
			void operator () (mu::io::ast::end * end_a) override;
			boost::shared_ptr <mu::io::ast::node> current;
			boost::shared_ptr <mu::io::ast::cluster> building;
			std::vector <boost::shared_ptr <mu::io::ast::cluster>> clusters;
		};
	}
}
