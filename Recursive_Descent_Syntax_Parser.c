
// Isha Koregave (R11743130) | Homework #4 | 11/10/2022
// This program is a recursive descent syntax parser that can validate the syntax of a source code file(written in DanC) provided by the user.


#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>



#ifndef FRONT_H
#define FRONT_H

/* Token codes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESSER_OP 27
#define GREATER_OP 28
#define MOD_OP 29

#define EQUAL_OP 30
#define NEQUAL_OP 31
#define LEQUAL_OP 32
#define GEQUAL_OP 33
#define SEMICOLON 34

#define LEFT_CBRACE 35

#define RIGHT_CBRACE 36
#define KEY_READ 37

#define KEY_PRINT 38
#define KEY_WHILE 39
#define KEY_DO 40

int lex();
;

#endif

/* Global Variable */
int nextToken;
char String;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();
void expr(char *array[]);
void term(char *array[]);
int statement(char *array[]);
void factor(char *array[]);
void comparision(char *array[]);
static void error();
int paren_count = 0;
int lexed = 0;

#ifdef WIN32
#include <io.h>

#define access _access
#endif
/******************************************************/
/* main driver */
int main(int argc, char *argv[]) {
  char *array[100];
/* Token codes inserted into array*/
  array[0] = "LETTER";
  array[1] = "DIGIT";
  array[99] = "UNKNOWN";
  array[10] = "INT_LIT";
  array[11] = "IDENT ";
  array[20] = "ASSIGN_OP";
  array[21] = "ADD_OP ";
  array[22] = "SUB_OP ";
  array[23] = "MULT_OP";
  array[24] = " DIV_OP ";
  array[25] = " LEFT_PAREN ";
  array[26] = "RIGHT_PAREN";
  array[27] = " LESSER_OP ";
  array[28] = "GREATER_OP";
  array[29] = "MOD_OP ";
  array[30] = "EQUAL_OP ";
  array[31] = "NEQUAL_OP ";
  array[32] = "LEQUAL_OP ";
  array[33] = "GEQUAL_OP ";
  array[34] = "SEMICOLON ";
  array[35] = "LEFT_CBRACE ";
  array[36] = "RIGHT_CBRACE";
  array[37] = "KEY_READ ";
  array[38] = "KEY_PRINT";
  array[39] = "KEY_WHILE";
  array[40] = "KEY_DO";

  int error;
  /* Open the input data file and process its contents */
  printf("DanC Analyzer :: R11743130\n");

  //If the user did not provide a file as input:

  if (argc == 1){//if no arguments are supplied argc will be 1
  printf("ERROR - Input file not provided. \n");

  return 2;
  }

  //If the user did provide a file as input but the file does not exist:

  else if ((in_fp = fopen(argv[1], "r")) == NULL) {
    printf("ERROR - Input file does not exist. \n");
    return 3;
  }

  else {
    getChar();
    do {
      lex();
      error = statement(array);

    } while (nextToken != EOF && error != 1); //if error code is 1 the parser will print the first encountered error
    if (error == 0) {
      printf("Syntax Validated");
    }
    return error;
  }

}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses (everything in
 * unknown)and return the token */
static int lookup(char ch) {
  switch (ch) {

  case '=':
    addChar();
    nextToken = ASSIGN_OP;
    // printf(" %s     ASSIGN_OP\n", lexeme);
    break;

  case '<':
    addChar();
    nextToken = LESSER_OP;

    // printf(" %s     LESSER_OP\n", lexeme);

    break;

  case '>':
    addChar();
    nextToken = GREATER_OP;
    // printf(" %s     GREATER\n", lexeme);

    break;

  case ';':
    addChar();
    nextToken = SEMICOLON;
    //printf(" %s     SEMICOLON\n", lexeme);
    break;

  case '(':
    addChar();
    nextToken = LEFT_PAREN;
    //printf(" %s     LEFT_PAREN\n", lexeme);
    break;

  case '{':
    addChar();
    nextToken = LEFT_CBRACE;
    //printf(" %s     LEFT_CBRACE\n", lexeme);
    break;

  case '}':
    addChar();
    nextToken = RIGHT_CBRACE;
    //printf(" %s     RIGHT_CBRACE\n", lexeme);
    break;

  case '+':
    addChar();
    nextToken = ADD_OP;
    //printf(" %s     ADD_OP\n", lexeme);
    break;
  case '-':
    addChar();
    nextToken = SUB_OP;
    //printf(" %s     SUB_OP\n", lexeme);
    break;
  case '*':
    addChar();
    nextToken = MULT_OP;
    //printf(" %s     MULT_OP\n", lexeme);
    break;
  case '/':
    addChar();
    nextToken = DIV_OP;
    //printf(" %s     DIV_OP\n", lexeme);
    break;
  case '%':
    addChar();
    nextToken = MOD_OP;
    //printf(" %s     MOD_OP\n", lexeme);
    break;
  case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    //printf(" %s     RIGHT_PAREN\n", lexeme);
    break;

  default:
    addChar();

    nextToken = UNKNOWN;
    //printf(" %s     UNKNON\n", lexeme);

    break;
  }
  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  } else {
    printf("Error - lexeme is too long \n");
  }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
static void getChar() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))

      charClass = LETTER;
    else if (isdigit(nextChar))
      charClass = DIGIT;
    else
      charClass = UNKNOWN;
  } else {
    charClass = EOF;
  }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
  lexLen = 0;
  getNonBlank();

  switch (charClass) {
  /* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = IDENT;

    // key words
    if (strcmp(lexeme, "read") == 0) {
      nextToken = KEY_READ;
      printf(" %s  KEY_READ\n", lexeme);

    }
    else if (strcmp(lexeme, "print") == 0) {
      nextToken = KEY_PRINT;
      printf(" %s KEY_PRINT\n", lexeme);

    }
    else if (strcmp(lexeme, "while") == 0) {
      nextToken = KEY_WHILE;
      printf(" %s KEY_WHILE\n", lexeme);
    }

    else if (strcmp(lexeme, "do") == 0) {
      nextToken = KEY_DO;
      printf(" %s    KEY_DO\n", lexeme);

    }
    else {
      printf(" %s     IDENT\n", lexeme);
    }
    break;

  /* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    printf(" %s     INT_LIT\n", lexeme);

    break;

  /* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    getChar();
    if ((lexeme[0] == '=') && (nextChar != '=')) {
      printf(" %s     ASSIGN_OP\n", lexeme);
    } else if ((lexeme[0] == '<') && (nextChar != '=' && nextChar != '>')) {
      printf(" %s     LESSER_OP\n", lexeme);
    } else if ((lexeme[0] == '>') && (nextChar != '=')) {
      printf(" %s     GREATER_OP\n", lexeme);
    }
    //used to add next character to lexeme if needed
    if ((lexeme[0] == '=') && (nextChar == '=')) {
      addChar();
      getChar();
    } else if ((lexeme[0] == '<') && (nextChar == '=' || nextChar == '>')) {
      addChar();
      getChar();
    } else if ((lexeme[0] == '>') && (nextChar == '=')) {
      addChar();
      getChar();
    }
    //used to print lexemes: "==",">=","<=","<>"
    if (strcmp(lexeme, "==") == 0) {
      nextToken = EQUAL_OP;
      //printf(" %s    EQUAL_OP\n", lexeme);
    } else if (strcmp(lexeme, "<=") == 0) {
      nextToken = LEQUAL_OP;
      //printf(" %s    LEQUAL_OP\n", lexeme);
    } else if (strcmp(lexeme, ">=") == 0) {
      nextToken = GEQUAL_OP;
      //printf(" %s    GEQUAL_OP\n", lexeme);
    } else if (strcmp(lexeme, "<>") == 0) {
      nextToken = NEQUAL_OP;
      //printf(" %s    NEQUAL_OP\n", lexeme);
    }


    break;

  /* EOF */
  case EOF:
    nextToken = EOF;
    // printf(" %s     EOF\n",lexeme);
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  } /* End of switch */


  return nextToken;
}
/* End of function lex */
int errorcode;//used to keep track of enocuntered error

/* statement
 * Parses strings in the language generated by the rule:
 * S ::= V=E | read(V) | print(V) | do { S } while C | S;S
 */
int statement(char *array[]) {

  printf("Enter <statement>\n");
  if (nextToken == IDENT) {

    lex();
    if (nextToken == ASSIGN_OP) {

      lex();
      expr(array);

      //if semicolon is encountered at the end of the statement check for another statement (according to  syntax)
      if (nextToken == SEMICOLON) {
        lex();
        statement(array);

      }
    } else {
      printf("Error encounter: The next lexeme was %c and next token was "
             "array[nextToken]",
             nextChar);

    }
  }

  else if (nextToken == KEY_READ) {

    lex();
    if (nextToken == LEFT_PAREN) {
      lex();
      if (nextToken == IDENT) {
        lex();
        if (nextToken == RIGHT_PAREN) {
          lex();
          errorcode = 0;
          //if semicolon is encountered at the end of the statement check for another statement (according to  syntax)
          if (nextToken == SEMICOLON) {
            lex();
            statement(array);

          }
        } else {


          printf("Error encounter: The next lexeme was %c and next token was "
                 "array[nextToken]",
                 nextChar);
          errorcode = 1;
        }
      } else {

        printf("Error encounter: The next lexeme was %c and next token was "
               "array[nextToken]",
               nextChar);
        errorcode = 1;

      }
    } else {



    }
  }

  else if (nextToken == KEY_PRINT) {

    lex();
    if (nextToken == LEFT_PAREN) {
      lex();
      if (nextToken == IDENT) {
        lex();
        if (nextToken == RIGHT_PAREN) {
          lex();
          errorcode = 0;
          //if semicolon is encountered at the end of the statement check for another statement (according to  syntax)
          if (nextToken == SEMICOLON) {
            lex();

            statement(array);

          } else {
          }
        } else {

          printf("error in print\n");

        }
      } else {

        printf("error in print\n");

      }
    } else {

      printf("error in print\n");

    }
  }

  else if (nextToken == KEY_DO) {

    lex();
    if (nextToken == LEFT_CBRACE) {
      lex();
      statement(array);
      //if semicolon is encountered at the end of the statement check for another statement (according to  syntax)

      if (nextToken == SEMICOLON) {
        lex();

        statement(array);


      }
      if (paren_count != 1 && nextToken == RIGHT_CBRACE) {
        lex();
        if (nextToken == KEY_WHILE) {
          lex();
          comparision(array);
          //error code set to one in comparision function when there is a comp op after second expr
          if (errorcode != 1) {

            if (nextToken == SEMICOLON) {
              lex();
              statement(array);

            }

            else if (nextToken != EOF &&
                     nextToken != RIGHT_CBRACE && nextToken != KEY_WHILE) {
              errorcode = 1;
              printf(
                  "Error encounter: The next lexeme was %s and next token was "
                  "%s\n",
                  lexeme, array[nextToken]);
            }
          }
        } else {
          error();
          printf(
              "Error encounter: The next lexeme was %s and next token was %s\n",
              lexeme, array[nextToken]);

        }
      } else {
        error();
        errorcode = 1;
        printf(
            "Error encounter: The next lexeme was %s and next token was %s\n",
            lexeme, array[nextToken]);

      }

    } else {
      error();


    }

  } else if (errorcode == 0 && nextToken == EOF) {

    printf("Syntax Validated\n");
  }

  else {

    printf("Error encounter: The next lexeme was %s and next token was %s\n",
           lexeme, array[nextToken]);

    errorcode = 1;

  }
  return errorcode;
}

/* comparision
 * Parses strings in the language generated by the rule:
 * <comparision> -> <expr> {(< | >|==|<>|<=| >=) <expr>}
 */

void comparision(char *array[]) {
  printf("Enter <comp>\n");

  expr(array);
  if (lexed != 1) {
    lex();
  }

  while (nextToken == LESSER_OP || nextToken == GREATER_OP ||
         nextToken == EQUAL_OP || nextToken == NEQUAL_OP ||
         nextToken == LEQUAL_OP || nextToken == GEQUAL_OP) {

    lex();

    expr(array);
    //invalid syntax if comparision operator even after second expression
    if (nextToken == LESSER_OP || nextToken == GREATER_OP ||
         nextToken == EQUAL_OP || nextToken == NEQUAL_OP ||
         nextToken == LEQUAL_OP || nextToken == GEQUAL_OP) {
      printf("Error encounter: The next lexeme was  and next token was %s \n",
             array[nextToken]);
      errorcode = 1;
      lex();


      errorcode = 1;
    }
  }

  printf("Exit <comp>\n");
}

//end of comparision

/* expr
 * Parses strings in the language generated by the rule:
 * <expr> -> <term> {(+ | -) <term>}
 */
void expr(char *array[]) {
  printf("Enter <expr>\n");

  /* Parse the first term */
  term(array);

  /* As long as the next token is + or -, get
  the next token and parse the next term */
  while (nextToken == ADD_OP || nextToken == SUB_OP) {
    lex();
    term(array);
  }

  printf("Exit <expr>\n");
} /* End of function expr */


/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
void term(char *array[]) {
  printf("Enter <term>\n");
  /* Parse the first factor */
  factor(array);
  /* As long as the next token is * or /, get the
  next token and parse the next factor */
  while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
    lex();
    factor(array);
  }


  printf("Exit <term>\n");
} /* End of function term */


/* factor
 * Parses strings in the language generated by the rule:
 * <factor> -> id | int_constant | ( <expr )
 * */

void factor(char *array[]) {

  printf("Enter <factor>\n");
  /* Determine which RHS */
  if (nextToken == IDENT || nextToken == INT_LIT) {

    lex();

    lexed = 1;

  } else if (nextToken == UNKNOWN) {
    lex();
    errorcode = 1;
    printf("Error encountered in factor for unknown token the next lexeme is "
           "%s \n",
           lexeme);

  }

  else {

    /* If the RHS is (<expr>), call lex to pass over the
    left parenthesis, call expr, and check for the right
    parenthesis */
    if (nextToken == LEFT_PAREN) {
      paren_count = paren_count + 1;
      lex();
      expr(array);

      if (nextToken == RIGHT_PAREN) {
        paren_count = paren_count - 1;
        lex();

      } else {
        error();
        errorcode = 1;
      }
    } /* End of if (nextToken == ... */
    /* It was not an id, an integer literal, or a left parenthesis */
    else {

      error();
      errorcode = 1;
      printf("Error encountered the next lexeme is %s \n", lexeme);
    }
  } /* End of else */
  printf("Exit <factor>\n");

} /* End of function factor */

static void error() {
  //printf("Error (more is desired, but not implemented).\n");
}
