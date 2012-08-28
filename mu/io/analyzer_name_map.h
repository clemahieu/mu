#pragma once

#include <mu/core/types.h>
#include <mu/io/analyzer_resolver.h>

namespace mu
{
    namespace core
    {
        class expression;
        class node;
        class node_list;
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
                void insert_cluster_scope (mu::core::errors::error_target & errors_a, mu::string const &name, mu::core::node * const node, mu::io::context const & context_a);
                void insert_routine_scope (mu::core::errors::error_target & errors_a, mu::string const &name, mu::core::node * const node, mu::io::context const & context_a);
                void free_locals ();
                void fill_reference (mu::string name, mu::io::context const & context_a, mu::core::node_list & target_a);
                bool finalize (mu::core::errors::error_target & errors_a);
            private:
                void resolve (mu::core::errors::error_target & errors_a, mu::string const & name, mu::core::node * const node, bool global, mu::io::context const & context_a);
                std::vector <bool *> local_references;
                std::set <mu::string> used_names;
                std::set <mu::string> locals;
                mu::map <mu::string, mu::core::node *> mapping;
                mu::multimap <mu::string, mu::io::analyzer::resolver> unresolved;
            };
        }
    }
}