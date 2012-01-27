[
	.id result
	[llvm/execution_engine/run_function
		engine
		function
		[llvm/execution_engine/generic_value/create_int
			# d32
			# h12345678
		; a]
		a
	; result]
	[llvm/execution_engine/create_jit
		module
	; engine]
	[llvm_io/synthesize
		.llvm
			[
				[:~; 1]
				trunc
					1
					[integer # d16]
			]
		module
		[llvm/integer_type/create context # d32 ; t]
		t
	; function]
	[llvm/module/create 
		[llvm/context/create; context]
		context
	; module]
]