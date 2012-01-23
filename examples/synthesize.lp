[
	.id function
	[llvm_io/synthesize
		=>
			[:~]
		module
		[llvm/integer_type/create context # d32]
	; function]
	[llvm/module/create 
		[llvm/context/create; context]
		context
	; module]
]