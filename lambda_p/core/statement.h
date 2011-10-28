#pragma once

#include <vector>

namespace lambda_p_kernel
{
	class bind_procedure;
}
namespace lambda_p
{
	namespace binder
	{
		class data;
	}
	namespace serialization
	{
		template <typename> class simple;
		namespace parser
		{
			class parser;
		}
	}
	namespace core
	{
		class routine;
		class association;
		class statement
		{
			friend class lambda_p::binder::data;
			friend class lambda_p_kernel::bind_procedure;
			template <typename> friend class lambda_p::serialization::simple;
			friend class lambda_p::serialization::parser::parser;
		public:
			statement ();
			~statement (void);
			size_t target;
			lambda_p::core::association * association;
		};
	}
}
