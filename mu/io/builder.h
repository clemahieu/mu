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
		class builder : mu::io::source
		{
		public:
			using mu::io::source::operator ();
			builder (boost::shared_ptr <mu::io::debugging::stream> stream_a);
			builder (boost::shared_ptr <mu::io::debugging::stream> stream_a, boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
			void operator () (wchar_t char_a) override;
			boost::shared_ptr <mu::core::errors::error_list> errors;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			boost::shared_ptr <mu::io::debugging::stream> stream;
			mu::io::lexer::lexer lexer;
			void add (boost::shared_ptr <mu::core::cluster>, boost::shared_ptr <mu::io::debugging::mapping>);
			boost::shared_ptr <mu::core::cluster> cluster;
			boost::shared_ptr <mu::io::debugging::mapping> cluster_info;
		};
	}
}
