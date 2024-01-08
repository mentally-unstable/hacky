## Hacky
just a lil' Hack assembly assembler from the Elements of Computer Systems book

it's not the exact way they wanted it implemented, but they also intended for it to be done in an OOP language like Java

work in progress (:

## SYNOPSIS
Since i'm writing this, I may as well explain a little what you'd be looking
at if you followed the link. In 'src/' reside all the modules of the assembler.
This is a Hack (made up assembly language) to binary assembler (compiler but
simpler). the core 3 modules are the parser (parser.c), encoder (code.c), and
the symbol table (table.c). But first, the assembler module is essentially the
main loop, it pulls the strings and defines the two stages of the assembler, more
on that later. The parser takes a structure, part of our current state as the
assembler, and it decides what the values are in that structure. the encoder is
responsible for giving the writer module (the thing that writes to the output file)
the binary values of the parsed structure. the table module keeps track of symbols
like labels (to jump to in the program) and constants, and the addresses of those
symbol (whether program address for labels or RAM for constants).

With the core modules out of the way, the info module just implements a tiny function
which allows me to enable or disable debug printing, i think it's cool and a quality
of life improvement. The args module just does the command line argument parsing, and
defines the global args structure. the util(ities) module just defines some small
string parsing and printing methods. Notably that's where I clean comments out of the
code. 'def.h' defines definitions that most of the files need, like the enums or
labels that determine how the assembler and encoder treat parsed values.

essentially what i've done is break lines like

```
@10
D=M+1 // set D to i+1 (i is at address 10)
@LABEL
0;JMP
```

into structures like

```
{ACMD, 10}
{CCMD, 'D', "M+1", null}
{LCMD, <addr of 'LABEL'>}
{CCMD, 0, null, JMP}
```

note: ACMD or a-commands load values into the A(ddress) register in the CPU. the CCMD
or c-commands are computations (they do math and determine when to jump), and LCMDs
are just label declarations. def.h defines another enum, VARR, and this is done because
the update_state() function in parser.c can't access the symbol table, so we declare a
variable reference/declaration (this is a misnomer, it's a constant; should fix that).
Because of this, update_state just marks it as a constant and the assembler module adds
it to the symbol table.

these are then pretty easy to write to a file, because the enums there make for easy
control-flow, and the encoder can translate those strings into binary. It can also write
them as hex which is implemented because the ROM in Logisim only takes Hex.

the update_state() function in parser.c doesn't handle everything, and the table is
updated in the assembler/main module, and that's annoying imo; bad practice: too much
being handled in one function.

the two stages of the assembler are as follows:
stage one, `user_symbols` fills the symbol table with label declarations (places to jump
to later in the program). the second stage does all the actual parsing and stuff, and if
it finds a label that it doesn't find in the symbol table it assumes it's a new constant
being declared, and adds the value to the table (while also replacing the constant's name
with it's declared value).

