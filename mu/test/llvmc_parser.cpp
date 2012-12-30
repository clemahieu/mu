#include <gtest/gtest.h>

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_muistream.hpp>

TEST (llvmc_parser, empty)
{
    mu::stringstream text (U":a");
    mu::io::stream_muistream stream (text, 16);
    mu::io::lexer lexer (stream);
    mu::io::stream_token stream_token (lexer, 2);
    mu::llvmc::parser parser (stream_token);
    auto module1 (parser.parse ());
    EXPECT_NE (nullptr, module1.error);
}