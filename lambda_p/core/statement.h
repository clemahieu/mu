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
			std::vector <size_t> target; // {TODO} Parser wants to have a place to put out of order declarations.  Uses vector reference + index for associations and this doesn't fit the abstraction.  Pointer doesn't work because vectors resize.
			lambda_p::core::association * association;
		};
	}
}
