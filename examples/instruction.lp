[
	.id result
	[llvm/execution_engine/run_function
		engine
		function
		[llvm/execution_engine/generic_value/create_int
			# d32
			# h100
		; a]
		a a a a a a
	; result]
	[llvm/execution_engine/create_jit
		module
	; engine]
	[llvm_io/synthesize
		.llvm
			[
				[:~; 1 2 3 4 5 6]
				add
					[udiv
						[mul 1 2]
						[add 3 4]
					]
					[add 5 6]
			]
		module
		[llvm/integer_type/create context # d32 ; t]
		t t t t t t
	; function]
	[llvm/module/create 
		[llvm/context/create; context]
		context
	; module]
]