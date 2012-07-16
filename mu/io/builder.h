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
			builder ();
			builder (mu::io::analyzer::extensions::extensions * extensions_a);
			void operator () (char32_t char_a) override;
			mu::core::errors::error_list * errors;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void add (mu::core::cluster *);
			mu::core::cluster * cluster;
		};
	}
}
