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
  if (isspace(c)) {
    c = fgetc(yyin);
  }
  if (feof(yyin)) {
    c = -1;
    return TOK_EOF;
  }
  lexeme[yyleng++] = c;
  c = fgetc(yyin);

  if (lexeme[0] == '"') {
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
    while (c != '"') {
      if (feof(yyin)) {
        c = -1;
        break;
      }
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
    }
    lexeme[yyleng++] = c;
    c = fgetc(yyin);
  }
  else {
    while (!isspace(c)) {
      // this isn't the end of the lexeme
      lexeme[yyleng++] = c;
      c = fgetc(yyin);
      // Check if this character is an EOF
      if (feof(yyin)) {
        c = -1;
      }
    }
  }
  if (feof(yyin)) {
    c = -1;
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
  if (isalpha(lexeme[0])) {
    bool isIdent = true;
    for (int i = 1; i < yyleng; i++) {
      if (!(isalpha(lexeme[i]) || isdigit(lexeme[i]) || lexeme[i] == '_')) {
        isIdent = false;
        break;
      }
    }
    if (isIdent) {
      return TOK_IDENTIFIER;
    }
  }
  if (isdigit(lexeme[0])) {
    bool isDigit = true;
    for (int i = 1; i < yyleng; i++) {
      if (!isdigit(lexeme[i])) {
        isDigit = false;
        break;
      }
    }
    if (isDigit) {
      return TOK_INT;
    }
  }
  if (isdigit(lexeme[0])) {
    bool isFloat = true;
    int i;
    for (i = 1; i < yyleng; i++) {
      if (!isdigit(lexeme[i])) {
        if (lexeme[i] != '.') {
          isFloat = false;
          break;
        }
        else {
          i++;
          break;
        }
      }
    }
    for (i = i; i < yyleng; i++) {
      if (!isdigit(lexeme[i])) {
        isFloat = false;
        break;
      }
    }
    if (isFloat) {
      return TOK_FLOATLIT;
    }
  }
  if (lexeme[0] == '"') {
    if (lexeme[yyleng - 1] == '"') {
      return TOK_STRINGLIT;
    }
    else if (c == -1) {
      return TOK_EOF_SL;
    }
  }

  // If you get here it must be something we don't know how to recognize.
  return TOK_UNKNOWN;
}
