#include "lexer.h"

#include <lambda_p_io_test/lexer_result.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/source.h>
#include <lambda_p_io/tokens/token.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/tokens/parameters.h>
#include <lambda_p/errors/error_list.h>

#include <boost/bind.hpp>

void lambda_p_io_test::lexer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
	run_13 ();
	run_14 ();
	run_15 ();
	run_16 ();
	run_17 ();
	run_18 ();
	run_19 ();
}

void lambda_p_io_test::lexer::run_1 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"");
	assert (result.results.empty ());
}

void lambda_p_io_test::lexer::run_2 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"");
	source ();
	assert (result.results.size () == 1);
	auto t1 (result.results [0]);
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t1.first) != nullptr);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 0);
	assert (t1.second.last.column == 1);
	assert (t1.second.last.row == 1);
}

void lambda_p_io_test::lexer::run_3 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"a[];");
	source ();
	assert (result.results.size () == 5);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t3 (result.results [2]);
	auto t4 (result.results [3]);
	auto t5 (result.results [4]);
	auto t1i (dynamic_cast <lambda_p_io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 1);
	assert (t1i->string [0] == L'a');
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 0);
	assert (t1.second.last.column == 1);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::left_square *> (t2.first) != nullptr);
	assert (t2.second.first.character == 1);
	assert (t2.second.first.column == 2);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 1);
	assert (t2.second.last.column == 2);
	assert (t2.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::right_square *> (t3.first) != nullptr);
	assert (t3.second.first.character == 2);
	assert (t3.second.first.column == 3);
	assert (t3.second.first.row == 1);
	assert (t3.second.last.character == 2);
	assert (t3.second.last.column == 3);
	assert (t3.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::divider *> (t4.first) != nullptr);
	assert (t4.second.first.character == 3);
	assert (t4.second.first.column == 4);
	assert (t4.second.first.row == 1);
	assert (t4.second.last.character == 3);
	assert (t4.second.last.column == 4);
	assert (t4.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t5.first) != nullptr);
	assert (t5.second.first.character == 4);
	assert (t5.second.first.column == 5);
	assert (t5.second.first.row == 1);
	assert (t5.second.last.character == 4);
	assert (t5.second.last.column == 5);
	assert (t5.second.last.row == 1);
}

void lambda_p_io_test::lexer::run_4 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"||");
	source ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <lambda_p_io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 0);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 1);
	assert (t1.second.last.column == 2);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 2);
	assert (t2.second.first.column == 3);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 2);
	assert (t2.second.last.column == 3);
	assert (t2.second.last.row == 1);
}

void lambda_p_io_test::lexer::run_5 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"|a|a");
	source ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <lambda_p_io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 0);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 3);
	assert (t1.second.last.column == 4);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 4);
	assert (t2.second.first.column == 5);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 4);
	assert (t2.second.last.column == 5);
	assert (t2.second.last.row == 1);
}

void lambda_p_io_test::lexer::run_6 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"|a||;[]:a");
	source ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <lambda_p_io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == std::wstring (L"|;[]:"));
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 8);
	assert (t1.second.last.column == 9);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 9);
	assert (t2.second.first.column == 10);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 9);
	assert (t2.second.last.column == 10);
	assert (t2.second.last.row == 1);
}

void lambda_p_io_test::lexer::run_7 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"|:a||;[]:a");
	source ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <lambda_p_io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == std::wstring (L"|;[]"));
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (t2.first) != nullptr);
}

void lambda_p_io_test::lexer::run_8 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":- a\nb");
	source ();
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1->string == std::wstring (L"b"));
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (result.results [1].first) != nullptr);
}

void lambda_p_io_test::lexer::run_9 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":[ a :] b");
	source ();
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1->string == std::wstring (L"b"));
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (result.results [1].first) != nullptr);
}

void lambda_p_io_test::lexer::run_10 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":[:[ a :]:] b");
	source ();
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1->string == std::wstring (L"b"));
	assert (dynamic_cast <lambda_p_io::tokens::stream_end *> (result.results [1].first) != nullptr);
}

void lambda_p_io_test::lexer::run_11 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":~");
	assert (result.results.size () == 1);
	auto t1 (dynamic_cast <lambda_p_io::tokens::parameters *> (result.results [0].first));
	assert (t1 != nullptr);
}

void lambda_p_io_test::lexer::run_12 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":~]");
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::parameters *> (result.results [0].first));
	assert (t1 != nullptr);
	auto t2 (dynamic_cast <lambda_p_io::tokens::right_square *> (result.results [1].first));
	assert (t2 != nullptr);
}

void lambda_p_io_test::lexer::run_13 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":a20");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == std::wstring (L" "));
}

void lambda_p_io_test::lexer::run_14 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"thing:a20");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L"thing ");
}

void lambda_p_io_test::lexer::run_15 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":a20thing");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L" thing");
}

void lambda_p_io_test::lexer::run_16 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":u00000020");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L" ");
}

void lambda_p_io_test::lexer::run_17 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L"thing:u00000020");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L"thing ");
}

void lambda_p_io_test::lexer::run_18 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":u00000020thing");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L" thing");
}

void lambda_p_io_test::lexer::run_19 ()
{
	lambda_p_io_test::lexer_result result;
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p_io::lexer::lexer lexer (errors, boost::bind (&lambda_p_io_test::lexer_result::operator (), &result, _1, _2));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator (), &lexer, _1));
	source (L":a7C:a3A:a3b:a5b:a5d");
	source ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (dynamic_cast <lambda_p_io::tokens::identifier *> (result.results [0].first));
	assert (t1 != nullptr);
	assert (t1->string == L"|:;[]");
}