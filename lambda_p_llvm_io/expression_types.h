#pragma once

#include <lambda_p/visitor.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace llvm
{
	class Type;
}
namespace lambda_p
{
	class expression;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_llvm_io
{
	class routine_types;
	class expression_types : public lambda_p::visitor
	{
	public:
		expression_types (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_llvm_io::routine_types & routine_a, boost::shared_ptr <lambda_p::expression> expression_a);
		void operator () (lambda_p::expression * expression_a) override;
		void operator () (lambda_p::parameters * parameters_a) override;
		void operator () (lambda_p::reference * reference_a) override;
		void operator () (lambda_p::link * link_a) override;
		void operator () (lambda_p::node * node_a) override;
		boost::shared_ptr <lambda_p::errors::error_target> errors;
		boost::shared_ptr <lambda_p::node> current;
		lambda_p_llvm_io::routine_types & routine;
		llvm::Type * return_m;
		std::vector <llvm::Type *> parameters;
	};
}

