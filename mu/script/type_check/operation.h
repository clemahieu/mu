#pragma once

#include <mu/script/operation.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace type_check
        {
			bool check_count (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, size_t expected);
			void invalid_type (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::core::node> node_a, size_t position);
			template <typename type1_t=void, typename type2_t=void, typename type3_t=void, typename type4_t=void, typename type5_t=void>
			class check
			{		
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 5))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							if (boost::dynamic_pointer_cast <type2_t> (context_a.parameters [1]).get () != nullptr)
							{
								if (boost::dynamic_pointer_cast <type3_t> (context_a.parameters [2]).get () != nullptr)
								{
									if (boost::dynamic_pointer_cast <type4_t> (context_a.parameters [3]).get () != nullptr)
									{
										if (boost::dynamic_pointer_cast <type5_t> (context_a.parameters [4]).get () != nullptr)
										{
											target_a->perform (context_a);
										}
										else
										{
											invalid_type (context_a.errors, context_a.parameters [4], 4);
										}
									}
									else
									{
										invalid_type (context_a.errors, context_a.parameters [3], 3);
									}
								}
								else
								{
									invalid_type (context_a.errors, context_a.parameters [2], 2);
								}
							}
							else
							{
								invalid_type (context_a.errors, context_a.parameters [1], 1);
							}
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
			};
			template <typename type1_t, typename type2_t, typename type3_t, typename type4_t>
			class check <type1_t, type2_t, type3_t, type4_t, void>
			{		
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 4))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							if (boost::dynamic_pointer_cast <type2_t> (context_a.parameters [1]).get () != nullptr)
							{
								if (boost::dynamic_pointer_cast <type3_t> (context_a.parameters [2]).get () != nullptr)
								{
									if (boost::dynamic_pointer_cast <type4_t> (context_a.parameters [3]).get () != nullptr)
									{
										target_a->perform (context_a);
									}
									else
									{
										invalid_type (context_a.errors, context_a.parameters [3], 3);
									}
								}
								else
								{
									invalid_type (context_a.errors, context_a.parameters [2], 2);
								}
							}
							else
							{
								invalid_type (context_a.errors, context_a.parameters [1], 1);
							}
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
			};
			template <typename type1_t, typename type2_t, typename type3_t>
			class check <type1_t, type2_t, type3_t, void, void>
			{		
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 3))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							if (boost::dynamic_pointer_cast <type2_t> (context_a.parameters [1]).get () != nullptr)
							{
								if (boost::dynamic_pointer_cast <type3_t> (context_a.parameters [2]).get () != nullptr)
								{
									target_a->perform (context_a);
								}
								else
								{
									invalid_type (context_a.errors, context_a.parameters [2], 2);
								}
							}
							else
							{
								invalid_type (context_a.errors, context_a.parameters [1], 1);
							}
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
			};
			template <typename type1_t, typename type2_t>
			class check <type1_t, type2_t, void, void, void>
			{		
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 2))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							if (boost::dynamic_pointer_cast <type2_t> (context_a.parameters [1]).get () != nullptr)
							{
								target_a->perform (context_a);
							}
							else
							{
								invalid_type (context_a.errors, context_a.parameters [1], 1);
							}
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
			};
			template <typename type1_t>
			class check <type1_t, void, void, void, void>
			{
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 1))
					{
						if (boost::dynamic_pointer_cast <type1_t> (context_a.parameters [0]).get () != nullptr)
						{
							target_a->perform (context_a);
						}
						else
						{
							invalid_type (context_a.errors, context_a.parameters [0], 0);
						}
					}
				}
			};
			template <>
			class check <void, void, void, void, void>
			{
			public:
				void operator () (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> target_a)
				{
					if (check_count (context_a.errors, context_a.parameters, 0))
					{
						target_a->perform (context_a);
					}
				}
			};
			template <typename type1_t=void, typename type2_t=void, typename type3_t=void, typename type4_t=void, typename type5_t=void>
            class operation: public mu::script::operation
            {
			public:
                operation (boost::shared_ptr <mu::script::operation> target_a)
					: target (target_a)
				{
				}
                void perform (mu::script::context & context_a)
				{
					check <type1_t, type2_t> check_l;
					check_l (context_a, target);
				}
                boost::shared_ptr <mu::script::operation> target;
            };
        }
    }
}