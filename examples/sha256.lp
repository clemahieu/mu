[~	
	[llvm/compile/operation
		[.() verify print]
		module
		`a temp/sha256
	]
	[script/print/operation
		[llvm/module/print
			module
		]		
	;; print]
	[llvm/module/verify
		[.() sha256]
		module
	;; verify]
	[add_abort
		context
		module
		synthesizer
	;; abort]
	[add_wprintf
		context
		module
		synthesizer
	;; wprintf]
	[add_exit
		context
		module
		synthesizer
	;; exit]
	[add_bits
		synthesizer
		module
	; bits]
	[llvm/synthesizer/create		
	; synthesizer]
	[llvm/synthesizer/merge
		synthesizer
		` bits/
		bits
	;; added_bits]
	[add_sha256
		[.() added_bits abort wprintf exit]
		synthesizer
		module
	; sha256]
	[llvm/module/create
		[llvm/context/create
		; context]
		context
	; module]
]

[.()
	add
	linkage
	name
	[llvm/global_value/set_linkage
		function
		llvm/linkage_types/external
	;; linkage]
	[llvm/function/create
		function_type
	; function]
	[llvm/value/set_name
		function
		[script/astring/truncate function_name]
	;; name]
	[llvm/synthesizer/add
		synthesizer
		function_name
		function
		[llvm/module/add_function
			module
			function
		]
	;; add]
	[:~; context module synthesizer function_name function_type]
;; add_function]

[add_function
	context
	module
	synthesizer
	` exit
	[llvm/function_type/create
		context
		[{ ]
		[{ ]
	]
	[:~; context module synthesizer]
;; add_exit]

[add_function
	context
	module
	synthesizer
	` abort
	[llvm/function_type/create
		context
		[{ ]
		[{ ]
	]
	[:~; context module synthesizer]
;; add_abort]

[add_function
	context
	module
	synthesizer
	` wprintf
	[llvm/function_type/create
		context
		[{ [llvm/pointer_type/create [llvm/integer_type/create context [llvm/apint/create # d16]]]]
		[{ ]
	]
	[:~; context module synthesizer]
;; add_wprintf]

[synthesizer
	[script/ast/read_from_file ` examples/bits.lp]
	module
	[:~
	; synthesizer module]
;; add_bits]

[~
	[.() ]
	cluster	
	[synthesizer
		[script/ast/read_from_file ` examples/sha256_llvm.lp]
		module
	; cluster]
	[llvm/cluster/get
		cluster
		` _start
	; start]
	[llvm/value/set_name
		start
		`a _start
	]
	[llvm/global_value/set_linkage
		start
		llvm/linkage_types/external
	]
	[:~
	; synthesizer module]
;; add_sha256]