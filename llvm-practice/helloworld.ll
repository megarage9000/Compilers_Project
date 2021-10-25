; Declare the string constant as a global constant. 
; run the following command to run this LLVM assembly program:
; sh run-llvm-code.sh helloworld.ll 
@LC0 = internal constant [13 x i8] c"hello world\0A\00"
; note how the newline character is inserted into the string

; External declaration of the puts function 
declare i32 @puts(i8*)

; Definition of main function
define i32 @main() {
  ; Convert [13 x i8]* to i8*
  ; this is because the function puts takes a char* which is an i8* in LLVM
  %cast = getelementptr [13 x i8], [13 x i8]* @LC0, i8 0, i8 0
  ; read up on getelementptr: http://llvm.org/docs/GetElementPtr.html

  ; Call puts function to write out the char* string to stdout. 
  call i32 @puts(i8* %cast)
  ret i32 0 
}

