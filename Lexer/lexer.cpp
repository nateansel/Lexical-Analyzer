//
//  lexer.cpp
//  Lexer
//
//  Created by Nathan Ansel on 1/31/16.
//  Copyright © 2016 Nathan Ansel. All rights reserved.
//

#include "lexer.h"


char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme

int yylex() {
  static char c = -1;         // Have we read the first character yet?
  int char_type;              // Hold the character type
  bool string = false;

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
  while (isspace(c)) {
    c = fgetc(yyin);
  }
  if (feof(yyin)) {
    c = -1;
    return TOK_EOF;
  }

  if (isalpha(c)) {
    // Might be:
    // if
    // else
    // for
    // while
    // print
    // return
    // continue
    // break
    // debug
    // read
    // let
    // int
    // float
    // string
    // and
    // or
    // not
    // length
    // identifier

    while (isalpha(c)) {
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
    }
    if (isdigit(c) || c == '_') {
      while (isalpha(c) || isdigit(c) || c == '_') {
        lexeme[yyleng++] = c;
        c = fgetc(yyin);
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
    return TOK_IDENTIFIER;
  }

  if (isdigit(c)) {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    while (isdigit(c)) {
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
    }
    if (c == '.') {
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      while (isdigit(c)) {
        lexeme[yyleng++] = c;
        c = fgetc(yyin);
      }
      return TOK_FLOATLIT;
    }
    return TOK_INTLIT;
  }

  lexeme[yyleng++] = c;
  c = fgetc(yyin);

  if (lexeme[0] == ';') {
    return TOK_SEMICOLON;
  }
  if (lexeme[0] == '(') {
    return TOK_OPENPAREN;
  }
  if (lexeme[0] == ')') {
    return TOK_CLOSEPAREN;
  }
  if (lexeme[0] == '[') {
    return TOK_OPENBRACE;
  }
  if (lexeme[0] == ']') {
    return TOK_CLOSEBRACE;
  }
  if (lexeme[0] == '{') {
    return TOK_OPENBRACKET;
  }
  if (lexeme[0] == '}') {
    return TOK_CLOSEBRACKET;
  }
  if (lexeme[0] == ',') {
    return TOK_COMMA;
  }
  if (lexeme[0] == '+') {
    return TOK_PLUS;
  }
  if (lexeme[0] == '-') {
    return TOK_MINUS;
  }
  if (lexeme[0] == '*') {
    return TOK_MULTIPLY;
  }
  if (lexeme[0] == '/') {
    return TOK_DIVIDE;
  }
  if (lexeme[0] == ':') {
    if (c == '=') {
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      return TOK_ASSIGN;
    }
  }
  if (lexeme[0] == '=') {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    if (c == '=') {
      return TOK_EQUALTO;
    }
  }
  if (lexeme[0] == '<') {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    if (lexeme[yyleng - 1] == '>') {
      return TOK_NOTEQUALTO;
    }
    lexeme[--yyleng] = '\0';
    return TOK_LESSTHAN;
  }
  if (lexeme[0] == '>') {
    return TOK_GREATERTHAN;
  }

  if (lexeme[0] == '"') {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);

    while (c != '"') {
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      if (feof(yyin)) {
        lexeme[yyleng] = '\0';
        return TOK_EOF_SL;
      }
    }
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    return TOK_STRINGLIT;
  }

  return TOK_UNKNOWN;
}
