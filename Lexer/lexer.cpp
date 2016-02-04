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

  // We don't yet know how to recognize any lexemes
  return TOK_UNKNOWN;
}
