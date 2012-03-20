#pragma once

#include <mu/io/source.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/parser/parser.h>
#include <mu/io/analyzer/analyzer.h>

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
		namespace debugging
		{
			class mapping;
		}
		class builder
		{
		public:
			builder ();
			boost::shared_ptr <mu::core::errors::error_list> errors;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void add (boost::shared_ptr <mu::core::cluster>, boost::shared_ptr <mu::io::debugging::mapping>);
			std::vector <boost::shared_ptr <mu::core::cluster>> clusters;
			std::vector <boost::shared_ptr <mu::io::debugging::mapping>> cluster_infos;
		};
	}
}
