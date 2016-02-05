//
//  lexer.cpp
//  Lexer
//
//  Created by Nathan Ansel on 1/31/16.
//  Copyright © 2016 Nathan Ansel. All rights reserved.
//

#include "lexer.h"
#include <ctype.h>


char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme

int yylex() {
  static char c = -1;         // Have we read the first character yet?
  int char_type;              // Hold the character type

  // Prepare the buffer to hold the lexeme
  for (int i = 0; i < MAX_LEXEME_LEN; i++) {
    lexeme[i] = '\0';
  }
  yytext = lexeme;
  yyleng = 0;

  // If the very first character has not yet been read, read it
  if (c < 0) {
    c = fgetc(yyin);
  }

  // Test for end of file
  if (feof(yyin)) {
    // Ready for next time
    c = -1;
    // Done!
    return TOK_EOF;
  }

  // Store current character and read the next
  lexeme[yyleng++] = c;
  c = fgetc(yyin);
  while (!isspace(c)) {
    // this isn't the end of the lexeme
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    // Check if the next character is an EOF
    if (feof(c)) {
      c = -1;
    }
  }

  if (!strcmp(lexeme, "if")) {
    return TOK_IF;
  }
  if (!strcmp(lexeme, "else")) {
    return TOK_ELSE;
  }
  if (!strcmp(lexeme, "for")) {
    return TOK_FOR;
  }
  if (!strcmp(lexeme, "while")) {
    return TOK_WHILE;
  }
  if (!strcmp(lexeme, "print")) {
    return TOK_PRINT;
  }
  if (!strcmp(lexeme, "return")) {
    return TOK_RETURN;
  }
  if (!strcmp(lexeme, "continue")) {
    return TOK_CONTINUE;
  }
  if (!strcmp(lexeme, "break")) {
    return TOK_BREAK;
  }
  if (!strcmp(lexeme, "debug")) {
    return TOK_DEBUG;
  }
  if (!strcmp(lexeme, "read")) {
    return TOK_READ;
  }
  if (!strcmp(lexeme, "let")) {
    return TOK_LET;
  }
  if (!strcmp(lexeme, "int")) {
    return TOK_INT;
  }
  if (!strcmp(lexeme, "float")) {
    return TOK_FLOAT;
  }
  if (!strcmp(lexeme, "string")) {
    return TOK_STRING;
  }
  if (!strcmp(lexeme, ";")) {
    return TOK_SEMICOLON;
  }
  if (!strcmp(lexeme, "(")) {
    return TOK_OPENPAREN;
  }
  if (!strcmp(lexeme, ")")) {
    return TOK_CLOSEPAREN;
  }
  if (!strcmp(lexeme, "[")) {
    return TOK_OPENBRACE;
  }
  if (!strcmp(lexeme, "]")) {
    return TOK_CLOSEBRACE;
  }
  if (!strcmp(lexeme, "{")) {
    return TOK_OPENBRACKET;
  }
  if (!strcmp(lexeme, "}")) {
    return TOK_CLOSEBRACKET;
  }
  if (!strcmp(lexeme, ",")) {
    return TOK_COMMA;
  }
  if (!strcmp(lexeme, "+")) {
    return TOK_PLUS;
  }
  if (!strcmp(lexeme, "-")) {
    return TOK_MINUS;
  }
  if (!strcmp(lexeme, "*")) {
    return TOK_MULTIPLY;
  }
  if (!strcmp(lexeme, "/")) {
    return TOK_DIVIDE;
  }
  if (!strcmp(lexeme, "=")) {
    return TOK_ASSIGN;
  }
  if (!strcmp(lexeme, "==")) {
    return TOK_EQUALTO;
  }
  if (!strcmp(lexeme, "<")) {
    return TOK_LESSTHAN;
  }
  if (!strcmp(lexeme, ">")) {
    return TOK_GREATERTHAN;
  }
  if (!strcmp(lexeme, "<>")) {
    return TOK_NOTEQUALTO;
  }
  if (!strcmp(lexeme, "and")) {
    return TOK_AND;
  }
  if (!strcmp(lexeme, "or")) {
    return TOK_OR;
  }
  if (!strcmp(lexeme, "not")) {
    return TOK_NOT;
  }
  if (!strcmp(lexeme, "length")) {
    return TOK_LENGTH;
  }

  // for (int i = 0; i < yyleng; i++) {
  // 
  // }

  // We don't yet know how to recognize any lexemes
  return TOK_UNKNOWN;
}
