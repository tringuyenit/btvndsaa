#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_ENDOFCOMMENT,
  ERR_IDENTTOOLONG,
  ERR_INVALIDCHARCONSTANT,
  ERR_INVALIDSYMBOL,
  ERR_INVALIDCONSTANT,
  ERR_INVALIDTYPE,
  ERR_INVALIDBASICTYPE,
  ERR_INVALIDPARAM,
  ERR_INVALIDSTATEMENT,
  ERR_INVALIDARGUMENTS,
  ERR_INVALIDCOMPARATOR,
  ERR_INVALIDEXPRESSION,
  ERR_INVALIDTERM,
  ERR_INVALIDFACTOR,
  ERR_INVALIDCONSTDECL,
  ERR_INVALIDTYPEDECL,
  ERR_INVALIDVARDECL,
  ERR_INVALIDSUBDECL,

  ERR_INVALIDCONDITION,
  ERR_INVALIDINDEX,
  ERR_INVALIDSTRING,
  ERR_INVALIDFLOAT,
} ErrorCode;


#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALIDCONSTANT "Invalid constant!"
#define ERM_INVALIDTYPE "Invalid type!"
#define ERM_INVALIDBASICTYPE "Invalid basic type!"
#define ERM_INVALIDPARAM "Invalid parameter!"
#define ERM_INVALIDSTATEMENT "Invalid statement!"
#define ERM_INVALIDARGUMENTS "Invalid arguments!"
#define ERM_INVALIDCOMPARATOR "Invalid comparator!"
#define ERM_INVALIDEXPRESSION "Invalid expression!"
#define ERM_INVALIDTERM "Invalid term!"
#define ERM_INVALIDFACTOR "Invalid factor!"
#define ERM_INVALIDCONSTDECL "Invalid constant declaration!"
#define ERM_INVALIDTYPEDECL "Invalid type declaration!"
#define ERM_INVALIDVARDECL "Invalid variable declaration!"
#define ERM_INVALIDSUBDECL "Invalid subroutine declaration!"

#define ERM_INVALIDCONDITION "Invalid condition!"
#define ERM_INVALIDINDEX "Invalid index!"
#define ERM_INVALIDSTRING "Invalid const string!\n[ string too long (100000) ]"
#define ERM_INVALIDFLOAT "Invalid float value!"

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
