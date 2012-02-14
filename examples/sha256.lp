[~
	[llvm/compile/operation
		[.() cluster]
		module2
		`a temp/sha256
	]
	[llvm/module/merge
		module2
		module
	]
	[llvm/module/assemble 
		context
		`a
			|!|
				define void @_start ()
				{
					ret void
				}
			!
	; module2]
	[llvm/synthesizer/operation
		[script/ast/read_from_file ` examples/sha256_llvm.lp]
		module
	; cluster]
	[llvm/module/create
		[llvm/context/create
		; context]
		context
	; module]
]