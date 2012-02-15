[~
	[llvm/module/print
		[.() name linkage]
		module
	; text]
	[llvm/compile/operation
		[.() name linkage]
		module
		`a temp/sha256
	]
	[llvm/global_value/set_linkage
		function
		llvm/linkage_types/external
	;; linkage]
	[llvm/value/set_name
		[llvm/cluster/get
			cluster
			` _start
		; function]
		function
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