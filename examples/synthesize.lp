[
	.id function result
	[llvm/execution_engine/run_function
		engine
		function
		[llvm/execution_engine/generic_value/create_int
			# d32
			# h3c3c3c3c
		]
	; result]
	[llvm/execution_engine/create_jit
		module
	; engine]
	[llvm_io/synthesize
		->
			[:~]
		module
		[llvm/integer_type/create context # d32]
	; function]
	[llvm/module/create 
		[llvm/context/create; context]
		context
	; module]
]