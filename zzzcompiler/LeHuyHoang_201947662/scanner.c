/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void
skipBlank ()
{
  Token *token;
  if (currentChar == EOF)
    return ;
  switch (charCodes[currentChar]){
      case CHAR_SPACE:
        readChar();
        return ;
      default :
        return ;
  }
}

void
skipComment ()
{
  Token *token;
  if (currentChar == EOF){
      error (ERR_ENDOFCOMMENT, lineNo, colNo);
      return ;
  }
  switch (charCodes[currentChar]){
      case CHAR_TIMES:
        readChar();
        if (currentChar == EOF){
            error (ERR_ENDOFCOMMENT, lineNo, colNo);
            return ;
        }
        else {
            switch (charCodes[currentChar]){
                case CHAR_RPAR:
                    readChar();
                    return ;
            }
        }
      default :
        readChar();
        skipComment();
  }
}

Token *
readIdentKeyword (int count, char *word, int ln, int cn)
{
  Token *token;
  char a = currentChar;
  size_t len = strlen(word);
  char *word2 = malloc(len + 1 + 1);
  strcpy(word2, word);
  
  if (currentChar == EOF)
    return makeToken (TK_EOF, ln, cn);

  switch (charCodes[currentChar]){
      case CHAR_DIGIT:
        word2[len] = a;
        word2[len + 1] = '\0';
        
        readChar();
        count++;
        return readIdentKeyword(count,word2,ln,cn);
      case CHAR_LETTER:
        word2[len] = a;
        word2[len + 1] = '\0';
        
        readChar();
        count++;
        return readIdentKeyword(count,word2,ln,cn);
      default :
        if(count > MAX_IDENT_LEN) {
            token = makeToken (TK_NONE, ln, cn);
            error (ERR_INVALIDSYMBOL, ln, cn);
            readChar ();
            return token;
        }
        else{
            CharCode code = checkKeyword(word2);
            if (code == TK_NONE) {
                token = makeToken (TK_IDENT, ln, cn);
                strcpy(token->string,word2);
                return token;
            } else {
                token = makeToken (checkKeyword(word2), ln, cn);
                
                return token;
            }
        }
  }
}

Token *
readFloat (char *word, int ln, int cn)
{
  Token *token;
  char a = currentChar;
  size_t len = strlen(word);
  char *word2 = malloc(len + 1 + 1);
  strcpy(word2, word);

  if (currentChar == EOF)
    return makeToken (TK_EOF, ln, cn);

  switch (charCodes[currentChar]){
      case CHAR_DIGIT:
        word2[len] = a;
        word2[len + 1] = '\0';
        readChar();
        return readFloat(word2,ln,cn);
      default :
        token = makeToken (TK_FLOAT, ln, cn);
        strcpy(token->string,word2);
        return token;
  }
}

Token *
readNumber (char *word, int ln, int cn)
{
  Token *token;
  char a = currentChar;
  size_t len = strlen(word);
  char *word2 = malloc(len + 1 + 1);
  strcpy(word2, word);

  if (currentChar == EOF)
    return makeToken (TK_EOF, ln, cn);

  switch (charCodes[currentChar]){
      case CHAR_DIGIT:
        word2[len] = a;
        word2[len + 1] = '\0';
        readChar();
        return readNumber(word2,ln,cn);
      case CHAR_PERIOD:
        word2[len] = a;
        word2[len + 1] = '\0';
        readChar();
        return readFloat(word2,ln,cn);
      default :
        token = makeToken (TK_NUMBER, ln, cn);
        strcpy(token->string,word2);
        return token;
  }
}

Token *
readConstChar (char *word, int ln, int cn)
{
  Token *token;
  char a = currentChar;
  size_t len = strlen(word);
  char *word2 = malloc(len + 1 + 1);
  strcpy(word2, word);

  if (currentChar == EOF)
    return makeToken (TK_EOF, ln, cn);

  switch (charCodes[currentChar]){
      case CHAR_SINGLEQUOTE:
        token = makeToken (TK_CHAR, ln, cn);
        strcpy(token->string,word2);
        readChar ();
        return token;
      default :
        word2[len] = a;
        word2[len + 1] = '\0';
        readChar();
        return readConstChar(word2,ln,cn);
  }
}

Token *
getToken (void)
{
  Token *token;
  int ln, cn;
  char *word;
  

  if (currentChar == EOF)
    return makeToken (TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar])
    {
    case CHAR_SPACE:
      skipBlank ();
      return getToken ();
    case CHAR_LETTER:
      word = "";
      return readIdentKeyword (0,word,lineNo,colNo);
    case CHAR_DIGIT:
      word = "";
      return readNumber (word,lineNo,colNo);
    case CHAR_PLUS:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken(SB_ASSIGN_PLUS,ln,cn);
                readChar();
                return token;
            default:
                token = makeToken (SB_PLUS, ln, cn);
                return token;
        }
      } else return makeToken (SB_PLUS, ln, cn);
    case CHAR_MINUS:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken(SB_ASSIGN_SUBTRACT,ln,cn);
                readChar();
                return token;
            default:
                token = makeToken (SB_MINUS, ln, cn);
                return token;
        }
      } else return makeToken (SB_MINUS, ln, cn);
    case CHAR_TIMES:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken(SB_ASSIGN_TIMES,ln,cn);
                readChar();
                return token;
            default:
                token = makeToken (SB_TIMES, ln, cn);
                return token;
        }
      } else return makeToken (SB_TIMES, ln, cn);
    case CHAR_SLASH:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken(SB_ASSIGN_DIVIDE,ln,cn);
                readChar();
                return token;
            default:
                token = makeToken (SB_SLASH, ln, cn);
                return token;
        }
      } else return makeToken (SB_SLASH, ln, cn);
    case CHAR_EQ:
      token = makeToken (SB_EQ, lineNo, colNo);
      readChar ();
      return token;
    case CHAR_COMMA:
      token = makeToken (SB_COMMA, lineNo, colNo);
      readChar ();
      return token;
    case CHAR_SEMICOLON:
      token = makeToken (SB_SEMICOLON, lineNo, colNo);
      readChar ();
      return token;
    case CHAR_RPAR:
      token = makeToken (SB_RPAR, lineNo, colNo);
      readChar ();
      return token;
    case CHAR_LPAR:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_TIMES:
                skipComment ();
                return getToken ();
            default:
                token = makeToken (SB_LPAR, ln, cn);
                return token;
        }
      } else return makeToken (SB_LPAR, ln, cn);
    case CHAR_LBRACKET:
        token = makeToken (SB_LBRACKET, lineNo, colNo);
        readChar ();
        return token;
    case CHAR_RBRACKET:
        token = makeToken (SB_RBRACKET, lineNo, colNo);
        readChar ();
        return token;
    case CHAR_SINGLEQUOTE:
        word = "";
        readChar();
        return readConstChar(word,lineNo,colNo-1);
    case CHAR_LT:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken (SB_LE, ln, cn);
                readChar ();
                return token;
            default:
                token = makeToken (SB_LT, ln, cn);
                readChar ();
                return token;
        }
      } else return makeToken (SB_LT, ln, cn);
    case CHAR_GT:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken (SB_GE, ln, cn);
                readChar ();
                return token;
            default:
                token = makeToken (SB_GT, ln, cn);
                readChar ();
                return token;
        }
      } else return makeToken (SB_GT, ln, cn);
    case CHAR_EXCLAIMATION:
      ln = lineNo;
      cn = colNo;
      readChar ();
      if (currentChar != EOF){
        switch(charCodes[currentChar]){
            case CHAR_EQ:
                token = makeToken (SB_NEQ, ln, cn);
                readChar ();
                return token;
            default:
                token = makeToken (TK_NONE, lineNo, colNo);
                error (ERR_INVALIDSYMBOL, lineNo, colNo);
                readChar ();
                return token;
        }
      } else return makeToken (TK_NONE, lineNo, colNo);
    case CHAR_PERIOD:
        token = makeToken (SB_PERIOD, lineNo, colNo);
        readChar ();
        return token;
    case CHAR_COLON:
        ln = lineNo;
        cn = colNo;
        readChar();
        if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ)) {
            readChar();
            return makeToken(SB_ASSIGN, ln, cn);
        } else return makeToken(SB_COLON, ln,cn);
    case CHAR_PERCENT:
        token = makeToken (SB_MOD, lineNo, colNo);
        readChar ();
        return token;
    default:
      token = makeToken (TK_NONE, lineNo, colNo);
      error (ERR_INVALIDSYMBOL, lineNo, colNo);
      readChar ();
      return token;
    }
}


/******************************************************************/

void
printToken (Token * token)
{

  printf ("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType)
    {
    case TK_NONE:
      printf ("TK_NONE\n");
      break;
    case TK_IDENT:
      printf ("TK_IDENT(%s)\n", token->string);
      break;
    case TK_NUMBER:
      printf ("TK_NUMBER(%s)\n", token->string);
      break;
    case TK_FLOAT:
      printf ("TK_FLOAT(%s)\n", token->string);
      break;
    case TK_CHAR:
      printf ("TK_CHAR(\'%s\')\n", token->string);
      break;
    case TK_EOF:
      printf ("TK_EOF\n");
      break;

    case KW_PROGRAM:
      printf ("KW_PROGRAM\n");
      break;
    case KW_CONST:
      printf ("KW_CONST\n");
      break;
    case KW_TYPE:
      printf ("KW_TYPE\n");
      break;
    case KW_VAR:
      printf ("KW_VAR\n");
      break;
    case KW_INTEGER:
      printf ("KW_INTEGER\n");
      break;
    case KW_CHAR:
      printf ("KW_CHAR\n");
      break;
    case KW_ARRAY:
      printf ("KW_ARRAY\n");
      break;
    case KW_OF:
      printf ("KW_OF\n");
      break;
    case KW_FUNCTION:
      printf ("KW_FUNCTION\n");
      break;
    case KW_PROCEDURE:
      printf ("KW_PROCEDURE\n");
      break;
    case KW_BEGIN:
      printf ("KW_BEGIN\n");
      break;
    case KW_END:
      printf ("KW_END\n");
      break;
    case KW_CALL:
      printf ("KW_CALL\n");
      break;
    case KW_IF:
      printf ("KW_IF\n");
      break;
    case KW_THEN:
      printf ("KW_THEN\n");
      break;
    case KW_ELSE:
      printf ("KW_ELSE\n");
      break;
    case KW_WHILE:
      printf ("KW_WHILE\n");
      break;
    case KW_DO:
      printf ("KW_DO\n");
      break;
    case KW_FOR:
      printf ("KW_FOR\n");
      break;
    case KW_TO:
      printf ("KW_TO\n");
      break;
    case KW_FLOAT:
      printf ("KW_FLOAT\n");
      break;
    case SB_SEMICOLON:
      printf ("SB_SEMICOLON\n");
      break;
    case SB_COLON:
      printf ("SB_COLON\n");
      break;
    case SB_PERIOD:
      printf ("SB_PERIOD\n");
      break;
    case SB_COMMA:
      printf ("SB_COMMA\n");
      break;
    case SB_ASSIGN:
      printf ("SB_ASSIGN\n");
      break;
    case SB_ASSIGN_PLUS:
      printf ("SB_ASSIGN_PLUS\n");
      break;
    case SB_ASSIGN_SUBTRACT:
      printf ("SB_ASSIGN_SUBTRACT\n");
      break;
    case SB_ASSIGN_DIVIDE:
      printf ("SB_ASSIGN_DIVIDE\n");
      break;
    case SB_ASSIGN_TIMES:
      printf ("SB_ASSIGN_TIMES\n");
      break;
    case SB_MOD:
      printf ("SB_MOD\n");
      break;
    case SB_EQ:
      printf ("SB_EQ\n");
      break;
    case SB_NEQ:
      printf ("SB_NEQ\n");
      break;
    case SB_LT:
      printf ("SB_LT\n");
      break;
    case SB_LE:
      printf ("SB_LE\n");
      break;
    case SB_GT:
      printf ("SB_GT\n");
      break;
    case SB_GE:
      printf ("SB_GE\n");
      break;
    case SB_PLUS:
      printf ("SB_PLUS\n");
      break;
    case SB_MINUS:
      printf ("SB_MINUS\n");
      break;
    case SB_TIMES:
      printf ("SB_TIMES\n");
      break;
    case SB_SLASH:
      printf ("SB_SLASH\n");
      break;
    case SB_LPAR:
      printf ("SB_LPAR\n");
      break;
    case SB_RPAR:
      printf ("SB_RPAR\n");
      break;
    case SB_LBRACKET:
      printf ("SB_LBRACKET\n");
      break;
    case SB_RBRACKET:
      printf ("SB_RBRACKET\n");
      break;
    }
}

Token* getValidToken(void) {
  Token *token = getToken();
  while (token->tokenType == TK_NONE) {
    free(token);
    token = getToken();
  }
  return token;
}


/******************************************************************/


