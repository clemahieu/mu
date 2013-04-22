extern char const * const generate_empty_expected = R"%%%(
define void @0() {
  br label %1

; <label>:1                                       ; preds = %0
  unreachable
                                                  ; No predecessors!
  unreachable
}
)%%%";

extern char const * const generate_add_expected = R"%%%(
define i1 @0(i1) {
  br label %2

; <label>:2                                       ; preds = %1
  %3 = add i1 %0, %0
  ret i1 %3
                                                  ; No predecessors!
  unreachable
}
)%%%";

extern char const * const generate_two_return_expected = R"%%%(
%0 = type { i1, i1 }

define %0 @0(i1) {
  br label %2

; <label>:2                                       ; preds = %1
  %3 = insertvalue %0 undef, i1 %0, 0
  %4 = insertvalue %0 %3, i1 %0, 1
  ret %0 %4
                                                  ; No predecessors!
  unreachable
}
)%%%";

extern char const * const generate_if_expected = R"%%%(
define i8 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %4
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  ret i8 1

; <label>:4                                       ; preds = %1
  ret i8 0
}
)%%%";

extern char const * const generate_if_value_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %6
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  %4 = insertvalue %0 undef, i32 4, 1
  %5 = insertvalue %0 %4, i8 1, 2
  ret %0 %5

; <label>:6                                       ; preds = %1
  %7 = insertvalue %0 undef, i32 4, 0
  %8 = insertvalue %0 %7, i8 0, 2
  ret %0 %8
}
)%%%";

extern char const * const generate_if_join_expected = R"%%%(
define void @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %4
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  br label %5

; <label>:4                                       ; preds = %1
  br label %5

; <label>:5                                       ; preds = %3, %4
  ret void
}
)%%%";

extern char const * const generate_if_join_value_expected = R"%%%(
define i1 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %5
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  %4 = add i1 %0, %0
  br label %7

; <label>:5                                       ; preds = %1
  %6 = add i1 %0, %0
  br label %7

; <label>:7                                       ; preds = %3, %5
  %8 = phi i1 [ %4, %3 ], [ %6, %5 ]
  ret i1 %8
}
)%%%";

extern char const * const generate_if_join_2value_expected = R"%%%(
%0 = type { i1, i1 }

define %0 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %6
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  %4 = add i1 %0, %0
  %5 = add i1 %0, %0
  br label %9

; <label>:6                                       ; preds = %1
  %7 = add i1 %0, %0
  %8 = add i1 %0, %0
  br label %9

; <label>:9                                       ; preds = %3, %6
  %10 = phi i1 [ %4, %3 ], [ %7, %6 ]
  %11 = phi i1 [ %5, %3 ], [ %8, %6 ]
  %12 = insertvalue %0 undef, i1 %10, 0
  %13 = insertvalue %0 %12, i1 %11, 1
  ret %0 %13
}
)%%%";