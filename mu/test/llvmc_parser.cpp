#include <gtest/gtest.h>

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/partial_ast.hpp>
#include <mu/core/error.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/instruction_type.hpp>
#include <mu/core/string_hash.hpp>

#include <llvm/DerivedTypes.h>

#include <gc_cpp.h>

class test_parser
{
public:
    test_parser (char const * const text_a):
    text (text_a),
    stream (text, 16),
    lexer (stream),
    stream_token (lexer, 2),
    parser (stream_token)
    {        
    };
    std::stringstream text;
    mu::io::stream_istream stream;
    mu::io::lexer lexer;
    mu::io::stream_token stream_token;
    mu::llvmc::parser parser;
};

static mu::string test_non_covering_name (U"test_non_covering");

class test_non_covering : public mu::llvmc::hook
{
public:    
    mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool covering () override
    {
        return false;
    }
    mu::string const & name () override
    {
        return test_non_covering_name;
    }
};

static mu::string test_covering_name (U"test_covering");
class test_covering : public mu::llvmc::hook
{
public:
    mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser) override
    {
        return mu::llvmc::node_result {new (GC) mu::llvmc::ast::node, nullptr};
    }
    bool covering () override
    {
        return true;
    }
    mu::string const & name () override
    {
        return test_covering_name;
    }
};

TEST (llvmc_parser, mapping_get_hook)
{
    mu::llvmc::keywords mapping;
    auto keyword1 (mapping.get_hook (mu::string (U"keyword")));
    EXPECT_EQ (nullptr, keyword1.hook);
}

TEST (llvmc_parser, mapping_get_covered)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error (mapping.insert (mu::string (U"non-covered"), &keyword1));
    EXPECT_EQ (false, error);
    auto keyword2 (mapping.get_hook (mu::string (U"non-covered")));
    EXPECT_EQ (&keyword1, keyword2.hook);
    auto keyword3 (mapping.get_hook (mu::string (U"non-covered1")));
    EXPECT_EQ (nullptr, keyword3.hook);
    auto keyword4 (mapping.get_hook (mu::string (U"non-covere")));
    EXPECT_EQ (nullptr, keyword4.hook);
}

TEST (llvmc_parser, mapping_get_non_covered)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error);
    auto keyword2 (mapping.get_hook (mu::string (U"covered")));
    EXPECT_EQ (&keyword1, keyword2.hook);
    EXPECT_EQ (mu::string (U""), keyword2.data);
    auto keyword3 (mapping.get_hook (mu::string (U"covered1")));
    EXPECT_EQ (&keyword1, keyword3.hook);
    EXPECT_EQ (mu::string (U"1"), keyword3.data);
    auto keyword4 (mapping.get_hook (mu::string (U"covere")));
    EXPECT_EQ (nullptr, keyword4.hook);
}

TEST (llvmc_parser, mapping_insert_under_covered)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    test_non_covering keyword2;
    auto error2 (mapping.insert (mu::string (U"covered1"), &keyword2));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, mapping_insert_covering_existing)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered1"), &keyword1));
    EXPECT_EQ (false, error1);
    test_covering keyword2;
    auto error2 (mapping.insert (mu::string (U"covered"), &keyword2));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, global_check_non_covering)
{
    test_non_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::global global (&mapping);
    mu::llvmc::ast::unit unit1;
    auto error2 (global.insert (mu::string (U"covered"), &unit1));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, global_check_covering)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto error1 (mapping.insert (mu::string (U"covered"), &keyword1));
    EXPECT_EQ (false, error1);
    mu::llvmc::global global (&mapping);
    mu::llvmc::ast::unit unit1;
    auto error2 (global.insert (mu::string (U"covered1"), &unit1));
    EXPECT_EQ (true, error2);
}

TEST (llvmc_parser, unresolved_passing)
{
    test_covering keyword1;
    mu::llvmc::keywords mapping;
    auto called (false);
    mu::llvmc::global global (&mapping);
    {
        mu::llvmc::block block (&global);
        block.refer (mu::string (U"test"), mu::empty_region, 
				[&] 
		(mu::llvmc::ast::node *, mu::core::region const & region_a) 
				{called = true;});
        EXPECT_TRUE (global.unresolved.empty ());
    }
    EXPECT_FALSE (global.unresolved.empty ());
}

TEST (llvmc_parser, block)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    mu::llvmc::ast::node node;
    auto error (block.insert (mu::string (U"test"), &node));
    EXPECT_TRUE (!error);
    auto success (false);
    block.refer (mu::string (U"test"), mu::empty_region,
                 [&success]
                 (mu::llvmc::ast::node * node_a, mu::core::region const & region_a)
                 {
                     success = true;
                 });
    EXPECT_TRUE (success);
}

TEST (llvmc_parser, block_get)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    mu::llvmc::ast::node node;
    auto success (false);
    auto val (block.get (mu::string (U"test"), mu::empty_region,
                         [&success]
                         (mu::llvmc::ast::node * node_a, mu::core::region const & region_a)
                         {
                             success = true;
                         }));
    EXPECT_TRUE (val);
    EXPECT_FALSE (success);
}

TEST (llvmc_parser, block_resolve)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    mu::llvmc::ast::node node;
    auto success (false);
    block.refer (U"test", mu::empty_region,
                         [&success]
                         (mu::llvmc::ast::node * node_a, mu::core::region const & region_a)
                         {
                             success = true;
                         });
    EXPECT_FALSE (success);
    block.insert (U"test", &node);
    EXPECT_TRUE (success);
}

TEST (llvmc_parser, block_reuse_id)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    auto fail1 (block.reserve (U"test"));
    ASSERT_FALSE (fail1);
    auto fail2 (block.reserve (U"test"));
    ASSERT_FALSE (fail2);
    {
        mu::llvmc::block block2 (&block);
        mu::llvmc::ast::node node;
        auto fail (block2.insert (U"test", &node));
        EXPECT_FALSE (fail);
    }
    {
        mu::llvmc::block block2 (&block);
        mu::llvmc::ast::node node;
        auto fail (block2.insert (U"test", &node));
        EXPECT_FALSE (fail);
    }
}

TEST (llvmc_parser, block_refer_reserved)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    mu::llvmc::block block (&global);
    auto fail1 (block.reserve (U"test"));
    ASSERT_FALSE (fail1);
    {
        mu::llvmc::block block2 (&block);
        mu::llvmc::ast::node node;
        auto test (false);
        block2.refer (U"test", mu::empty_region,
            [&]
            (mu::llvmc::ast::node * node_a, mu::core::region const & region_a)
            {
                test = true;
            }
        );
        EXPECT_FALSE (test);
    }
}

TEST (llvmc_parser, global_refer_reserved)
{
    mu::llvmc::keywords keywords;
    mu::llvmc::global global (&keywords);
    auto fail1 (global.reserve (U"test"));
    ASSERT_FALSE (fail1);
    auto test (false);
    global.refer (U"test", mu::empty_region,
        [&]
        (mu::llvmc::ast::node * node_a, mu::core::region const & region_a)
        {
            test = true;
        }
    );
    EXPECT_FALSE (test);
}

TEST (llvmc_parser, empty)
{
    test_parser parser ("");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    EXPECT_EQ (0, module2->globals.size ());
}

TEST (llvmc_parser, empty_reserved)
{
    test_parser parser ("");
	auto failure (parser.parser.builtins.reserve (U"test"));
	ASSERT_FALSE (failure);
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    EXPECT_EQ (0, module2->globals.size ());
	ASSERT_EQ (0, module2->names.size ());
}

TEST (llvmc_parser, top_identifier_error)
{
    test_parser parser ("thing");
    auto module1 (parser.parser.parse ());
    ASSERT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::region (0, 1, 1, 4, 1, 5), module1.error->region ());
}

TEST (llvmc_parser, expression_no_end_error)
{
    test_parser parser ("[");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::region (1, 1, 2, 1, 1, 2), module1.error->region ());
}

TEST (llvmc_parser, simple)
{
    test_parser parser ("let test function [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
	ASSERT_EQ (mu::core::region (0, 1, 1, 26, 1, 27), module2->region);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
	ASSERT_EQ (U"test", element1->name);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
	ASSERT_EQ (mu::core::region (9, 1, 10, 25, 1, 26), function1->region);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	ASSERT_EQ (1, module2->names.size ());
	auto existing (module2->names.find (U"test"));
	ASSERT_NE (module2->names.end (), existing);
}

TEST (llvmc_parser, instructions)
{
    test_parser parser ("let test function [] [[add alloca and ashr atomicrmw bitcast call cmpxchg extractelement extractvalue fadd fcmp fdiv fence fmul fpext fptoi fptosi fptoui fptrunc frem fsub getelementptr icmp insertelement insertvalue load lshr mul or ptrfromint ptrtoint sdiv select sext shl shufflevector sitofp srem store switch sub trunc udiv uitofp urem xor zext]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    EXPECT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (mu::core::region (22, 1, 23, 349, 1, 350), expression1->region);
    ASSERT_EQ (48, expression1->arguments.size ());
	size_t arg (0);
    auto argument1 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument1);
    auto value1 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument1->node_m));
    ASSERT_NE (nullptr, value1);
    ASSERT_EQ (mu::llvmc::instruction_type::add, value1->type);
    auto argument2 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument2);
    auto value2 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument2->node_m));
    ASSERT_NE (nullptr, value2);
    ASSERT_EQ (mu::llvmc::instruction_type::alloca, value2->type);
    auto argument3 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument3);
    auto value3 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument3->node_m));
    ASSERT_NE (nullptr, value3);
    ASSERT_EQ (mu::llvmc::instruction_type::and_i, value3->type);
    auto argument4 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument4);
    auto value4 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument4->node_m));
    ASSERT_NE (nullptr, value4);
    ASSERT_EQ (mu::llvmc::instruction_type::ashr, value4->type);
    auto argument5 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument5);
    auto value5 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument5->node_m));
    ASSERT_NE (nullptr, value5);
    ASSERT_EQ (mu::llvmc::instruction_type::atomicrmw, value5->type);
    auto argument6 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument6);
    auto value6 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument6->node_m));
    ASSERT_NE (nullptr, value6);
    ASSERT_EQ (mu::llvmc::instruction_type::bitcast, value6->type);
    auto argument7 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument7);
    auto value7 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument7->node_m));
    ASSERT_NE (nullptr, value7);
    ASSERT_EQ (mu::llvmc::instruction_type::call, value7->type);
    auto argument8 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument8);
    auto value8 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument8->node_m));
    ASSERT_NE (nullptr, value8);
    ASSERT_EQ (mu::llvmc::instruction_type::cmpxchg, value8->type);
    auto argument9 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument9);
    auto value9 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument9->node_m));
    ASSERT_NE (nullptr, value9);
    ASSERT_EQ (mu::llvmc::instruction_type::extractelement, value9->type);
    auto argument10 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument10);
    auto value10 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument10->node_m));
    ASSERT_NE (nullptr, value10);
    ASSERT_EQ (mu::llvmc::instruction_type::extractvalue, value10->type);
    auto argument11 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument11);
    auto value11 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument11->node_m));
    ASSERT_NE (nullptr, value11);
    ASSERT_EQ (mu::llvmc::instruction_type::fadd, value11->type);
    auto argument12 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument12);
    auto value12 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument12->node_m));
    ASSERT_NE (nullptr, value12);
    ASSERT_EQ (mu::llvmc::instruction_type::fcmp, value12->type);
    auto argument13 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument13);
    auto value13 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument13->node_m));
    ASSERT_NE (nullptr, value13);
    ASSERT_EQ (mu::llvmc::instruction_type::fdiv, value13->type);
    auto argument14 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument11);
    auto value14 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument14->node_m));
    ASSERT_NE (nullptr, value14);
    ASSERT_EQ (mu::llvmc::instruction_type::fence, value14->type);
    auto argument15 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument15);
    auto value15 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument15->node_m));
    ASSERT_NE (nullptr, value15);
    ASSERT_EQ (mu::llvmc::instruction_type::fmul, value15->type);
    auto argument16 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument16);
    auto value16 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument16->node_m));
    ASSERT_NE (nullptr, value16);
    ASSERT_EQ (mu::llvmc::instruction_type::fpext, value16->type);
    auto argument17 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument17);
    auto value17 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument17->node_m));
    ASSERT_NE (nullptr, value17);
    ASSERT_EQ (mu::llvmc::instruction_type::fptoi, value17->type);
    auto argument18 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument18);
    auto value18 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument18->node_m));
    ASSERT_NE (nullptr, value18);
    ASSERT_EQ (mu::llvmc::instruction_type::fptosi, value18->type);
    auto argument19 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument19);
    auto value19 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument19->node_m));
    ASSERT_NE (nullptr, value19);
    ASSERT_EQ (mu::llvmc::instruction_type::fptoui, value19->type);
    auto argument20 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument20);
    auto value20 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument20->node_m));
    ASSERT_NE (nullptr, value20);
    ASSERT_EQ (mu::llvmc::instruction_type::fptrunc, value20->type);
    auto argument21 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument21);
    auto value21 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument21->node_m));
    ASSERT_NE (nullptr, value21);
    ASSERT_EQ (mu::llvmc::instruction_type::frem, value21->type);
    auto argument22 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument22);
    auto value22 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument22->node_m));
    ASSERT_NE (nullptr, value22);
    ASSERT_EQ (mu::llvmc::instruction_type::fsub, value22->type);
    auto argument23 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument23);
    auto value23 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument23->node_m));
    ASSERT_NE (nullptr, value23);
    ASSERT_EQ (mu::llvmc::instruction_type::getelementptr, value23->type);
    auto argument24 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument24);
    auto value24 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument24->node_m));
    ASSERT_NE (nullptr, value24);
    ASSERT_EQ (mu::llvmc::instruction_type::icmp, value24->type);
    auto argument25 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument25);
    auto value25 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument25->node_m));
    ASSERT_NE (nullptr, value25);
    ASSERT_EQ (mu::llvmc::instruction_type::insertelement, value25->type);
    auto argument26 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument26);
    auto value26 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument26->node_m));
    ASSERT_NE (nullptr, value26);
    ASSERT_EQ (mu::llvmc::instruction_type::insertvalue, value26->type);
    auto argument27 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument27);
    auto value27 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument27->node_m));
    ASSERT_NE (nullptr, value27);
    ASSERT_EQ (mu::llvmc::instruction_type::load, value27->type);
    auto argument28 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument28);
    auto value28 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument28->node_m));
    ASSERT_NE (nullptr, value28);
    ASSERT_EQ (mu::llvmc::instruction_type::lshr, value28->type);
    auto argument29 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument29);
    auto value29 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument29->node_m));
    ASSERT_NE (nullptr, value29);
    ASSERT_EQ (mu::llvmc::instruction_type::mul, value29->type);
    auto argument30 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument30);
    auto value30 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument30->node_m));
    ASSERT_NE (nullptr, value30);
    ASSERT_EQ (mu::llvmc::instruction_type::or_i, value30->type);
    auto argument31 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument31);
    auto value31 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument31->node_m));
    ASSERT_NE (nullptr, value31);
    ASSERT_EQ (mu::llvmc::instruction_type::inttoptr, value31->type);
    auto argument32 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument32);
    auto value32 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument32->node_m));
    ASSERT_NE (nullptr, value32);
    ASSERT_EQ (mu::llvmc::instruction_type::ptrtoint, value32->type);
    auto argument33 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument33);
    auto value33 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument33->node_m));
    ASSERT_NE (nullptr, value33);
    ASSERT_EQ (mu::llvmc::instruction_type::sdiv, value33->type);
    auto argument34 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument34);
    auto value34 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument34->node_m));
    ASSERT_NE (nullptr, value34);
    ASSERT_EQ (mu::llvmc::instruction_type::select, value34->type);
    auto argument35 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument35);
    auto value35 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument35->node_m));
    ASSERT_NE (nullptr, value35);
    ASSERT_EQ (mu::llvmc::instruction_type::sext, value35->type);
    auto argument36 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument36);
    auto value36 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument36->node_m));
    ASSERT_NE (nullptr, value36);
    ASSERT_EQ (mu::llvmc::instruction_type::shl, value36->type);
    auto argument37 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument37);
    auto value37 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument37->node_m));
    ASSERT_NE (nullptr, value37);
    ASSERT_EQ (mu::llvmc::instruction_type::shufflevector, value37->type);
    auto argument38 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument38);
    auto value38 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument38->node_m));
    ASSERT_NE (nullptr, value38);
    ASSERT_EQ (mu::llvmc::instruction_type::sitofp, value38->type);
    auto argument39 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument39);
    auto value39 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument39->node_m));
    ASSERT_NE (nullptr, value39);
    ASSERT_EQ (mu::llvmc::instruction_type::srem, value39->type);
    auto argument40 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument40);
    auto value40 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument40->node_m));
    ASSERT_NE (nullptr, value40);
    ASSERT_EQ (mu::llvmc::instruction_type::store, value40->type);
    auto argument48 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument48);
    auto value48 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument48->node_m));
    ASSERT_NE (nullptr, value48);
    ASSERT_EQ (mu::llvmc::instruction_type::switch_i, value48->type);
    auto argument41 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument41);
    auto value41 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument41->node_m));
    ASSERT_NE (nullptr, value41);
    ASSERT_EQ (mu::llvmc::instruction_type::sub, value41->type);
    auto argument42 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument42);
    auto value42 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument42->node_m));
    ASSERT_NE (nullptr, value42);
    ASSERT_EQ (mu::llvmc::instruction_type::trunc, value42->type);
    auto argument43 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument43);
    auto value43 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument43->node_m));
    ASSERT_NE (nullptr, value43);
    ASSERT_EQ (mu::llvmc::instruction_type::udiv, value43->type);
    auto argument44 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument44);
    auto value44 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument44->node_m));
    ASSERT_NE (nullptr, value44);
    ASSERT_EQ (mu::llvmc::instruction_type::uitofp, value44->type);
    auto argument45 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument45);
    auto value45 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument45->node_m));
    ASSERT_NE (nullptr, value45);
    ASSERT_EQ (mu::llvmc::instruction_type::urem, value45->type);
    auto argument46 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument46);
    auto value46 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument46->node_m));
    ASSERT_NE (nullptr, value46);
    ASSERT_EQ (mu::llvmc::instruction_type::xor_i, value46->type);
    auto argument47 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [arg++]));
    ASSERT_NE (nullptr, argument47);
    auto value47 (dynamic_cast <mu::llvmc::skeleton::marker *> (argument47->node_m));
    ASSERT_NE (nullptr, value47);
    ASSERT_EQ (mu::llvmc::instruction_type::zext, value47->type);
}

TEST (llvmc_parser, number)
{
    test_parser parser ("let test function [] [[#100]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    EXPECT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (mu::core::region (22, 1, 23, 27, 1, 28), expression1->region);
    ASSERT_EQ (1, expression1->arguments.size ());
    auto argument1 (dynamic_cast <mu::llvmc::ast::number *> (expression1->arguments [0]));
    ASSERT_EQ (mu::core::region (23, 1, 24, 26, 1, 27), argument1->region);
    ASSERT_NE (nullptr, argument1);
    ASSERT_EQ (U"100", argument1->number_m);
}

TEST (llvmc_parser, rational)
{
    test_parser parser ("let test function [] [[#100/1000]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    EXPECT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
    auto argument1 (dynamic_cast <mu::llvmc::ast::number *> (expression1->arguments [0]));
    ASSERT_NE (nullptr, argument1);
    ASSERT_EQ (U"100/1000", argument1->number_m);
}

TEST (llvmc_parser, constant_int)
{
    test_parser parser ("let test function [] [[cint int32 #42]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    EXPECT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (mu::core::region (22, 1, 23, 37, 1, 38), expression1->region);
	ASSERT_EQ (3, expression1->arguments.size ());
	auto constant_int (dynamic_cast <mu::llvmc::ast::constant_int *> (expression1->arguments [0]));
	ASSERT_NE (nullptr, constant_int);
	auto type (dynamic_cast <mu::llvmc::ast::integer_type *> (expression1->arguments [1]));
	ASSERT_NE (nullptr, type);
	auto number (dynamic_cast <mu::llvmc::ast::number *> (expression1->arguments [2]));
	ASSERT_NE (nullptr, number);
    ASSERT_EQ (U"32", type->bits);
    ASSERT_EQ (U"42", number->number_m);
}

TEST (llvmc_parser, recursive)
{
    test_parser parser ("let test1 function [] [[test2]] [] let test2 function [] [[test1]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element3 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element3);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element3->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_EQ (1, expression1->arguments.size ());
    ASSERT_EQ (1, expression1->predicate_position);
	auto set2 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [1]));
	ASSERT_NE (nullptr, set2);
	ASSERT_EQ (1, set2->nodes.size ());
	auto element4 (dynamic_cast <mu::llvmc::ast::element *> (set2->nodes [0]));
	ASSERT_NE (nullptr, element4);
    auto function2 (dynamic_cast <mu::llvmc::ast::function *> (element4->node_m));
    ASSERT_NE (nullptr, function2);
    EXPECT_EQ (0, function2->parameters.size ());
    EXPECT_EQ (0, function2->results.size ());
    ASSERT_EQ (1, function2->roots.size ());
    auto expression2 (dynamic_cast <mu::llvmc::ast::expression *> (function2->roots [0]));
    ASSERT_EQ (1, expression2->arguments.size ());
    auto element1 (dynamic_cast <mu::llvmc::ast::element *> (expression1->arguments [0]));
    ASSERT_NE (nullptr, element1);
    ASSERT_EQ (function2, element1->node_m);
    auto element2 (dynamic_cast <mu::llvmc::ast::element *> (expression2->arguments [0]));
    ASSERT_NE (nullptr, element2);
    ASSERT_EQ (function1, element2->node_m);
}

TEST (llvmc_parser, unresolved)
{
    test_parser parser ("let test1 function [] [[test2]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::unresolved_symbols, module1.error->type ());
    ASSERT_EQ (mu::core::region (24, 1, 25, 28, 1, 29), module1.error->region ());
}

TEST (llvmc_parser, two_functions)
{
    test_parser parser ("let test1 function [] [] [] let test2 function [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    EXPECT_EQ (0, function1->parameters.size ());
    EXPECT_EQ (0, function1->results.size ());
	auto set2 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [1]));
	ASSERT_NE (nullptr, set2);
	ASSERT_EQ (1, set2->nodes.size ());
	auto element2 (dynamic_cast <mu::llvmc::ast::element *> (set2->nodes [0]));
	ASSERT_NE (nullptr, element2);
    auto function2 (dynamic_cast <mu::llvmc::ast::function *> (element2->node_m));
    ASSERT_NE (nullptr, function2);
    EXPECT_EQ (0, function2->parameters.size ());
    EXPECT_EQ (0, function2->results.size ());
}

TEST (llvmc_parser, int_type42)
{
    test_parser parser ("let test1 function [int42 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_NE (nullptr, parameter1);
    ASSERT_EQ (mu::core::region (20, 1, 21, 28, 1, 29), parameter1->region);
    auto type1 (dynamic_cast <mu::llvmc::ast::integer_type *> (parameter1->type));
    ASSERT_NE (nullptr, type1);
    EXPECT_EQ (U"42", type1->bits);
}

TEST (llvmc_parser, join_empty)
{
    test_parser parser ("let test1 function [] [join []] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto join1 (dynamic_cast <mu::llvmc::ast::join *> (function1->roots [0]));
    ASSERT_NE (nullptr, join1);
    ASSERT_EQ (0, join1->branches.size ());
}

TEST (llvmc_parser, join_single)
{
    test_parser parser ("let test1 function [] [join [[]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto join1 (dynamic_cast <mu::llvmc::ast::join *> (function1->roots [0]));
    ASSERT_NE (nullptr, join1);
    ASSERT_EQ (1, join1->branches.size ());
    auto & branch1 (join1->branches [0]);
    ASSERT_EQ (0, branch1.arguments.size ());
    ASSERT_EQ (0, branch1.predicates.size ());
}

TEST (llvmc_parser, join_item)
{
    test_parser parser ("let test1 function [int32 i] [join [[i]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto join1 (dynamic_cast <mu::llvmc::ast::join *> (function1->roots [0]));
    ASSERT_NE (nullptr, join1);
    ASSERT_EQ (1, join1->branches.size ());
    auto & branch1 (join1->branches [0]);
    ASSERT_EQ (1, branch1.arguments.size ());
    ASSERT_EQ (0, branch1.predicates.size ());
    ASSERT_EQ (function1->parameters [0], branch1.arguments [0]);
}

TEST (llvmc_parser, join_predicate)
{
    test_parser parser ("let test1 function [int32 i] [join [[; i]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto join1 (dynamic_cast <mu::llvmc::ast::join *> (function1->roots [0]));
    ASSERT_NE (nullptr, join1);
    ASSERT_EQ (1, join1->branches.size ());
    auto & branch1 (join1->branches [0]);
    ASSERT_EQ (0, branch1.arguments.size ());
    ASSERT_EQ (1, branch1.predicates.size ());
    ASSERT_EQ (function1->parameters [0], branch1.predicates [0]);
}

TEST (llvmc_parser, join_2branches)
{
    test_parser parser ("let test1 function [int32 i] [join [[][]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    ASSERT_EQ (1, function1->roots.size ());
    auto join1 (dynamic_cast <mu::llvmc::ast::join *> (function1->roots [0]));
    ASSERT_NE (nullptr, join1);
    ASSERT_EQ (2, join1->branches.size ());
    auto & branch1 (join1->branches [0]);
    ASSERT_EQ (0, branch1.arguments.size ());
    ASSERT_EQ (0, branch1.predicates.size ());
    auto & branch2 (join1->branches [1]);
    ASSERT_EQ (0, branch2.arguments.size ());
    ASSERT_EQ (0, branch2.predicates.size ());
}

TEST (llvmc_parser, join_no_left_square_error)
{
    test_parser parser ("let test1 function [int32 i] [join i] []");
    auto module1 (parser.parser.parse ());
    ASSERT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::region (35, 1, 36, 35, 1, 36), module1.error->region ());
}

TEST (llvmc_parser, join_branch_error)
{
    test_parser parser ("let test1 function [int32 i] [join [i]] []");
    auto module1 (parser.parser.parse ());
    ASSERT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::region (36, 1, 37, 36, 1, 37), module1.error->region ());
}

TEST (llvmc_parser, ptr_int_type42)
{
    test_parser parser ("let test1 function [ptr int42 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (mu::core::region (20, 1, 21, 32, 1, 33), parameter1->region);
    ASSERT_NE (nullptr, parameter1);
    auto type1 (dynamic_cast <mu::llvmc::ast::pointer_type *> (parameter1->type));
    ASSERT_EQ (mu::core::region (20, 1, 21, 28, 1, 29), type1->region);
    ASSERT_NE (nullptr, type1);
    auto type2 (dynamic_cast <mu::llvmc::ast::integer_type *> (type1->pointed_type));
    ASSERT_NE (nullptr, type2);
    EXPECT_EQ (U"42", type2->bits);
}

TEST (llvmc_parser, ptr_reference)
{
    test_parser parser ("let i8 int8 let test1 function [ptr i8 val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [1]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (mu::core::region (32, 1, 33, 41, 1, 42), parameter1->region);
    ASSERT_NE (nullptr, parameter1);
    auto type1 (dynamic_cast <mu::llvmc::ast::pointer_type *> (parameter1->type));
    ASSERT_EQ (mu::core::region (32, 1, 33, 37, 1, 38), type1->region);
    ASSERT_NE (nullptr, type1);
    auto element2 (dynamic_cast <mu::llvmc::ast::element *> (type1->pointed_type));
    ASSERT_NE (nullptr, element2);
    auto type2 (dynamic_cast <mu::llvmc::ast::integer_type *> (element2->node_m));
    ASSERT_NE (nullptr, type2);
    EXPECT_EQ (U"8", type2->bits);
}

TEST (llvmc_parser, result_no_type_error)
{
    test_parser parser ("let test function [int1 i] [] [[");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    EXPECT_EQ (mu::core::error_type::expecting_right_square, module1.error->type ());
    ASSERT_EQ (mu::core::region (32, 1, 33, 32, 1, 33), module1.error->region ());
    EXPECT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, result_no_close_error)
{
    test_parser parser ("let test function [int1 i] [] [[int1 i]");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    EXPECT_EQ (mu::core::error_type::expecting_identifier_or_right_square, module1.error->type ());
    ASSERT_EQ (mu::core::region (39, 1, 40, 39, 1, 40), module1.error->region ());
    EXPECT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, results1)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    ASSERT_EQ (mu::core::region (35, 1, 36, 42, 1, 43), result1->region);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_empty_predicate)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val;]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_one_predicate)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val; val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results1_expression_predicate)
{
    test_parser parser ("let test1 function [int1 val] [] [[; [val]]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (0, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::expression *> (result1));
    ASSERT_NE (nullptr, value1);
}

TEST (llvmc_parser, results1_multi_predicate)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val; val val val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (4, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (4, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
}

TEST (llvmc_parser, results2)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val] [int1 val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (2, function1->results.size ());
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    EXPECT_EQ (parameter1, value1->value);
    ASSERT_EQ (2, function1->branch_ends [1]);
    ASSERT_EQ (2, function1->predicate_offsets [1]);
    auto result2 (function1->results [1]);
    auto value2 (dynamic_cast <mu::llvmc::ast::result *> (result2));
    ASSERT_NE (nullptr, value2);
    EXPECT_EQ (parameter1, value2->value);
}

TEST (llvmc_parser, results2_predicates)
{
    test_parser parser ("let test1 function [int1 val] [] [[int1 val; val] [int1 val; val]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_EQ (4, function1->results.size ());
    ASSERT_EQ (2, function1->branch_ends.size ());
    ASSERT_EQ (2, function1->predicate_offsets.size ());
    ASSERT_EQ (2, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
    ASSERT_EQ (value1->value, function1->results [1]);
    EXPECT_EQ (parameter1, value1->value);
    ASSERT_EQ (4, function1->branch_ends [1]);
    ASSERT_EQ (3, function1->predicate_offsets [1]);
    auto result2 (function1->results [2]);
    auto value2 (dynamic_cast <mu::llvmc::ast::result *> (result2));
    ASSERT_NE (nullptr, value2);
    ASSERT_EQ (value2->value, function1->results [3]);
    EXPECT_EQ (parameter1, value2->value);
}

TEST (llvmc_parser, results_resolved_predicates)
{
    test_parser parser ("let test1 function [] [] [[int1 test2]] let test2 function [] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (2, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element2 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element2);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element2->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    ASSERT_NE (nullptr, value1);
	auto set2 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [1]));
	ASSERT_NE (nullptr, set2);
	ASSERT_EQ (1, set2->nodes.size ());
	auto element3 (dynamic_cast <mu::llvmc::ast::element *> (set2->nodes [0]));
	ASSERT_NE (nullptr, element3);
    auto function2 (dynamic_cast <mu::llvmc::ast::function *> (element3->node_m));
    ASSERT_NE (nullptr, function2);
    auto element1 (dynamic_cast <mu::llvmc::ast::element *> (value1->value));
    ASSERT_NE (nullptr, element1);
    ASSERT_EQ (function2, element1->node_m);
}

TEST (llvmc_parser, body1)
{
    test_parser parser ("let test1 function [int1 val] [[]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    EXPECT_EQ (0, root1->arguments.size ());
    ASSERT_EQ (0, root1->predicate_position);
}

TEST (llvmc_parser, body2)
{
    test_parser parser ("let test1 function [int1 val] [[val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    ASSERT_EQ (1, root1->predicate_position);
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, root1->predicate_position);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
}

TEST (llvmc_parser, body3)
{
    test_parser parser ("let test1 function [int1 val] [[val] [val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (2, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    ASSERT_EQ (1, root1->predicate_position);
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    auto root2 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [1]));
    ASSERT_NE (nullptr, root2);
    ASSERT_EQ (1, root2->arguments.size ());
    ASSERT_EQ (1, root2->predicate_position);
    auto argument2 (root2->arguments [0]);
    EXPECT_EQ (parameter1, argument2);
}

TEST (llvmc_parser, body4)
{
    test_parser parser ("let test1 function [int1 val] [[val;val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (2, root1->arguments.size ());
    ASSERT_EQ (1, root1->predicate_position);
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, root1->predicate_position);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
}

TEST (llvmc_parser, body_not_expression_fail)
{
    test_parser parser ("let test1 function [int1 val] [");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::region (31, 1, 32, 31, 1, 32), module1.error->region ());
}

TEST (llvmc_parser, expression_already_parsing_predicates_error)
{
    test_parser parser ("let test1 function [int1 val] [[val;;val]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::already_parsing_predicates, module1.error->type());
}

TEST (llvmc_parser, set1)
{
    test_parser parser ("let test1 function [int1 val] [set val1 [val]] [[int1 val1]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    ASSERT_EQ (1, root1->arguments.size ());
    ASSERT_EQ (1, root1->predicate_position);
    auto argument1 (root1->arguments [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    ASSERT_EQ (1, function1->predicate_offsets.size ());
    ASSERT_EQ (1, function1->predicate_offsets [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    EXPECT_EQ (root1, value1->value);
}

TEST (llvmc_parser, loop1)
{
    test_parser parser ("let test1 function [] [loop [] [] [] []] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    EXPECT_EQ (0, root1->arguments.size ());
    EXPECT_EQ (0, root1->parameters.size ());
    EXPECT_EQ (0, root1->roots.size ());
    EXPECT_EQ (0, root1->results.size ());
}

TEST (llvmc_parser, loop2)
{
    test_parser parser ("let test1 function [int1 val] [loop [val; val] [val1] [[val1]] [[val val1]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (function1->parameters [0]);
    ASSERT_EQ (1, function1->roots.size ());
    auto loop1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, loop1);
    ASSERT_EQ (2, loop1->arguments.size ());
    ASSERT_EQ (1, loop1->argument_predicate_offset);
    EXPECT_EQ (parameter1, loop1->arguments [0]);
    ASSERT_EQ (1, loop1->parameters.size ());
    auto parameter2 (loop1->parameters [0]);
    ASSERT_EQ (1, loop1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (loop1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
    EXPECT_EQ (parameter2, expression1->arguments [0]);
    ASSERT_EQ (2, loop1->results.size ());
    ASSERT_EQ (1, loop1->predicate_offsets.size ());
    ASSERT_EQ (1, loop1->branch_ends.size ());
    ASSERT_EQ (2, loop1->predicate_offsets [0]);
    ASSERT_EQ (2, loop1->branch_ends [0]);
    ASSERT_EQ (parameter1, loop1->results [0]);
    ASSERT_EQ (parameter2, loop1->results [1]);
}

TEST (llvmc_parser, loop3)
{
    test_parser parser ("let test1 function [int1 val] [loop [] [] [] [[;][;]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto root1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, root1);
    EXPECT_EQ (0, root1->arguments.size ());
    EXPECT_EQ (0, root1->parameters.size ());
    EXPECT_EQ (0, root1->roots.size ());
    EXPECT_EQ (0, root1->results.size ());
}

TEST (llvmc_parser, loop_result_expression)
{
    test_parser parser ("let test1 function [int1 val] [loop [val] [val1] [] [[[val1]]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (function1->parameters [0]);
    ASSERT_EQ (1, function1->roots.size ());
    auto loop1 (dynamic_cast <mu::llvmc::ast::loop *> (function1->roots [0]));
    ASSERT_NE (nullptr, loop1);
    ASSERT_EQ (1, loop1->arguments.size ());
    ASSERT_EQ (1, loop1->argument_predicate_offset);
    EXPECT_EQ (parameter1, loop1->arguments [0]);
    ASSERT_EQ (1, loop1->parameters.size ());
    auto parameter2 (loop1->parameters [0]);
    ASSERT_EQ (0, loop1->roots.size ());
    ASSERT_EQ (1, loop1->results.size ());
    ASSERT_EQ (1, loop1->predicate_offsets.size ());
    ASSERT_EQ (1, loop1->branch_ends.size ());
    ASSERT_EQ (1, loop1->predicate_offsets [0]);
    ASSERT_EQ (1, loop1->branch_ends [0]);
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (loop1->results [0]));
	ASSERT_NE (nullptr, expression1);
}

TEST (llvmc_parser, let1)
{
    test_parser parser ("let test1 function [int1 val] [let val1 [val]] [[int1 val1]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
	auto set2 (dynamic_cast <mu::llvmc::ast::set *> (function1->roots [0]));
	ASSERT_NE (nullptr, set2);
	ASSERT_EQ (1, set2->nodes.size ());
	auto element3 (dynamic_cast <mu::llvmc::ast::element *> (set2->nodes [0]));
	ASSERT_NE (nullptr, element3);
	auto expression2 (dynamic_cast <mu::llvmc::ast::expression *> (element3->node_m));
	ASSERT_NE (nullptr, expression2);
	ASSERT_EQ (1, expression2->arguments.size ());
    auto argument1 (expression2->arguments [0]);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    EXPECT_EQ (parameter1, argument1);
    ASSERT_EQ (1, function1->results.size ());
    ASSERT_EQ (1, function1->branch_ends.size ());
    ASSERT_EQ (1, function1->branch_ends [0]);
    auto result1 (function1->results [0]);
    auto value1 (dynamic_cast <mu::llvmc::ast::result *> (result1));
    auto element2 (dynamic_cast <mu::llvmc::ast::element *> (value1->value));
    ASSERT_NE (nullptr, element2);
    ASSERT_EQ (element3->node_m, element2->node_m);
    ASSERT_EQ (0, element2->index);
    ASSERT_EQ (1, element2->total);
}

TEST (llvmc_parser, asm1)
{
    test_parser parser ("let test1 function [] [asm int1 text constraints] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto asm_l (dynamic_cast <mu::llvmc::ast::asm_c *> (function1->roots [0]));
    ASSERT_EQ (mu::core::region (23, 1, 24, 47, 1, 48), asm_l->region);
    ASSERT_NE (nullptr, asm_l);
    ASSERT_EQ (mu::string (U"text"), asm_l->text);
    ASSERT_EQ (mu::string (U"constraints"), asm_l->constraints);
}

TEST (llvmc_parser, asm_type_error)
{
    test_parser parser ("let test1 function [] [asm] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::expecting_ast_or_reference, module1.error->type ());
    ASSERT_EQ (mu::core::region (26, 1, 27, 26, 1, 27), module1.error->region ());
}

TEST (llvmc_parser, asm_text_error)
{
    test_parser parser ("let test1 function [] [asm int1] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::asm_hook_expecting_identifier, module1.error->type ());
    ASSERT_EQ (mu::core::region (31, 1, 32, 31, 1, 32), module1.error->region ());
}

TEST (llvmc_parser, asm_constraint_error)
{
    test_parser parser ("let test1 function [] [asm int1 text] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
    ASSERT_EQ (mu::core::error_type::asm_hook_expecting_constraints, module1.error->type ());
    ASSERT_EQ (mu::core::region (36, 1, 37, 36, 1, 37), module1.error->region ());
}

TEST (llvmc_parser, array_type)
{
    test_parser parser ("let test1 function [array int8 #4 p0] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_NE (nullptr, parameter1);
    auto array_type1 (dynamic_cast <mu::llvmc::ast::array_type *> (parameter1->type));
    ASSERT_NE (nullptr, array_type1);
    auto integer_type1 (dynamic_cast <mu::llvmc::ast::integer_type *> (array_type1->element_type));
    ASSERT_NE (nullptr, integer_type1);
    ASSERT_EQ (U"8", integer_type1->bits);
    auto number1 (dynamic_cast <mu::llvmc::ast::number *> (array_type1->size));
    ASSERT_NE (nullptr, number1);
    ASSERT_EQ (U"4", number1->number_m);
}

TEST (llvmc_parser, constant_array)
{
    test_parser parser ("let test1 function [] [[carray int8 [[cint int8 #h08] [cint int8 #h09] [cint int8 #h0a] [cint int8 #h0b]]]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
    auto constant1 (dynamic_cast <mu::llvmc::ast::constant_array *> (expression1->arguments [0]));
    ASSERT_NE (nullptr, constant1);
    auto integer_type1 (dynamic_cast <mu::llvmc::ast::integer_type *> (constant1->type));
    ASSERT_NE (nullptr, integer_type1);
    ASSERT_EQ (U"8", integer_type1->bits);
    ASSERT_EQ (4, constant1->initializer.size ());
	auto expression2 (dynamic_cast <mu::llvmc::ast::expression *> (constant1->initializer [0]));
	ASSERT_NE (nullptr, expression2);
	ASSERT_EQ (3, expression2->arguments.size ());
    auto constant2 (dynamic_cast <mu::llvmc::ast::constant_int *> (expression2->arguments [0]));
    ASSERT_NE (nullptr, constant2);
	auto type (dynamic_cast <mu::llvmc::ast::integer_type *> (expression2->arguments [1]));
	ASSERT_NE (nullptr, type);
	auto number (dynamic_cast <mu::llvmc::ast::number *> (expression2->arguments [2]));
	ASSERT_NE (nullptr, number);
    ASSERT_EQ (integer_type1->bits, type->bits);
    ASSERT_EQ (U"h08", number->number_m);
}

TEST (llvmc_parser, constant_string)
{
    test_parser parser ("let test1 function [] [[utf32 thing]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
	auto value1 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [0]));
	ASSERT_NE (nullptr, value1);
	auto array1 (dynamic_cast <mu::llvmc::skeleton::constant_array *> (value1->node_m));
	ASSERT_NE (nullptr, array1);
	ASSERT_EQ (5, array1->initializer.size ());
	auto type1 (dynamic_cast <mu::llvmc::skeleton::array_type *> (array1->type ()));
	ASSERT_NE (nullptr, type1);
	auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type1->element));
	ASSERT_NE (nullptr, type2);
	ASSERT_EQ (5, type1->size);
	ASSERT_EQ (32, type2->bits);
	ASSERT_EQ (*type2, *array1->initializer [0]->type ());
	auto value2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (array1->initializer [0]));
	ASSERT_NE (nullptr, value2);
	ASSERT_EQ (uint64_t ('t'), value2->value_m);
}

TEST (llvmc_parser, constant_string_keyword)
{
    test_parser parser ("let test1 function [] [[utf32 utf32]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
	auto value1 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [0]));
	ASSERT_NE (nullptr, value1);
	auto array1 (dynamic_cast <mu::llvmc::skeleton::constant_array *> (value1->node_m));
	ASSERT_NE (nullptr, array1);
	ASSERT_EQ (5, array1->initializer.size ());
	auto type1 (dynamic_cast <mu::llvmc::skeleton::array_type *> (array1->type ()));
	ASSERT_NE (nullptr, type1);
	auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type1->element));
	ASSERT_NE (nullptr, type2);
	ASSERT_EQ (5, type1->size);
	ASSERT_EQ (32, type2->bits);
	ASSERT_EQ (*type2, *array1->initializer [0]->type ());
	auto value2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (array1->initializer [0]));
	ASSERT_NE (nullptr, value2);
	ASSERT_EQ (uint64_t ('u'), value2->value_m);
}

TEST (llvmc_parser, constant_ascii)
{
    test_parser parser ("let test1 function [] [[ascii string]] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->roots.size ());
    auto expression1 (dynamic_cast <mu::llvmc::ast::expression *> (function1->roots [0]));
    ASSERT_NE (nullptr, expression1);
    ASSERT_EQ (1, expression1->arguments.size ());
	auto value1 (dynamic_cast <mu::llvmc::ast::value *> (expression1->arguments [0]));
	ASSERT_NE (nullptr, value1);
	auto array1 (dynamic_cast <mu::llvmc::skeleton::constant_array *> (value1->node_m));
	ASSERT_NE (nullptr, array1);
	ASSERT_EQ (6, array1->initializer.size ());
	auto type1 (dynamic_cast <mu::llvmc::skeleton::array_type *> (array1->type ()));
	ASSERT_NE (nullptr, type1);
	auto type2 (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type1->element));
	ASSERT_NE (nullptr, type2);
	ASSERT_EQ (6, type1->size);
	ASSERT_EQ (8, type2->bits);
	ASSERT_EQ (*type2, *array1->initializer [0]->type ());
	auto value2 (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (array1->initializer [0]));
	ASSERT_NE (nullptr, value2);
	ASSERT_EQ (uint64_t ('s'), value2->value_m);
}

TEST (llvmc_parser, unit_type)
{
    test_parser parser ("let test1 function [unit val] [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (1, function1->parameters.size ());
    ASSERT_EQ (0, function1->results.size ());
    auto parameter1 (dynamic_cast <mu::llvmc::ast::parameter *> (function1->parameters [0]));
    ASSERT_NE (nullptr, parameter1);
    ASSERT_EQ (mu::core::region (20, 1, 21, 27, 1, 28), parameter1->region);
    auto value1 (dynamic_cast <mu::llvmc::ast::value *> (parameter1->type));
    ASSERT_NE (nullptr, value1);
	auto unit (dynamic_cast <mu::llvmc::skeleton::unit_type *> (value1->node_m));
	ASSERT_NE (nullptr, unit);
}

TEST (llvmc_parser, unit_result)
{
    test_parser parser ("let test1 function [] [] [[unit unit_v]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (1, function1->results.size ());
	auto result1 (dynamic_cast <mu::llvmc::ast::result *> (function1->results [0]));
	ASSERT_NE (nullptr, result1);
	auto value1 (dynamic_cast <mu::llvmc::ast::value *> (result1->written_type));
	ASSERT_NE (nullptr, value1);
	auto unit (dynamic_cast <mu::llvmc::skeleton::unit_type *> (value1->node_m));
	ASSERT_NE (nullptr, unit);
}

TEST (llvmc_parser, global_variable)
{
    test_parser parser ("let test1 global [cint int64 #42]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto global1 (dynamic_cast <mu::llvmc::ast::global_variable *> (element1->node_m));
    ASSERT_NE (nullptr, global1);
	auto expression (dynamic_cast <mu::llvmc::ast::expression *> (global1->initializer));
	ASSERT_NE (nullptr, expression);
	ASSERT_EQ (3, expression->arguments.size ());
    auto initializer1 (dynamic_cast <mu::llvmc::ast::constant_int *> (expression->arguments [0]));
    ASSERT_NE (nullptr, initializer1);
	auto type (dynamic_cast <mu::llvmc::ast::integer_type *> (expression->arguments [1]));
	ASSERT_NE (nullptr, type);
    auto number1 (dynamic_cast <mu::llvmc::ast::number *> (expression->arguments [2]));
    ASSERT_NE (nullptr, number1);
    ASSERT_EQ (U"64", type->bits);
    ASSERT_EQ (U"42", number1->number_m);
}

TEST (llvmc_parser, constant_pointer_null)
{
    test_parser parser ("let test1 null int8");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto constant1 (dynamic_cast <mu::llvmc::ast::constant_pointer_null *> (element1->node_m));
    ASSERT_NE (nullptr, constant1);
    auto type1 (dynamic_cast <mu::llvmc::ast::integer_type *> (constant1->type));
    ASSERT_NE (nullptr, type1);
    ASSERT_EQ (U"8", type1->bits);
}

TEST (llvmc_parser, undefined)
{
    test_parser parser ("let test1 function [] [] [[int8 undefined int8]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (1, function1->results.size ());
	auto result1 (dynamic_cast <mu::llvmc::ast::result *> (function1->results [0]));
	ASSERT_NE (nullptr, result1);
	auto type1 (dynamic_cast <mu::llvmc::ast::integer_type *> (result1->written_type));
	ASSERT_NE (nullptr, type1);
    auto undefined1 (dynamic_cast <mu::llvmc::ast::undefined *> (result1->value));
    ASSERT_NE (nullptr, undefined1);
    auto type2 (dynamic_cast <mu::llvmc::ast::integer_type *> (undefined1->type));
    ASSERT_NE (nullptr, type2);
}

TEST (llvmc_parser, struct_type)
{
    test_parser parser ("let test1 function [] [] [[struct [name1 int8] undefined struct [name1 int8]]]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto function1 (dynamic_cast <mu::llvmc::ast::function *> (element1->node_m));
    ASSERT_NE (nullptr, function1);
    ASSERT_EQ (0, function1->parameters.size ());
    ASSERT_EQ (1, function1->results.size ());
	auto result1 (dynamic_cast <mu::llvmc::ast::result *> (function1->results [0]));
	ASSERT_NE (nullptr, result1);
	auto type1 (dynamic_cast <mu::llvmc::ast::struct_type *> (result1->written_type));
	ASSERT_NE (nullptr, type1);
	ASSERT_EQ (1, type1->names.size ());
	ASSERT_NE (type1->names.end (), type1->names.find (U"name1"));
    auto undefined1 (dynamic_cast <mu::llvmc::ast::undefined *> (result1->value));
    ASSERT_NE (nullptr, undefined1);
    auto type2 (dynamic_cast <mu::llvmc::ast::struct_type *> (undefined1->type));
    ASSERT_NE (nullptr, type2);
}

TEST (llvmc_parser, struct_type_duplicate_name_fail)
{
    test_parser parser ("let test1 function [] [] [[struct [name1 int8 name1 int8]]]");
    auto module1 (parser.parser.parse ());
    ASSERT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
	ASSERT_EQ (mu::core::error_type::unable_to_use_identifier, module1.error->type ());
}

TEST (llvmc_parser, local_covering_parameter_error)
{
    test_parser parser ("let test1 function [int64 a] [let a int32] []");
    auto module1 (parser.parser.parse ());
    EXPECT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, template_t)
{
    test_parser parser ("let test1 template [] []");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
	auto template1 (dynamic_cast <mu::llvmc::ast::template_c *> (element1->node_m));
	ASSERT_NE (nullptr, template1);
    ASSERT_EQ (nullptr, template1->template_m);
	ASSERT_EQ (0, template1->parameters.size ());
	ASSERT_EQ (0, template1->body.size ());
}

TEST (llvmc_parser, template_parameter)
{
    test_parser parser ("let test1 template [thing] [thing]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
	auto template1 (dynamic_cast <mu::llvmc::ast::template_c *> (element1->node_m));
	ASSERT_NE (nullptr, template1);
	ASSERT_EQ (1, template1->parameters.size ());
	ASSERT_EQ (1, template1->body.size ());
    auto parameter1 (template1->parameters [0]);
    ASSERT_NE (nullptr, parameter1->template_m);
    ASSERT_EQ (nullptr, parameter1->template_m->parent);
	ASSERT_EQ (parameter1, template1->body [0]);
}

TEST (llvmc_parser, template_reference_error)
{
    test_parser parser ("let test1 template [thing] [let test2 function [] [] [[]]] let test3 function [] [let result [test2]][[;result]]");
    auto module1 (parser.parser.parse ());
    ASSERT_NE (nullptr, module1.error);
    ASSERT_EQ (nullptr, module1.node);
}

TEST (llvmc_parser, entrypoint)
{
    test_parser parser ("let test1 entrypoint function [] [] []");
    auto module1 (parser.parser.parse ());
    ASSERT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto set1 (dynamic_cast <mu::llvmc::ast::set *> (module2->globals [0]));
	ASSERT_NE (nullptr, set1);
	ASSERT_EQ (1, set1->nodes.size ());
	auto element1 (dynamic_cast <mu::llvmc::ast::element *> (set1->nodes [0]));
	ASSERT_NE (nullptr, element1);
    auto entry1 (dynamic_cast <mu::llvmc::ast::entry *> (element1->node_m));
    ASSERT_NE (nullptr, entry1);
}

TEST (llvmc_template_context, even_clone)
{
	mu::llvmc::template_context root ({nullptr});
	auto should (root.should_clone (&root));
	ASSERT_TRUE (should);
}

TEST (llvmc_template_context, above_clone)
{
	mu::llvmc::template_context root ({nullptr});
	mu::llvmc::template_context context1 ({&root});
	auto should (root.should_clone (&context1));
	ASSERT_TRUE (should);
}

TEST (llvmc_template_context, dont_clone)
{
	mu::llvmc::template_context root ({nullptr});
	auto should (root.should_clone (nullptr));
	ASSERT_FALSE (should);
}

TEST (llvmc_parser, namespace_hook)
{
    test_parser parser ("` #container member");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
    auto namespace_l (dynamic_cast <mu::llvmc::ast::namespace_c *> (module2->globals [0]));
    ASSERT_NE (nullptr, namespace_l);
    ASSERT_EQ (U"member", namespace_l->member);
    auto number (dynamic_cast <mu::llvmc::ast::number *> (namespace_l->node_m));
    ASSERT_NE (nullptr, number);
}

TEST (llvmc_parser, namespace_template)
{
    test_parser parser ("template [] [` #container member]");
    auto module1 (parser.parser.parse ());
    EXPECT_EQ (nullptr, module1.error);
    ASSERT_NE (nullptr, module1.node);
    auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
    ASSERT_NE (nullptr, module2);
    ASSERT_EQ (1, module2->globals.size ());
	auto template1 (dynamic_cast <mu::llvmc::ast::template_c *> (module2->globals [0]));
	ASSERT_NE (nullptr, template1);
	ASSERT_EQ (1, template1->body.size ());
    auto namespace_l (dynamic_cast <mu::llvmc::ast::namespace_c *> (template1->body [0]));
    ASSERT_NE (nullptr, namespace_l);
	ASSERT_NE (nullptr, namespace_l->template_m);
    ASSERT_EQ (U"member", namespace_l->member);
    auto number (dynamic_cast <mu::llvmc::ast::number *> (namespace_l->node_m));
    ASSERT_NE (nullptr, number);
}

TEST (llvmc_parser, nested_module)
{
    test_parser parser ("module []");
    auto module1 (parser.parser.parse ());
	ASSERT_EQ (nullptr, module1.error);
	ASSERT_NE (nullptr, module1.node);
	auto module2 (dynamic_cast <mu::llvmc::ast::module *> (module1.node));
	ASSERT_NE (nullptr, module2);
	ASSERT_EQ (1, module2->globals.size ());
	auto module3 (dynamic_cast <mu::llvmc::ast::module *> (module2->globals [0]));
	ASSERT_NE (nullptr, module3);
	ASSERT_NE (module2, module3);
}