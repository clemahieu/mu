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
		[call bits/rotr x [#i 32 d2]]
		[call bits/rotr x [#i 32 d13]]
	]
	[call bits/rotr x [#i 32 d22]]
	[:~; x]
;; sigma1]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x [#i 32 d6]]
		[call bits/rotr x [#i 32 d11]]
	]
	[call bits/rotr x [#i 32 d25]]
	[:~; x]
;; sigma2]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x [#i 32 d7]]
		[call bits/rotr x [#i 32 d18]]
	]
	[lshr x [#i 32 d3]]
	[:~; x]
;; sigma3]

[~ [i32]]
[~ [i32]]
[xor
	[xor
		[call bits/rotr x [#i 32 d17]]
		[call bits/rotr x [#i 32 d19]]
	]
	[lshr x [#i 32 d10]]
	[:~; x]
;; sigma4]

[~ ]
[~ ]
[call
	wprintf [` |%|Hello world!%]
;; _start]