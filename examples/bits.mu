[not
i32 value; i32
 [xor
  value
  [sext
   #i 1 d1
   [i32]
  ]
 ]
]

[rotr
i32 value i32 count; i32
 [or
  [lshr value count]
  [shl value [sub #i 32 d32 count]]
 ]
]