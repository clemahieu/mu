#include <lambda_p/core/data.h>

#include <lambda_p/core/routine.h>

lambda_p::core::data::data(::boost::shared_array <uint8_t> item_a, size_t size_a, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a)
	: routine (routine_a),
	item_m (item_a),
	size (size_a),
	self_statement (self_statement_a),
	self_argument (self_argument_a)
{
}

lambda_p::core::data::~data(void)
{
}

void lambda_p::core::data::validate (::std::iostream & problems) const
{
	validate_argument ("data: ", routine, self_statement, self_argument, problems);
}

::boost::shared_array <uint8_t> lambda_p::core::data::item () const
{
    return item_m;
}

::lambda_p::core::node_id lambda_p::core::data::node_type () const
{
	return ::lambda_p::core::node_data;
}