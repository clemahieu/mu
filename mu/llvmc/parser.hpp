#pragma once

namespace mu
{
    namespace core
    {
        class error;
    }
    namespace io
    {
        template <typename T>
        class stream;
        class token;
    }
    namespace llvmc
    {
        namespace ast
        {
            class module;
        }
        struct module_result
        {
            ~module_result ();
            mu::llvmc::ast::module * module;
            mu::core::error * error;
        };
        namespace ast
        {
            class module;
        }
        class parser
        {
        public:
            parser (mu::io::stream <mu::io::token *> & stream_a);
            module_result parse ();
        private:
            mu::io::stream <mu::io::token *> & stream;
        };
    }
}