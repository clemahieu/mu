[~
	[llvm/module/print name
		module
	; text]
	[llvm/compile/operation name
		module
		`a temp/sha256
	]
	[llvm/value/set_name
		[llvm/cluster/get
			cluster
			` _start
		]
		`a _start
	;; name]
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