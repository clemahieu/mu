#include <mu/io_test/lexer.h>

#include <mu/io_test/lexer_result.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>
#include <mu/io/tokens/token.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/debugging/stream.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::io_test::lexer::run ()
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
	run_20 ();
	run_21 ();
}

void mu::io_test::lexer::run_1 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"");
	assert (result.results.empty ());
}

void mu::io_test::lexer::run_2 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"");
	lexer ();
	assert (result.results.size () == 1);
	auto t1 (result.results [0]);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t1.first) != nullptr);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 0);
	assert (t1.second.last.column == 1);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_3 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"a[];");
	lexer ();
	assert (result.results.size () == 5);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t3 (result.results [2]);
	auto t4 (result.results [3]);
	auto t5 (result.results [4]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 1);
	assert (t1i->string [0] == L'a');
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 0);
	assert (t1.second.last.column == 1);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::left_square *> (t2.first) != nullptr);
	assert (t2.second.first.character == 1);
	assert (t2.second.first.column == 2);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 1);
	assert (t2.second.last.column == 2);
	assert (t2.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::right_square *> (t3.first) != nullptr);
	assert (t3.second.first.character == 2);
	assert (t3.second.first.column == 3);
	assert (t3.second.first.row == 1);
	assert (t3.second.last.character == 2);
	assert (t3.second.last.column == 3);
	assert (t3.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::divider *> (t4.first) != nullptr);
	assert (t4.second.first.character == 3);
	assert (t4.second.first.column == 4);
	assert (t4.second.first.row == 1);
	assert (t4.second.last.character == 3);
	assert (t4.second.last.column == 4);
	assert (t4.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t5.first) != nullptr);
	assert (t5.second.first.character == 4);
	assert (t5.second.first.column == 5);
	assert (t5.second.first.row == 1);
	assert (t5.second.last.character == 4);
	assert (t5.second.last.column == 5);
	assert (t5.second.last.row == 1);
}

void mu::io_test::lexer::run_4 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"||");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 0);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 1);
	assert (t1.second.last.column == 2);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 2);
	assert (t2.second.first.column == 3);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 2);
	assert (t2.second.last.column == 3);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_5 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"|a|a");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string.size () == 0);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 3);
	assert (t1.second.last.column == 4);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 4);
	assert (t2.second.first.column == 5);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 4);
	assert (t2.second.last.column == 5);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_6 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"|a||;[]:a");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == std::wstring (L"|;[]:"));
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 8);
	assert (t1.second.last.column == 9);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 9);
	assert (t2.second.first.column == 10);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 9);
	assert (t2.second.last.column == 10);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_7 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"|:a||;[]:a");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t2 (result.results [1]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == std::wstring (L"|;[]"));
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 9);
	assert (t1.second.last.column == 10);
	assert (t1.second.last.row == 1);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 10);
	assert (t2.second.first.column == 11);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 10);
	assert (t2.second.last.column == 11);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_8 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":- a\nb");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i->string == std::wstring (L"b"));
	assert (t1.second.first.character == 5);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 2);
	assert (t1.second.last.character == 5);
	assert (t1.second.last.column == 1);
	assert (t1.second.last.row == 2);
	auto t2 (result.results [1]);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 6);
	assert (t2.second.first.column == 2);
	assert (t2.second.first.row == 2);
	assert (t2.second.last.character == 6);
	assert (t2.second.last.column == 2);
	assert (t2.second.last.row == 2);
}

void mu::io_test::lexer::run_9 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":{ a :} b");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i->string == std::wstring (L"b"));
	assert (t1.second.first.character == 8);
	assert (t1.second.first.column == 9);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 8);
	assert (t1.second.last.column == 9);
	assert (t1.second.last.row == 1);
	auto t2 (result.results [1]);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 9);
	assert (t2.second.first.column == 10);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 9);
	assert (t2.second.last.column == 10);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_10 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":{:{ a :}:} b");
	lexer ();
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i->string == std::wstring (L"b"));
	assert (t1.second.first.character == 12);
	assert (t1.second.first.column == 13);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 12);
	assert (t1.second.last.column == 13);
	assert (t1.second.last.row == 1);
	auto t2 (result.results [1]);
	assert (dynamic_cast <mu::io::tokens::stream_end *> (t2.first) != nullptr);
	assert (t2.second.first.character == 13);
	assert (t2.second.first.column == 14);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 13);
	assert (t2.second.last.column == 14);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_11 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":~");
	assert (result.results.size () == 1);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::parameters *> (t1.first));
	assert (t1i != nullptr);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 1);
	assert (t1.second.last.column == 2);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_12 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":~]");
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::parameters *> (t1.first));
	assert (t1i != nullptr);
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 1);
	assert (t1.second.last.column == 2);
	assert (t1.second.last.row == 1);
	auto t2 (result.results [1]);
	auto t2i (dynamic_cast <mu::io::tokens::right_square *> (t2.first));
	assert (t2i != nullptr);
	assert (t2.second.first.character == 2);
	assert (t2.second.first.column == 3);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 2);
	assert (t2.second.last.column == 3);
	assert (t2.second.last.row == 1);
}

void mu::io_test::lexer::run_13 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":a20");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == std::wstring (L" "));
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 3);
	assert (t1.second.last.column == 4);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_14 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"thing:a20");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L"thing ");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 8);
	assert (t1.second.last.column == 9);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_15 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":a20thing");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L" thing");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 8);
	assert (t1.second.last.column == 9);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_16 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":u00000020");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L" ");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 9);
	assert (t1.second.last.column == 10);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_17 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"thing:u00000020");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L"thing ");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 14);
	assert (t1.second.last.column == 15);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_18 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":u00000020thing");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L" thing");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 14);
	assert (t1.second.last.column == 15);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_19 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":a7C:a3A:a3b:a5b:a5d");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 2);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L"|:;[]");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 19);
	assert (t1.second.last.column == 20);
	assert (t1.second.last.row == 1);
}

void mu::io_test::lexer::run_20 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"thing:~a");
	lexer ();
	assert (errors->errors.empty ());
	assert (result.results.size () == 4);
	auto t1 (result.results [0]);
	auto t1i (dynamic_cast <mu::io::tokens::identifier *> (t1.first));
	assert (t1i != nullptr);
	assert (t1i->string == L"thing");
	assert (t1.second.first.character == 0);
	assert (t1.second.first.column == 1);
	assert (t1.second.first.row == 1);
	assert (t1.second.last.character == 4);
	assert (t1.second.last.column == 5);
	assert (t1.second.last.row == 1);
	auto t2 (result.results [1]);
	auto t2i (dynamic_cast <mu::io::tokens::parameters *> (t2.first));
	assert (t2i != nullptr);
	assert (t2.second.first.character == 5);
	assert (t2.second.first.column == 6);
	assert (t2.second.first.row == 1);
	assert (t2.second.last.character == 6);
	assert (t2.second.last.column == 7);
	assert (t2.second.last.row == 1);
	auto t3 (result.results [2]);
	auto t3i (dynamic_cast <mu::io::tokens::identifier *> (t3.first));
	assert (t3i != nullptr);
	assert (t3i->string == L"a");
	assert (t3.second.first.character == 7);
	assert (t3.second.first.column == 8);
	assert (t3.second.first.row == 1);
	assert (t3.second.last.character == 7);
	assert (t3.second.last.column == 8);
	assert (t3.second.last.row == 1);
	auto t4 (result.results [3]);
	auto t4i (dynamic_cast <mu::io::tokens::stream_end *> (t4.first));
	assert (t4i != nullptr);
	assert (t4.second.first.character == 8);
	assert (t4.second.first.column == 9);
	assert (t4.second.first.row == 1);
	assert (t4.second.last.character == 8);
	assert (t4.second.last.column == 9);
	assert (t4.second.last.row == 1);
}

void mu::io_test::lexer::run_21 ()
{
	mu::io_test::lexer_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L"\r \rthing thing\r \r[ [\r \r] ]\r \r:~ :~\r \r:a50 :a50\r \r:u00000050 :u00000050\r \r; ;\r");
	lexer ();
    assert (result.results.size () == 15);
}