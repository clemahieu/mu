#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/ast.hpp>

#include <boost/function.hpp>

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
        class keyword : public mu::llvmc::ast::node
        {
        public:
            virtual mu::llvmc::node_result parse (mu::io::stream <mu::io::token *> & stream_a) = 0;
            virtual bool dominator () = 0;
        };
        class mapping
        {
        public:
            // Returns the keyword covering `identifier_a' if one exists
            mu::llvmc::keyword * get_keyword (mu::string const & identifier_a);
            // Perform `action_a' on the node mapped to `identifier_a', if it's not mapped, store `action_a' and perform when resolved
            void refer (mu::string const & identifier_a, boost::function <void (mu::llvmc::ast::node *)> action_a);
            // Create mapping of `identifier_a' to `node_a', if actions for this identifier have been stored, perform them.
            // Return if mapping already existed.
            bool map (mu::string const & identifier_a, mu::llvmc::ast::node * node_a);
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved;
        };
        class parser
        {
        public:
            parser (mu::io::stream <mu::io::token *> & stream_a);
            node_result parse ();
        private:
            mu::io::stream <mu::io::token *> & stream;
            mu::llvmc::mapping mapping;
        };
    }
}