```
████████╗ ██████╗ ██████╗  ██████╗ 
╚══██╔══╝██╔═══██╗██╔══██╗██╔═══██╗
   ██║   ██║   ██║██║  ██║██║   ██║
   ██║   ██║   ██║██║  ██║██║   ██║
   ██║   ╚██████╔╝██████╔╝╚██████╔╝
   ╚═╝    ╚═════╝ ╚═════╝  ╚═════╝
```
- [x] Add pointers * and &
- [x] multi dimensional array
- [x] handle return statement and type check return statement
- [x] code gen for function blocks
- [x] address of local variables 
- [x] add 'AND' 'OR'
- [x] catch error if a function body does not contain a return statement (results in runtime errors), function code gen always add return instruction at end
- [x] allow pointer as function arguments
- [x] support for elif
- [x] currently generating code for function definition on first seeing definition
    - rather create a list of AST of function definition and generate code at the end
    - useful for code evalutaion without code generation
- [x] lex '\n' as a single character rather than '\' and 'n'
- [x] organize files an folders
- [x] a build folder for xsm, x86, and c backend output file
- [x] expl to c code gen
- [ ] a test system to autmatically run all test programs with valid input and check its output
- [ ] handle negative integers properly
- [ ] free all heap memory (symbol tables, AST)
- [ ] should array be treated as a pointer ?