#include "data.h"

#include <lambda_p_serialization/extensions/data.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/data.h>

#include <boost/bind.hpp>

void lambda_p_serialization_test::data::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_serialization_test::data::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
	values.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (std::wstring (L"`"))));
	values.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (std::wstring (L"a"))));
	lambda_p_serialization::extensions::data data;
	auto results (data (values, 0, errors));
	assert (!(*errors) ());
	assert (results.first == 1);
	assert (results.second.size () == 1);
	auto data_l (boost::dynamic_pointer_cast <lambda_p::core::data> (results.second [0]));
	assert (data_l.get () != nullptr);
	assert (data_l->string == std::wstring (L"a"));
}

void lambda_p_serialization_test::data::run_2 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
	values.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (std::wstring (L"`"))));
	lambda_p_serialization::extensions::data data;
	auto results (data (values, 0, errors));
	assert ((*errors) ());
}

void lambda_p_serialization_test::data::run_3 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
	values.push_back (boost::shared_ptr <lambda_p_serialization::ast::node> (new lambda_p_serialization::ast::identifier (std::wstring (L"`"))));
	values.push_back (boost::shared_ptr <lambda_p_serialization::ast::expression> (new lambda_p_serialization::ast::expression (std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> ())));
	lambda_p_serialization::extensions::data data;
	auto results (data (values, 0, errors));
	assert ((*errors) ());
}