# Compiler

Rules and methods.

## Grammar Analyze

Grammar:

```
CompUnit → {Decl} {FuncDef} MainFuncDecl

Decl → ConstDecl | VarDecl

ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'

BType → 'int'

ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal

ConstInitVal → ConstExp
              | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'

VarDecl → BType VarDef { ',' VarDef } ';'

VarDef → Ident { '[' ConstExp ']' }
        | Ident { '[' ConstExp ']' } '=' InitVal

InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'

FuncDef → FuncType Ident '(' [FuncFParams] ')' Block

MainFuncDef → 'int' 'main' '(' ')' Block

FuncFParams → FuncFParam { ',' FuncFParam }

FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]

Block → '{' { BlockItem } '}'

BlockItem → Decl | Stmt

Stmt → LVal '=' Exp ';'
     | [Exp] ';'
     | Block
     | 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
     | 'while' '(' Cond ')' Stmt
     | 'break' ';' | 'continue' ';'
     | 'return' [Exp] ';'
     | LVal '=' 'getint''('')'';'
     | 'printf''('FormatString{','Exp}')'';'
     
Exp → AddExp

Cond → LOrExp

LVal → Ident {'[' Exp ']'}

PrimaryExp → '(' Exp ')' | LVal | Number 

Number → IntConst

UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' 
          | UnaryOp UnaryExp 
          
UnaryOp → '+' | '−' | '!' 

FuncRParams → Exp { ',' Exp }

MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp 

AddExp → MulExp | AddExp ('+' | '−') MulExp 

RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp 

EqExp → RelExp | EqExp ('==' | '!=') RelExp 

LAndExp → EqExp | LAndExp '&&' EqExp 

LOrExp → LAndExp | LOrExp '||' LAndExp 

ConstExp → AddExp 
```

Identifier:

```
identifier → identifier-nondigit
            | identifier identifier-nondigit
            | identifier digit
```

Const:

```
integer-const → decimal-const | 0
decimal-const → nonzero-digit | decimal-const digit
```

## Lexical Analyze

Valid Token Symbols:

|  Word Name   |  Category |
|:------------:|:----:|
|    Ident     |   IDENFR |
|   IntConst   |   INTCON |
| FormatString |   STRCON |
|     main     |   MAINTK |
|    const     |  CONSTTK |
|     int      |   INTTK |
|    break     |  BREAKTK |
|   continue   | CONTINUETK |
|      if      |    IFTK |
|     else     |   ELSETK |
|    while     |  WHILETK |
|    getint    |  GETINTTK |
|    printf    |  PRINTFTK |
|    return    |  RETURNTK |
|     void     |   VOIDTK |
|      !       |    NOT |
|      &&      |    AND |
| &#124;&#124; |     OR     |
|      +       |    PLUS |
|      -       |    MINU |
|      *       |    MULT |
|      /       |    DIV |
|      %       |    MOD |
|      <       |    LSS |
|      <=      |    LEQ |
|      >       |    GRE |
|      >=      |    GEQ |
|      ==      |    EQL |
|      !=      |    NEQ |
|      =       |   ASSIGN |
|      ;       |   SEMICN |
|      ,       |   COMMA |
|      (       |  LPARENT |
|      )       |  RPARENT |
|      [       |   LBRACK |
|      ]       |   RBRACK |
|      {       |   LBRACE |
|      }       |   RBRACE |

Secondary Symbols:

| Word Name | Category |
|:---------:|:--------:|
|           |  BEGIN   |
|    //     |   SLC    |
|    /*     |   LMLC   |
|    */     |   RMLC   |
|          |   END    |

## Syntactic Analyze

Change the left recursion.

```
MulExp -> UnaryExp { ('*' | '/' | '%') UnaryExp }

AddExp -> MulExp { ('+' | '-') MulExp )

RelExp -> AddExp { ('<' | '>' | '<=' | '>=') AddExp )

EqExp -> RelExp { ('==' | '!=') RelExp }

LAndExp -> EqExp { '&&' EqExp }

LOrExp -> LAndExp { '||' LAndExp }
```

Back Tracking

```
Stmt -> LVal '=' Exp ';' | LVal '=' 'getint' '(' ')' ';' 
```

