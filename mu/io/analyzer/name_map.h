#pragma once

#include <gc_allocator.h>

#include <mu/core/types.h>
#include <mu/io/analyzer/resolver.h>

#include <map>
#include <set>
#include <vector>

namespace mu
{
    namespace core
    {
        class expression;
        class node;
        namespace errors
        {
            class error_target;
        }
    }
    namespace io
    {
        namespace analyzer
        {
            class resolver;
            class name_map
            {
            public:
                void insert_global (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, mu::io::debugging::context const & context_a);
                void insert_local (mu::core::errors::error_target & errors_a, mu::string const &name, mu::core::node * const node, mu::io::debugging::context const & context_a);
                void free_locals ();
                void fill_reference (mu::string name, mu::io::debugging::context const & context_a, mu::core::expression & expression);
                void finalize (mu::core::errors::error_target & errors_a);
            private:
                void resolve (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, bool global, mu::io::debugging::context const & context_a);
                std::vector <bool *> local_references;
                std::set <mu::string> used_names;
                std::set <mu::string> locals;
                std::map <mu::string, mu::core::node *, std::less <mu::string>, gc_allocator <std::map <mu::string, mu::core::node *>>> mapping;
                std::multimap <mu::string, mu::io::analyzer::resolver, std::less <mu::string>, gc_allocator <mu::io::analyzer::resolver>> unresolved;
            };
        }
    }
}