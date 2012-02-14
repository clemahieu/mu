[fun-t
	[{[i32]]
	[{[i32]]
]
[xor
	value
	[sext
		[#i 1 d1]
		[i32]
	]
	[:~; value]
;; not]

[fun-t
	[{[i32][i32][i32]]
	[{[i32]]
]
[xor
	[and x y]
	[and
		[call not x]
		z
	]
	[:~ ; x y z]
;; ch]

[fun-t
	[{[i32][i32][i32]]
	[{[i32]]
]
[xor
	[xor
		[and x y]
		[and x z]
	]
	[and y z]
	[:~ ; x y z]
;; maj]

[fun-t
	[{[i32][i32]]
	[{[i32]]
]
[or
	[lshr value count]
	[shl value [sub [#i 32 d32] count]]
	[:~; value count]
;; rotr]

[fun-t
	[{[i32]]
	[{[i32]]
]
[xor
	[xor
		[call rotr x [#i 32 d2]]
		[call rotr x [#i 32 d13]]
	]
	[call rotr x [#i 32 d22]]
	[:~; x]
;; sigma1]

[fun-t
	[{[i32]]
	[{[i32]]
]
[xor
	[xor
		[call rotr x [#i 32 d6]]
		[call rotr x [#i 32 d11]]
	]
	[call rotr x [#i 32 d25]]
	[:~; x]
;; sigma2]

[fun-t
	[{[i32]]
	[{[i32]]
]
[xor
	[xor
		[call rotr x [#i 32 d7]]
		[call rotr x [#i 32 d18]]
	]
	[lshr x [#i 32 d3]]
	[:~; x]
;; sigma3]

[fun-t
	[{[i32]]
	[{[i32]]
]
[xor
	[xor
		[call rotr x [#i 32 d17]]
		[call rotr x [#i 32 d19]]
	]
	[lshr x [#i 32 d10]]
	[:~; x]
;; sigma4]