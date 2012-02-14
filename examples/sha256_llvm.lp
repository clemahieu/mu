[fun-t
	[{[i32]]
	[{[i32]]
;; not]
[xor
	value
	[sext
		[#i 1 d1]
		[i32]
	]
	[:~; value]
]

[fun-t
	[{[i32][i32][i32]]
	[{[i32]]
;; ch]
[xor
	[and x y]
	[and
		[call not x]
		z
	]
	[:~ ; x y z]
]

[fun-t
	[{[i32][i32][i32]]
	[{[i32]]
;; maj]
[xor
	[xor
		[and x y]
		[and x z]
	]
	[and y z]
	[:~ ; x y z]
]

[fun-t
	[{[i32][i32]]
	[{[i32]]
;; rotr]
[or
	[lshr value count]
	[shl value [sub [#i 32 d32] count]]
	[:~; value count]
]

[fun-t
	[{[i32]]
	[{[i32]]
;; sigma1]
[xor
	[xor
		[call rotr x [#i 32 d2]]
		[call rotr x [#i 32 d13]]
	]
	[call rotr x [#i 32 d22]]
	[:~; x]
]

[fun-t
	[{[i32]]
	[{[i32]]
;; sigma2]
[xor
	[xor
		[call rotr x [#i 32 d6]]
		[call rotr x [#i 32 d11]]
	]
	[call rotr x [#i 32 d25]]
	[:~; x]
]

[fun-t
	[{[i32]]
	[{[i32]]
;; sigma3]
[xor
	[xor
		[call rotr x [#i 32 d7]]
		[call rotr x [#i 32 d18]]
	]
	[lshr x [#i 32 d3]]
	[:~; x]
]

[fun-t
	[{[i32]]
	[{[i32]]
;; sigma4]
[xor
	[xor
		[call rotr x [#i 32 d17]]
		[call rotr x [#i 32 d19]]
	]
	[lshr x [#i 32 d10]]
	[:~; x]
]