#ifndef __CHARCODE_H__
#define __CHARCODE_H__

typedef enum {
	CHAR_SPACE,					// ' '
	CHAR_LETTER,				// a - z, A - Z
	CHAR_DIGIT,					// 0 - 9
	CHAR_PLUS,					// +
	CHAR_MINUS,					// -
	CHAR_TIMES,					// *
	CHAR_MOD,					// %
	CHAR_SLASH,					// /
	CHAR_LT,					// <
	CHAR_GT,					// >
	CHAR_EXCLAIMATION,			// !
	CHAR_EQ,					// =
	CHAR_COMMA,					// ,
	CHAR_PERIOD,				// .
	CHAR_COLON,					// :
	CHAR_SEMICOLON,				// ;
	CHAR_SINGLEQUOTE,			// '\'
	CHAR_LPAR,					// (
	CHAR_RPAR,					// )
	CHAR_DOUBLEQUOTE,			// "
	CHAR_UNKNOWN
} CharCode;

#endif