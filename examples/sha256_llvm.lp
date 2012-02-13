[fun-t
	[{[i32]]
	[{[i32]]
;; not]
[xor
	value
	[sext
		[int-c # d1 # d1]
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
	[shl value [sub [int-c # d32 # d32] count]]
	[:~; value count]
]

[fun-t
	[{[int32]]
	[{[int32]]
;; sigma1]
[xor
	[xor
		[call rotr x [int-c # d32 # d2]]
		[call rotr x [int-c # d32 # d13]]
	]
	[call rotr x [int-c # d32 # d22]
	[:~; x]
]

[fun-t
	[{[int32]]
	[{[int32]]
;; sigma2]
[xor
	[xor
		[call rotr x [int-c # d32 # d6]]
		[call rotr x [int-c # d32 # d11]]
	]
	[call rotr x [int-c # d32 # d25]]
]

[fun-t
	[{[int32]]
	[{[int32]]
;; sigma3]
[

]

[fun-t
	[{[int32]]
	[{[int32]]
;; sigma4]
[

]