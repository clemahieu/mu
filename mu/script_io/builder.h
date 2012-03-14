#pragma once

#include <mu/io/source.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/parser/parser.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/errors/error_list.h>
#include <mu/script_io/synthesizer.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class cluster;
		}
	}
	namespace script
	{
		namespace closure
		{
			class single;
		}
		namespace cluster
		{
			class node;
		}
		namespace exec
		{
			class operation;
		}
	}
	namespace script_io
	{
		boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions ();
		void add_loadb (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a);
		void add_loads (boost::shared_ptr <mu::io::analyzer::extensions::extensions> result_a);
		class builder
		{
		public:
			builder ();
			builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
			boost::shared_ptr <mu::core::errors::error_list> errors;
			mu::script_io::synthesizer synthesizer;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void operator () (boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::cluster> cluster_info_a);
			std::vector <boost::shared_ptr <mu::script::cluster::node>> clusters;
		};
	}
}

