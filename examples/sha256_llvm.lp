[~ [i32][i32][i32]]
[~ [i32]]
[xor
	[and x y]
	[and
		[call bits/not x]
		z
	]
	[:~ ; x y z]
;; ch]

[~ [i32][i32][i32]]
[~ [i32]]
[xor
	[xor
		[and x y]
		[and x z]
	]
	[and y z]
	[:~ ; x y z]
;; maj]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x #i 32 d2]
		[call bits/rotr x #i 32 d13]
	]
	[call bits/rotr x #i 32 d22]
	[:~; x]
;; sigma1]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x #i 32 d6]
		[call bits/rotr x #i 32 d11]
	]
	[call bits/rotr x #i 32 d25]
	[:~; x]
;; sigma2]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x #i 32 d7]
		[call bits/rotr x #i 32 d18]
	]
	[lshr x #i 32 d3]
	[:~; x]
;; sigma3]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x #i 32 d17]
		[call bits/rotr x #i 32 d19]
	]
	[lshr x #i 32 d10]
	[:~; x]
;; sigma4]

[~ [ptr [i32]]]
[~ ]
[~
	[store
		#i 32 h6a09e667
		[call
			index
			destination
			#i 64 d0
		]
	]
	[store
		#i 32 hbb67ae85
		[call
			index
			destination
			#i 64 d1
		]
	]
	[store
		#i 32 h3c6ef372
		[call
			index
			destination
			#i 64 d2
		]
	]
	[store
		#i 32 ha54ff53a
		[call
			index
			destination
			#i 64 d3
		]
	]
	[store
		#i 32 h510e527f
		[call
			index
			destination
			#i 64 d4
		]
	]
	[store
		#i 32 h9b05688c
		[call
			index
			destination
			#i 64 d5
		]
	]
	[store
		#i 32 h1f83d9ab
		[call
			index
			destination
			#i 64 d6
		]
	]
	[store
		#i 32 h5be0cd19
		[call
			index
			destination
			#i 64 d7
		]
	]
	[:~; destination]
;; initialize_hash]

[~ [ptr [i32]] [i64]]
[~ [ptr [i32]]]
[inttoptr
	[add
		[ptrtoint
			value
			[i64]
		]
		[mul
			#i 64 d4
			position
		]
	]
	[ptr [i32]]
	[:~; value position]
;; index]

[~ ]
[~ ]
[call
	exit
	#i 32 d0
;; ex]

[~ ]
[~ ]
[call
	exit
	#i 32 d0
	[call
		wprintf
		` |%|Hello world!%
		:-[null [ptr [i16]]]
	]
;; entry]