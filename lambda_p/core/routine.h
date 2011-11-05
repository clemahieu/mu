#pragma once

#include <vector>
#include <map>

#include <lambda_p/core/position.h>
#include <lambda_p/binder/list.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_test
{
	class parser_test_1;
}
namespace lambda_p_repl
{
	class entry_environment;
}
namespace lambda_p_kernel
{
	class bind_procedure;
}
namespace lambda_p
{
	namespace binder
	{
		class node;
		class bind_procedure;
		class data;
	}
	namespace serialization
	{
		template <typename> class simple;
	}
	namespace parser
	{
		class parser;
		class statement;
		class routine;
	}
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class association;
		class statement;
		class routine
		{
			friend class lambda_p::core::statement;
			friend class lambda_p::binder::data;
            template <typename> friend class lambda_p::serialization::simple;
			friend class lambda_p::parser::parser;
			friend class lambda_p_kernel::bind_procedure;
			friend class lambda_p::parser::statement;
			friend class lambda_p_repl::entry_environment;
			friend class lambda_p::parser::routine;
			friend class lambda_p_test::parser_test_1;
		private:
		public:
			routine ();
			~routine (void);
			lambda_p::core::statement * add_statement ();
			size_t add_data (std::wstring string);
			size_t inject_declaration (boost::shared_ptr <lambda_p::binder::node> node_a);
			size_t add_declaration ();
            void placement (std::map <size_t, lambda_p::core::position> & argument_positions, std::map <lambda_p::core::statement const *, size_t> & statement_positions) const;
			void validate (std::vector <lambda_p::errors::error *> & problems) const;
			lambda_p::core::association * surface;
			std::vector <lambda_p::core::statement *> statements;
		private:
			lambda_p::core::association * injected_surface;
			lambda_p::binder::list injected;
			void validate_node (size_t node, size_t current_statement, size_t current_argument, std::vector <lambda_p::errors::error *> & problems) const;
			size_t nodes;
		};
	}
}
