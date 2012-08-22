#include <gtest/gtest.h>

#include <mu/llvm_/parser/parser.h>
#include <mu/core/errors/error_list.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/ctx.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/right_square.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <gc_cpp.h>

// Parser construction
TEST (llvm_parser, parser1)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
}

// Empty cluster
TEST (llvm_parser, parser2)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::stream_end, mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
    ASSERT_TRUE (clusters.size () == 1);
    auto cluster1 (clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 0);
}

// Invalid top symbol
TEST (llvm_parser, parser3)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    ASSERT_TRUE (errors ());
}

// Start of routine
TEST (llvm_parser, parser4)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
}

// Invalid routine name
TEST (llvm_parser, parser5)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    ASSERT_TRUE (errors ());
}

// Valid routine name
TEST (llvm_parser, parser6)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
}

// Invalid parameters
TEST (llvm_parser, parser7)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    ASSERT_TRUE (errors ());
}

// Omitted parameters
TEST (llvm_parser, parser8)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
}

// Empty parameters
TEST (llvm_parser, parser9)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
}

// Invalid body
TEST (llvm_parser, parser10)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    ASSERT_TRUE (errors ());
}

// Valid empty body
TEST (llvm_parser, parser11)
{
    mu::core::errors::error_list errors;
    llvm::LLVMContext llvm_ctx;
    mu::llvm_::context::node context (&llvm_ctx);
    mu::vector <mu::llvm_::ast::cluster *> clusters;
    mu::llvm_::parser::parser parser (&context, errors,
                                      [&clusters]
                                      (mu::llvm_::ast::cluster * cluster_a)
                                      {
                                          clusters.push_back (cluster_a);
                                      });
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::identifier (mu::string (U"t")), mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::divider, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::left_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    parser (new (GC) mu::io::tokens::right_square, mu::io::debugging::context ());
    ASSERT_TRUE (!errors ());
}