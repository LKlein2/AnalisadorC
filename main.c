#define TKN_ID 1
#define TKN_VOID 2
#define TKN_INT 4
#define TKN_FLOAT 6
#define TKN_DOUBLE 7
#define TKN_CHAR 69
#define TKN_BREAK 10
#define TKN_IF 11
#define TKN_ELSE 12
#define TKN_WHILE 13
#define TKN_DO 14
#define TKN_FOR 15
#define TKN_SWITCH 16
#define TKN_CASE 17
#define TKN_CONTINUE 18
#define TKN_RETURN 25
#define TKN_A_PAR 34
#define TKN_F_PAR 35
#define TKN_A_CHAVE 36
#define TKN_F_CHAVE 37
#define TKN_A_CON 38
#define TKN_F_CON 39
#define TKN_PONTO_VIRG 40
#define TKN_DOIS_PONTOS 41
#define TKN_VIRGULA 42
#define TKN_ATRIBUICAO 43
#define TKN_SOMA 44
#define TKN_DIMINUI 45
#define TKN_MULTIPLICA 46
#define TKN_DIVIDE 47
#define TKN_RESTO_DIVISAO 48
#define TKN_COMP_MAIOR 49
#define TKN_COMP_MENOR 50
#define TKN_MENOS_IGUAL 52
#define TKN_MAIS_IGUAL 53
#define TKN_MULTIPLICA_IGUAL 54
#define TKN_DIVIDE_IGUAL 55
#define TKN_COMP_MAIOR_IGUAL 57
#define TKN_COMP_MENOR_IGUAL 58
#define TKN_DECREMENT 59
#define TKN_INCREMENT 60
#define TKN_COMP_IGUAL 61
#define TKN_COMP_DIF 62
#define TKN_NEGACAO 63
#define TKN_TERNARIO 64
#define TKN_SHIFT_LEFT 65
#define TKN_SHIFT_RIGHT 66
#define TKN_OR 67
#define TKN_AND 68
#define TKN_LOGICAL_AND 70
#define TKN_LOGICAL_OR 71
#define TKN_XOR 72
#define TKN_CONST_INT 80
#define TKN_CONST_FLOAT 81
#define TKN_CONST_OCTAL 82
#define TKN_CONST_HEX 83
#define TKN_ERROR_E 100
#define TKN_ERROR_CONST_FLOAT 101
#define TKN_ERROR_OU 102
#define TKN_ERROR_AND 103
#define TKN_ERROR_CONST_HEX 104
#define MAX_COD 1000

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char TKsParserLex[1000][20];
char lex[10];
int pos = 0;
int previousState = 0;
int positionCol = 0;
int subcolumn = 0;
int line = 0;
int column = 0;
int tab = 0;
int TKsParser[1000];
int posParser = 0;
int posParserLex = 0;
int token = 0;
int doWhile = 0;
int laco = 0;

typedef struct TS {
  int identificadorEscopo;
  char id[10];
  char type[10];
  struct TS * prox;
}
table;
table * ts;

struct reservedWord {
  char palavra[20];
  int token;
};

struct reservedWord reservedWordList[] = {
  {
    "void",
    TKN_VOID
  },
  {
    "int",
    TKN_INT
  },
  {
    "float",
    TKN_FLOAT
  },
  {
    "double",
    TKN_DOUBLE
  },
  {
    "break",
    TKN_BREAK
  },
  {
    "if",
    TKN_IF
  },
  {
    "else",
    TKN_ELSE
  },
  {
    "while",
    TKN_WHILE
  },
  {
    "do",
    TKN_DO
  },
  {
    "for",
    TKN_FOR
  },
  {
    "switch",
    TKN_SWITCH
  },
  {
    "case",
    TKN_CASE
  },
  {
    "continue",
    TKN_CONTINUE
  },
  {
    "return",
    TKN_RETURN
  },
  {
    "fimtable",
    TKN_ID
  }
};

int reservedWord(char lex[]) {
  int postab = 0;

  while (strcmp("fimtable", reservedWordList[postab].palavra) != 0) {
    if (strcmp(lex, reservedWordList[postab].palavra) == 0)
      return reservedWordList[postab].token;
    postab++;
  }
  return TKN_ID;
}

int analizeTokens(char st[], char lex[]) {
  int state = 0, fim = 0, posl = 0;
  positionCol = pos;

  while (!fim) {
    char c = st[pos];

    lex[posl++] = c;

    switch (state) {
    case 0:
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
        pos++;
        state = 1;
        previousState = 0;
        break;
      }

      if (c >= '0' && c <= '9') {
        if (c == '0') {
          pos++;
          state = 8;
          previousState = 0;
          break;
        }

        pos++;
        state = 2;
        previousState = 0;
        break;
      }

      if (c == '.') {
        pos++;
        state = 3;
        previousState = 0;
        break;
      }

      if (c == '=') {
        c = st[++pos];
        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_COMP_IGUAL;
        } else {
          lex[posl] = '\0';
          return TKN_ATRIBUICAO;
        }
      }

      if (c == '!') {
        c = st[++pos];
        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_COMP_DIF;
        } else {
          lex[posl] = '\0';
          return TKN_NEGACAO;
        }
      }

      if (c == '?') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_TERNARIO;
      }

      if (c == '+') {
        c = st[++pos];

        if (c == '+') {
          lex[posl++] = '+';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_INCREMENT;
        } else if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_MAIS_IGUAL;
        } else {
          lex[posl] = '\0';
          return TKN_SOMA;
        }
      }

      if (c == '-') {
        c = st[++pos];

        if (c == '-') {
          lex[posl++] = '-';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_DECREMENT;
        } else if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_MENOS_IGUAL;
        } else {
          lex[posl] = '\0';
          return TKN_DIMINUI;
        }
      }

      if (c == '*') {
        c = st[++pos];

        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_MULTIPLICA_IGUAL;
        } else {
          lex[posl] = '\0';
          return TKN_MULTIPLICA;
        }
      }

      if (c == '/') {
        c = st[++pos];

        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_DIVIDE_IGUAL;
        } else {
          lex[posl] = '\0';
          return TKN_DIVIDE;
        }
      }

      if (c == '%') {
        c = st[++pos];

        lex[posl] = '\0';
        return TKN_RESTO_DIVISAO;
      }

      if (c == '|') {
        c = st[++pos];

        if (c == '|') {
          lex[posl++] = '|';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_OR;
        }
        return TKN_LOGICAL_OR;
      }

      if (c == '&') {
        c = st[++pos];

        if (c == '&') {
          lex[posl++] = '&';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_AND;
        }
        return TKN_LOGICAL_AND;
      }

      if (c == '>') {
        c = st[++pos];

        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_COMP_MAIOR_IGUAL;
        } else if (c == '>') {
          lex[posl++] = '>';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_SHIFT_RIGHT;
        } else {
          lex[posl] = '\0';
          return TKN_COMP_MAIOR;
        }
      }

      if (c == '<') {
        c = st[++pos];

        if (c == '=') {
          lex[posl++] = '=';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_COMP_MENOR_IGUAL;
        } else if (c == '<') {
          lex[posl++] = '<';
          lex[posl] = '\0';
          pos++;
          previousState = 0;
          return TKN_SHIFT_LEFT;
        } else {
          lex[posl] = '\0';
          return TKN_COMP_MENOR;
        }
      }

      if (c == '(') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_A_PAR;
      }

      if (c == ')') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_F_PAR;
      }

      if (c == '{') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_A_CHAVE;
      }

      if (c == '}') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_F_CHAVE;
      }

      if (c == '[') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_A_CON;
      }

      if (c == ']') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_F_CON;
      }

      if (c == ',') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_VIRGULA;
      }

      if (c == ';') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_PONTO_VIRG;
      }

      if (c == ':') {
        lex[posl] = '\0';
        pos++;
        previousState = 0;
        return TKN_DOIS_PONTOS;
      }

      if (c == ' ' || c == '\n') {
        pos++;
        posl--;
        positionCol = pos;
      }

      if (c == 127) {
        pos++;
        posl--;
        line++;
        subcolumn = pos;
        positionCol = pos;
      }

      if (c == 9) {
        tab++;
        pos++;
        positionCol = pos;
        posl--;
        subcolumn -= 3;
      }

      if (c == '\0') return -1;

      break;
    case 1:
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9')) {
        pos++;
        break;
      }

      lex[--posl] = '\0';
      previousState = 1;
      return reservedWord(lex);
    case 2:
      if (c >= '0' && c <= '9') {
        pos++;
        break;
      }

      if (c == '.') {
        pos++;
        state = 3;
        previousState = 2;
        break;
      }

      if (c == 'E') {
        pos++;
        state = 4;
        previousState = 2;
        break;
      }

      lex[--posl] = '\0';
      previousState = 2;
      return TKN_CONST_INT;
    case 3:
      if (c >= '0' && c <= '9') {
        pos++;
        state = 7;
        break;
      } else {
        return TKN_ERROR_CONST_FLOAT;
      }
      case 4:
        if (c >= '0' && c <= '9') {
          pos++;
          state = 6;
          break;
        } else if (c == '-' || c == '+') {
          pos++;
          state = 5;
          break;
        }
        return TKN_ERROR_E;
      case 5:
        if (c >= '0' && c <= '9') {
          pos++;
          state = 6;
          break;
        }
        return TKN_ERROR_E;
      case 6:
        if (c >= '0' && c <= '9') {
          pos++;
          break;
        }
        if (previousState == 2) {
          lex[--posl] = '\0';
          previousState = 6;
          return TKN_CONST_INT;
        } else {
          lex[--posl] = '\0';
          previousState = 6;
          return TKN_CONST_FLOAT;
        }
        case 7:
          if (c >= '0' && c <= '9') {
            pos++;
            break;
          }
          if (c == 'E') {
            pos++;
            state = 4;
            previousState = 7;
            break;
          }
          lex[--posl] = '\0';
          previousState = 7;
          return TKN_CONST_FLOAT;
        case 8:
          if (c >= '0' && c <= '9') {
            pos++;
            break;
          }
          if (c == 'x' || c == 'X') {
            pos++;
            state = 9;
            previousState = 8;
            break;
          }
          lex[--posl] = '\0';
          return TKN_CONST_INT;
        case 9:
          if (c >= '0' && c <= '9') {
            pos++;
            previousState = 9;
            break;
          } else {
            if (previousState == 8)
              return TKN_ERROR_CONST_HEX;
          }
          lex[--posl] = '\0';
          return TKN_CONST_INT;
    }
  }
}

void readToken() {
  token = TKsParser[posParser++];
  line = TKsParser[posParser++];
  column = TKsParser[posParser++];
  strcpy(lex, TKsParserLex[posParserLex++]);
}

void addSymbol(char * id, char * type) {
  table * aux = (table * ) malloc(sizeof(table));
  strcpy(aux -> id, id);
  strcpy(aux -> type, type);
  aux -> identificadorEscopo = laco;
  aux -> prox = ts;
  ts = aux;
}

int verifyDuplicated(char * lex, table * tab) {
  if (tab == NULL)
    return 1;

  if (!strcmp(tab -> id, lex) && tab -> identificadorEscopo == laco) {
    printf("Variavel %s ja foi declarada\n", lex);
    printf("Erro ocorreu na line %d, column %d", line, column);
    exit(0);
  }

  return verifyDuplicated(lex, tab -> prox);
}

void whatTypeIsIt(char * id, char * Type, table * tab) {
  if (tab == NULL)
    return;

  if (!strcmp(tab -> id, id))
    strcpy(Type, tab -> type);

  whatTypeIsIt(id, Type, tab -> prox);
}

void geralabel(char label[]) {
  static int numlabel = 0;
  sprintf(label, "LB%03d", numlabel++);
}

void geratemp(char temp[]) {
  static int numtemp = 0;
  sprintf(temp, "T%03d", numtemp++);
}

int PROGC(char * PROGC_c) {
  char LD_c[MAX_COD];

  if (LD(LD_c)) {
    strcpy(PROGC_c, LD_c);
    return 1;
  } else
    return 0;
}

int LD(char * LD_c) {
  char DEC_c[MAX_COD];
  char RLD_c[MAX_COD];

  if (DEC(DEC_c)) {
    if (RLD(RLD_c)) {
      sprintf(LD_c, "%s%s\n", DEC_c, RLD_c);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int RLD(char * RLD_c) {
  char LD_c[MAX_COD];

  if (LD(LD_c)) {
    strcpy(RLD_c, LD_c);
    return 1;
  } else
    return 1;
}

int DEC(char * DEC_c) {
  char RDEC_t[10];
  char Type_t[10];
  char RDEC_c[MAX_COD];

  if (TIPO(Type_t)) {
    strcpy(RDEC_t, Type_t);
    if (token == TKN_ID) {
      if (verifyDuplicated(lex, ts))
        addSymbol(lex, Type_t);
      readToken();
      if (RDEC(RDEC_t, RDEC_c)) {
        strcpy(DEC_c, RDEC_c);
        return 1;
      } else
        return 0;
    } else {
      printf("An error occurred. Expecting >> id << on line %d column %d\n", line, column);
      return 0;
    }
  } else
    return 0;
}

int RDEC(char * RDEC_t, char * RDEC_c) {
  char DF_c[MAX_COD];
  char DV_t[10];

  if (token == TKN_VIRGULA) {
    strcpy(DV_t, RDEC_t);
    readToken();
    if (DV(DV_t))
      return 1;
    else
      return 0;
  } else if (token == TKN_A_PAR) {
    readToken();
    if (DF(DF_c)) {
      strcpy(RDEC_c, DF_c);
      return 1;
    } else
      return 0;
  } else if (token == TKN_PONTO_VIRG) {
    readToken();
    return 1;
  } else if (token == TKN_ATRIBUICAO) {
    readToken();
    if (token == TKN_CONST_INT || token == TKN_CONST_FLOAT) {
      readToken();
      if (token == TKN_PONTO_VIRG) {
        readToken();
        return 1;
      } else {
        printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
        return 0;
      }
    } else {
      printf("An error occurred. esperava token contante inteira na line %d column %d\n", line, column);
      return 0;
    }
  } else {
    printf("An error occurred. Expecting >> ;', ')' ou ', << on line %d column %d\n", line, column);
    return 0;
  }
}

int DV(char * DV_t) {
  char RDV_t[10];
  if (token == TKN_ID) {
    strcpy(RDV_t, DV_t);
    if (verifyDuplicated(lex, ts))
      addSymbol(lex, DV_t);
    readToken();
    if (RDV(RDV_t))
      return 1;
    else
      return 0;
  } else {
    printf("An error occurred. Expecting >> id << on line %d column %d\n", line, column);
    return 0;
  }
}

int RDV(char * RDV_t) {
  char DV_t[10];
  if (token == TKN_VIRGULA) {
    strcpy(DV_t, RDV_t);
    readToken();
    if (DV(DV_t))
      return 1;
    else
      return 0;
  } else if (token == TKN_PONTO_VIRG) {
    readToken();
    return 1;
  } else {
    printf("An error occurred. Expecting >> ,' ou '; << on line %d column %d\n", line, column);
    return 0;
  }
}

int TIPO(char * Type_t) {
  if ((token == TKN_CHAR) || (token == TKN_INT) || (token == TKN_FLOAT)) {
    switch (token) {
    case TKN_CHAR:
      strcpy(Type_t, "char");
      break;
    case TKN_INT:
      strcpy(Type_t, "int");
      break;
    case TKN_FLOAT:
      strcpy(Type_t, "float");
      break;
    case TKN_DOUBLE:
      strcpy(Type_t, "double");
      break;
    }
    readToken();
    return 1;
  } else {
    return 0;
  }
}

int DF(char * DF_c) {
  char CORPO_c[MAX_COD];
  if (LP()) {
    if (token == TKN_F_PAR) {
      readToken();
      if (token == TKN_A_CHAVE) {
        readToken();
        if (CORPO(CORPO_c)) {
          if (token == TKN_F_CHAVE) {
            strcpy(DF_c, CORPO_c);
            readToken();
            return 1;
          } else {
            printf("An error occurred. Expecting >> } << on line %d column %d\n", line, column);
            return 0;
          }
        } else
          return 0;
      } else {
        printf("An error occurred. Expecting >> { << on line %d column %d\n", line, column);
        return 0;
      }
    } else {
      printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
      return 0;
    }
  } else
    return 0;
}

int LP() {
  char TIPO_t[10];

  if (TIPO(TIPO_t)) {
    if (token == TKN_ID) {
      if (verifyDuplicated(lex, ts))
        addSymbol(lex, TIPO_t);
      readToken();
      if (RLP())
        return 1;
      else
        return 0;
    } else {
      printf("An error occurred. Expecting >> id << on line %d column %d\n", line, column);
      return 0;
    }
  } else
    return 1;
}

int RLP() {
  char TIPO_t[10];

  if (token == TKN_VIRGULA) {
    readToken();
    if (TIPO(TIPO_t)) {
      if (token == TKN_ID) {
        if (verifyDuplicated(lex, ts))
          addSymbol(lex, TIPO_t);
        readToken();
        if (RLP())
          return 1;
        else
          return 0;
      } else {
        printf("An error occurred. Expecting >> id << on line %d column %d\n", line, column);
        return 0;
      }
    } else
      return 0;
  } else
    return 1;
}

int CORPO(char * CORPO_c) {
  char LCD_c[MAX_COD];
  if (LCD(LCD_c)) {
    strcpy(CORPO_c, LCD_c);
    return 1;
  } else {
    return 0;
  }
}

int LCD(char * LCD_c) {
  char DV_t[10];
  char TIPO_t[10];
  char COM_c[MAX_COD];
  char LCDline_c[MAX_COD];

  strcpy(LCDline_c, "");

  if (COM(COM_c)) {
    if (LCD(LCDline_c)) {
      sprintf(LCD_c, "%s%s", COM_c, LCDline_c);
      return 1;
    } else
      return 0;
  } else if (TIPO(TIPO_t)) {
    strcpy(DV_t, TIPO_t);
    if (DV(DV_t)) {
      if (LCD(LCDline_c)) {
        strcpy(LCD_c, LCDline_c);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else
    return 1;
}

int COM(char * COM_c) {
  char TIPO_t[10];
  char E_tp[10];
  char E_p[10];
  char E_c[MAX_COD];
  char LCD_c[MAX_COD];
  char RDEC_c[MAX_COD];
  char COMWHILE_c[MAX_COD];
  char COMFOR_c[MAX_COD];
  char COMDOWHILE_c[MAX_COD];
  char COMIF_c[MAX_COD];
  char RDEC_t[10];

  if (E(E_tp, E_p, E_c)) {
    if (token == TKN_PONTO_VIRG) {
      strcpy(COM_c, E_c);
      readToken();
      return 1;
    } else {
      printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
      return 0;
    }
  } else if (COMWHILE(COMWHILE_c)) {
    strcpy(COM_c, COMWHILE_c);
    return 1;
  } else if (COMDOWHILE(COMDOWHILE_c)) {
    strcpy(COM_c, COMDOWHILE_c);
    return 1;
  } else if (COMIF(COMIF_c)) {
    strcpy(COM_c, COMIF_c);
    return 1;
  } else if (COMFOR(COMFOR_c)) {
    strcpy(COM_c, COMFOR_c);
    return 1;
  } else if (token == TKN_RETURN) {
    readToken();
    if (token == TKN_PONTO_VIRG) {
      readToken();
      return 1;
    } else {
      printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
      return 0;
    }
  } else if (token == TKN_BREAK) {
    if (laco == 0) {
      printf("An error occurred. Not expecting >> break << here.");
      exit(0);
    }
    readToken();
    if (token == TKN_PONTO_VIRG) {
      readToken();
      return 1;
    } else {
      printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
      return 0;
    }
  } else if (token == TKN_CONTINUE) {
    if (laco == 0) {
      printf("An error occurred. Not expecting >> continue << here.");
      exit(0);
    }
    readToken();
    if (token == TKN_PONTO_VIRG) {
      readToken();
      return 1;
    } else {
      printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
      return 0;
    }
  } else if (token == TKN_A_CHAVE) {
    readToken();
    if (LCD(LCD_c)) {
      if (token == TKN_F_CHAVE) {
        strcpy(COM_c, LCD_c);
        readToken();
        return 1;
      } else {
        printf("An error occurred. Expecting >> } << on line %d column %d\n", line, column);
        return 0;
      }
    } else
      return 0;
  } else if (TIPO(TIPO_t)) {
    strcpy(RDEC_t, TIPO_t);
    if (token == TKN_ID) {
      if (verifyDuplicated(lex, ts))
        addSymbol(lex, TIPO_t);
      readToken();
      if (RDEC(RDEC_t, RDEC_c)) {
        strcpy(COM_c, RDEC_c);
        return 1;
      } else
        return 0;
    } else {
      printf("An error occurred. Expecting >> id << on line %d column %d\n", line, column);
      return 0;
    }
  } else {
    return 0;
  }
}

int COMIF(char * COMIF_c) {
  char E_tp[10];
  char E_p[MAX_COD];
  char E_c[MAX_COD];
  char COM_c[MAX_COD];
  char RIF_c[MAX_COD];
  char labelelse[10], labelfim[10];

  strcpy(RIF_c, "");

  if (token == TKN_IF) {
    readToken();
    if (token == TKN_A_PAR) {
      readToken();
      if (E(E_tp, E_p, E_c)) {
        if (token == TKN_F_PAR) {
          readToken();
          if (COM(COM_c)) {
            if (RIF(RIF_c)) {
              geralabel(labelelse);
              geralabel(labelfim);
              if (strcmp(RIF_c, ""))
                sprintf(COMIF_c, "%s\tif %s==0 goto %s\n%s\tgoto %s\n%s:\n%s%s:\n", E_c, E_p, labelelse, COM_c, labelfim, labelelse, RIF_c, labelfim);
              else
                sprintf(COMIF_c, "%s\tif %s==0 goto %s\n%s%s:\n", E_c, E_p, labelfim, COM_c, labelfim);
              return 1;
            } else
              return 0;
          } else
            return 0;
        } else {
          printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
          return 0;
        }
      } else
        return 0;
    } else {
      printf("An error occurred. Expecting >> ( << on line %d column %d\n", line, column);
      return 0;
    }
  } else {
    return 0;
  }
}

int RIF(char * RIF_c) {
  char COM_c[MAX_COD];

  if (token == TKN_ELSE) {
    readToken();
    if (COM(COM_c)) {
      strcpy(RIF_c, COM_c);
      return 1;
    } else
      return 0;
  } else
    return 1;
}

int COMFOR(char * COMFOR_c) {
  char COM_c[MAX_COD];
  char RFOR_c[MAX_COD];
  char EIF1_c[MAX_COD];
  char EIF2_c[MAX_COD];
  char EIF3_c[MAX_COD];
  char EIF1_p[MAX_COD];
  char EIF2_p[MAX_COD];
  char EIF3_p[MAX_COD];
  char labellaco[MAX_COD];
  char labelfim[MAX_COD];

  if (token == TKN_FOR) {
    laco++;
    readToken();
    if (token == TKN_A_PAR) {
      readToken();
      if (EIF(EIF1_c, EIF1_p)) {
        if (token == TKN_PONTO_VIRG) {
          readToken();
          if (EIF(EIF2_c, EIF2_p)) {
            if (token == TKN_PONTO_VIRG) {
              readToken();
              if (EIF(EIF3_c, EIF3_p)) {
                if (token == TKN_F_PAR) {
                  readToken();
                  if (COM(COM_c)) {
                    laco--;
                    if (RFOR(RFOR_c)) {
                      geralabel(labellaco);
                      geralabel(labelfim);
                      sprintf(COMFOR_c, "%s%s:\n%s\tif %s == 0 goto %s\n%s%s\tgoto %s\n%s:\n%s", EIF1_c, labellaco,
                        EIF2_c, EIF2_p, labelfim, COM_c, EIF3_c, labellaco, labelfim, RFOR_c);
                      return 1;
                    } else
                      return 0;
                  } else
                    return 0;
                } else {
                  printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
                  return 0;
                }
              } else
                return 0;
            } else {
              printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
              return 0;
            }
          } else
            return 0;
        } else {
          printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
          return 0;
        }
      } else
        return 0;
    } else {
      printf("An error occurred. Expecting >> ( << on line %d column %d\n", line, column);
      return 0;
    }
  } else
    return 0;
}

int RFOR(char * RFOR_c) {
  char COM_c[MAX_COD];

  if (COM(COM_c)) {
    strcpy(RFOR_c, COM_c);
    return 1;
  } else
    return 1;
}

int EIF(char * EIF_c, char * EIF_p) {
  char E_tp[10];
  char E_p[MAX_COD];
  char E_c[MAX_COD];

  if (E(E_tp, E_p, E_c)) {
    strcpy(EIF_c, E_c);
    strcpy(EIF_p, E_p);
    return 1;
  } else
    return 1;
}

int COMWHILE(char * COMWHILE_c) {
  char E_tp[10];
  char E_p[MAX_COD];
  char E_c[MAX_COD];
  char COM_c[MAX_COD];
  char RWHILE_c[MAX_COD];
  char labelinicio[10];
  char labelfim[10];

  if (token == TKN_WHILE && doWhile == 0) {
    laco++;
    readToken();
    if (token == TKN_A_PAR) {
      readToken();
      if (E(E_tp, E_p, E_c)) {
        if (token == TKN_F_PAR) {
          readToken();
          if (COM(COM_c)) {
            if (RWHILE(RWHILE_c)) {
              geralabel(labelinicio);
              geralabel(labelfim);
              sprintf(COMWHILE_c, "%s:\n%s\tif %s==0 goto %s\n%s\tgoto %s\n%s:\n%s", labelinicio, E_c, E_p, labelfim, COM_c, labelinicio, labelfim, RWHILE_c);
              laco--;
              return 1;
            } else
              return 0;
          } else
            return 0;
        } else {
          printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
          return 0;
        }
      } else
        return 0;
    } else {
      printf("An error occurred. Expecting >> ( << on line %d column %d\n", line, column);
      return 0;
    }
  } else {
    return 0;
  }
}

int RWHILE(char * RWHILE_c) {
  char COM_c[MAX_COD];

  if (COM(COM_c)) {
    strcpy(RWHILE_c, COM_c);
    return 1;
  } else
    return 1;
}

int COMDOWHILE(char * COMDOWHILE_c) {
  char E_tp[10];
  char E_p[MAX_COD];
  char E_c[MAX_COD];
  char COM_c[MAX_COD];
  char RDOWHILE_c[MAX_COD];
  char label[10];

  if (token == TKN_DO) {
    laco++;
    doWhile++;
    readToken();
    if (COM(COM_c)) {
      if (RDOWHILE(RDOWHILE_c)) {
        if (token == TKN_WHILE) {
          readToken();
          if (token == TKN_A_PAR) {
            readToken();
            if (E(E_tp, E_p, E_c)) {
              if (token == TKN_F_PAR) {
                readToken();
                if (token == TKN_PONTO_VIRG) {
                  readToken();
                  doWhile--;
                  geralabel(label);
                  sprintf(COMDOWHILE_c, "%s:\n%s%s\tif %s==1 goto %s\n%s", label, COM_c, E_c, E_p, label, RDOWHILE_c);
                  laco--;
                  return 1;
                } else {
                  printf("An error occurred. Expecting >> ; << on line %d column %d\n", line, column);
                }
              } else {
                printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
                return 0;
              }
            } else
              return 0;
          } else {
            printf("An error occurred. Expecting >> ( << on line %d column %d\n", line, column);
            return 0;
          }
        } else {
          printf("An error occurred. Expecting >> while << on line %d column %d\n", line, column);
          return 0;
        }
      } else
        return 0;
    } else
      return 0;
  } else {
    return 0;
  }
}

int RDOWHILE(char * RDOWHILE_c) {
  char COM_c[MAX_COD];

  if (COM(COM_c)) {
    strcpy(RDOWHILE_c, COM_c);
    return 1;
  } else
    return 1;
}

int RE() {
  if (token == TKN_A_PAR) {
    readToken();
    if (LP()) {
      if (token == TKN_F_PAR) {
        readToken();
        return 1;
      } else {
        printf("An error occurred. Expecting >> ) << on line %d column %d\n", line, column);
        return 0;
      }
    } else
      return 0;
  } else
    return 1;
}

int E(char * E_tp, char * E_p, char * E_c) {
  char Eline_h[10];
  char Eline_s[10];
  char Eline_c[MAX_COD];
  char Eline_p[10];
  char Eline_hp[10];
  char Eline_hc[MAX_COD];
  char Eline_sp[10];
  char Eline_sc[MAX_COD];
  char S1_tp[10];
  char S1_h[10];
  char S1_s[10];
  char S1_p[10];
  char S1_c[MAX_COD];

  if (S1(S1_tp, S1_h, S1_s, S1_p, S1_c)) {
    strcpy(Eline_h, S1_tp);
    strcpy(Eline_hp, S1_p);
    strcpy(Eline_hc, S1_c);
    if (Enew(Eline_h, Eline_s, Eline_p, Eline_hp, Eline_sp, Eline_c, Eline_hc, Eline_sc)) {
      strcpy(E_tp, Eline_s);
      strcpy(E_p, Eline_sp);
      strcpy(E_c, Eline_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int Enew(char * Eline_h, char * Eline_s, char * Eline_p, char * Eline_hp, char * Eline_sp, char * Eline_c, char * Eline_hc, char * Eline_sc) {
  char ElinS2_sp[10];
  char ElinS2_sc[MAX_COD];
  char ElinS2_hp[10];
  char ElinS2_hc[MAX_COD];
  char ElinS2_h[10];
  char ElinS2_s[10];
  char ElinS2_p[10];
  char ElinS2_c[MAX_COD];
  char S1_tp[10];
  char S1_h[10];
  char S1_s[10];
  char S1_p[10];
  char S1_c[MAX_COD];

  if (token == TKN_VIRGULA) {
    readToken();
    if (S1(S1_tp, S1_h, S1_s, S1_p, S1_c)) {
      strcpy(ElinS2_h, S1_tp);
      if (Enew(ElinS2_h, ElinS2_s, ElinS2_p, ElinS2_hp, ElinS2_sp, ElinS2_c, ElinS2_hc, ElinS2_sc)) {
        strcpy(Eline_s, ElinS2_s);
        strcpy(Eline_p, ElinS2_p);
        sprintf(Eline_c, "%s %s", S1_c, ElinS2_c);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(Eline_s, Eline_h);
    strcpy(Eline_sp, Eline_hp);
    strcpy(Eline_sc, Eline_hc);
    return 1;
  }
}

int S1(char * S1_tp, char * S1_h, char * S1_s, char * S1_p, char * S1_c) {
  char S1line_h[10];
  char S1line_s[10];
  char S1line_tp[10];
  char S1line_p[10];
  char S1line_c[MAX_COD];
  char S2_tp[10];
  char S2_h[10];
  char S2_s[10];
  char S2_p[10];
  char S2_c[MAX_COD];

  if (S2(S2_tp, S2_h, S2_s, S2_p, S2_c)) {
    if (token == TKN_ATRIBUICAO) {
      strcpy(S1line_h, S2_tp);
      readToken();
      if (S1(S1line_tp, S1line_h, S1line_s, S1line_p, S1line_c)) {
        strcpy(S1_tp, S1line_s);
        strcpy(S1_p, S2_p);
        sprintf(S1_c, "%s\t%s = %s\n", S1line_c, S2_p, S1line_p);
        return 1;
      } else
        return 0;
    } else if (token == TKN_MULTIPLICA_IGUAL) {
      strcpy(S1line_h, S2_tp);
      readToken();
      if (S1(S1line_tp, S1line_h, S1line_s, S1line_p, S1line_c)) {
        strcpy(S1_tp, S1line_s);
        strcpy(S1_p, S2_p);
        sprintf(S1_c, "%s\t%s = %s * %s\n", S1line_c, S2_p, S2_p, S1line_p);
        return 1;
      } else
        return 0;
    } else if (token == TKN_DIVIDE_IGUAL) {
      strcpy(S1line_h, S2_tp);
      readToken();
      if (S1(S1line_tp, S1line_h, S1line_s, S1line_p, S1line_c)) {
        strcpy(S1_tp, S1line_s);
        strcpy(S1_p, S2_p);
        sprintf(S1_c, "%s\t%s = %s / %s\n", S1line_c, S2_p, S2_p, S1line_p);
        return 1;
      } else
        return 0;
    } else if (token == TKN_MAIS_IGUAL) {
      strcpy(S1line_h, S2_tp);
      readToken();
      if (S1(S1line_tp, S1line_h, S1line_s, S1line_p, S1line_c)) {
        strcpy(S1_tp, S1line_s);
        strcpy(S1_p, S2_p);
        sprintf(S1_c, "%s\t%s = %s + %s\n", S1line_c, S2_p, S2_p, S1line_p);
        return 1;
      } else
        return 0;
    } else if (token == TKN_MENOS_IGUAL) {
      strcpy(S1line_h, S2_tp);
      readToken();
      if (S1(S1line_tp, S1line_h, S1line_s, S1line_p, S1line_c)) {
        strcpy(S1_tp, S1line_s);
        strcpy(S1_p, S2_p);
        sprintf(S1_c, "%s\t%s = %s - %s\n", S1line_c, S2_p, S2_p, S1line_p);
        return 1;
      } else
        return 0;
    } else {
      strcpy(S1_tp, S2_tp);
      strcpy(S1_p, S2_p);
      strcpy(S1_c, S2_c);
      return 1;
    }
  }
}

int S2(char * S2_tp, char * S2_h, char * S2_s, char * S2_p, char * S2_c) {
  char S2line_h[10];
  char S2line_s[10];
  char S2line_hp[10];
  char S2line_sp[10];
  char S2line_hc[MAX_COD];
  char S2line_sc[MAX_COD];
  char S3_tp[10];
  char S3_p[10];
  char S3_c[MAX_COD];

  if (S3(S3_tp, S3_p, S3_c)) {
    strcpy(S2line_h, S3_tp);
    strcpy(S2line_hp, S3_p);
    strcpy(S2line_hc, S3_c);
    if (S2new(S2line_h, S2line_s, S2line_hp, S2line_sp, S2line_hc, S2line_sc)) {
      strcpy(S2_tp, S2line_s);
      strcpy(S2_p, S2line_sp);
      strcpy(S2_c, S2line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S2new(char * S2line_h, char * S2line_s, char * S2line_hp, char * S2line_sp, char * S2line_hc, char * S2line_sc) {
  char S2_tp[10];
  char S2_h[10];
  char S2_s[10];
  char S2_p[10];
  char S2_c[MAX_COD];
  char S2linS2_h[10];
  char S2linS2_s[10];
  char S2linS2_hp[10];
  char S2linS2_sp[10];
  char S2linS2_hc[MAX_COD];
  char S2linS2_sc[MAX_COD];

  if (token == TKN_TERNARIO) {
    readToken();
    if (S2(S2_tp, S2_h, S2_s, S2_p, S2_c)) {
      if (token == TKN_DOIS_PONTOS) {
        readToken();
        if (S2(S2_tp, S2_h, S2_s, S2_p, S2_c)) {
          if (S2new(S2linS2_h, S2linS2_s, S2linS2_hp, S2linS2_sp, S2linS2_hc, S2linS2_sc))
            return 1;
          else
            return 0;
        } else
          return 0;
      } else {
        printf("An error occurred. Expecting >> : << on line %d column %d\n", line, column);
        return 0;
      }
    } else
      return 0;
  } else {
    strcpy(S2line_s, S2line_h);
    strcpy(S2line_sp, S2line_hp);
    strcpy(S2line_sc, S2line_hc);
    return 1;
  }
}

int S3(char * S3_tp, char * S3_p, char * S3_c) {
  char S3line_h[10];
  char S3line_s[10];
  char S3line_hp[10];
  char S3line_sp[10];
  char S3line_hc[MAX_COD];
  char S3line_sc[MAX_COD];
  char S4_tp[10];
  char S4_p[10];
  char S4_c[MAX_COD];

  if (S4(S4_tp, S4_p, S4_c)) {
    strcpy(S3line_h, S4_tp);
    strcpy(S3line_hp, S4_p);
    strcpy(S3line_hc, S4_c);
    if (S3new(S3line_h, S3line_s, S3line_hp, S3line_sp, S3line_hc, S3line_sc)) {
      strcpy(S3_tp, S3line_s);
      strcpy(S3_p, S3line_sp);
      strcpy(S3_c, S3line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S3new(char * S3line_h, char * S3line_s, char * S3line_hp, char * S3line_sp, char * S3line_hc, char * S3line_sc) {
  char S3linS2_h[10];
  char S3linS2_s[10];
  char S3linS2_hp[10];
  char S3linS2_sp[10];
  char S3linS2_hc[MAX_COD];
  char S3linS2_sc[MAX_COD];
  char S4_tp[10];
  char S4_p[10];
  char S4_c[MAX_COD];

  if (token == TKN_OR) {
    readToken();
    if (S4(S4_tp, S4_p, S4_c)) {
      strcpy(S3linS2_h, "int");
      geratemp(S3linS2_hp);
      sprintf(S3linS2_hc, "%s%s\t%s = %s || %s\n", S3line_hc, S4_c, S3linS2_hp, S3line_hp, S4_p);
      if (S3new(S3linS2_h, S3linS2_s, S3linS2_hp, S3linS2_sp, S3linS2_hc, S3linS2_sc)) {
        strcpy(S3line_s, S3linS2_s);
        strcpy(S3line_sp, S3linS2_sp);
        strcpy(S3line_sc, S3linS2_sc);
        return 1;
      }
    } else
      return 0;
  } else {
    strcpy(S3line_s, S3line_h);
    strcpy(S3line_sp, S3line_hp);
    strcpy(S3line_sc, S3line_hc);
    return 1;
  }
}

int S4(char * S4_tp, char * S4_p, char * S4_c) {
  char S4line_h[10];
  char S4line_s[10];
  char S4line_hp[10];
  char S4line_sp[10];
  char S4line_hc[MAX_COD];
  char S4line_sc[MAX_COD];
  char S5_tp[10];
  char S5_p[10];
  char S5_c[MAX_COD];

  if (S5(S5_tp, S5_p, S5_c)) {
    strcpy(S4line_h, S5_tp);
    strcpy(S4line_hp, S5_p);
    strcpy(S4line_hc, S5_c);
    if (S4new(S4line_h, S4line_s, S4line_hp, S4line_sp, S4line_hc, S4line_sc)) {
      strcpy(S4_tp, S4line_s);
      strcpy(S4_p, S4line_sp);
      strcpy(S4_c, S4line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S4new(char * S4line_h, char * S4line_s, char * S4line_hp, char * S4line_sp, char * S4line_hc, char * S4line_sc) {
  char S4linS2_h[10];
  char S4linS2_s[10];
  char S4linS2_hp[10];
  char S4linS2_sp[10];
  char S4linS2_hc[MAX_COD];
  char S4linS2_sc[MAX_COD];
  char S5_tp[10];
  char S5_p[10];
  char S5_c[MAX_COD];

  if (token == TKN_AND) {
    readToken();
    if (S5(S5_tp, S5_p, S5_c)) {
      strcpy(S4linS2_h, "int");
      geratemp(S4linS2_hp);
      sprintf(S4linS2_hc, "%s%s\t%s = %s && %s\n", S4line_hc, S5_c, S4linS2_hp, S4line_hp, S5_p);
      if (S4new(S4linS2_h, S4linS2_s, S4linS2_hp, S4linS2_sp, S4linS2_hc, S4linS2_sc)) {
        strcpy(S4line_s, S4linS2_s);
        strcpy(S4line_sp, S4linS2_sp);
        strcpy(S4line_sc, S4linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S4line_s, S4line_h);
    strcpy(S4line_sp, S4line_hp);
    strcpy(S4line_sc, S4line_hc);
    return 1;
  }
}

int S5(char * S5_tp, char * S5_p, char * S5_c) {
  char S6_tp[10];
  char S6_p[10];
  char S6_c[MAX_COD];
  char S5line_h[10];
  char S5line_s[10];
  char S5line_hp[10];
  char S5line_sp[10];
  char S5line_hc[MAX_COD];
  char S5line_sc[MAX_COD];

  if (S6(S6_tp, S6_p, S6_c)) {
    strcpy(S5line_h, S6_tp);
    strcpy(S5line_hp, S6_p);
    strcpy(S5line_hc, S6_c);
    if (S5new(S5line_h, S5line_s, S5line_hp, S5line_sp, S5line_hc, S5line_sc)) {
      strcpy(S5_tp, S5line_s);
      strcpy(S5_p, S5line_sp);
      strcpy(S5_c, S5line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S5new(char * S5line_h, char * S5line_s, char * S5line_hp, char * S5line_sp, char * S5line_hc, char * S5line_sc) {
  char S6_tp[10];
  char S6_p[10];
  char S6_c[MAX_COD];
  char S5linS2_h[10];
  char S5linS2_s[10];
  char S5linS2_hp[10];
  char S5linS2_sp[10];
  char S5linS2_hc[MAX_COD];
  char S5linS2_sc[MAX_COD];

  if (token == TKN_LOGICAL_OR) {
    readToken();
    if (S6(S6_tp, S6_p, S6_c)) {
      strcpy(S5linS2_h, "int");
      geratemp(S5linS2_hp);
      sprintf(S5linS2_hc, "%s%s\t%s = %s | %s\n", S5line_hc, S6_c, S5linS2_hp, S5line_hp, S6_p);
      if (S5new(S5linS2_h, S5linS2_s, S5linS2_hp, S5linS2_sp, S5linS2_hc, S5linS2_sc)) {
        strcpy(S5line_s, S5linS2_s);
        strcpy(S5line_sp, S5linS2_sp);
        strcpy(S5line_sc, S5linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S5line_s, S5line_h);
    strcpy(S5line_sp, S5line_hp);
    strcpy(S5line_sc, S5line_hc);
    return 1;
  }
}

int S6(char * S6_tp, char * S6_p, char * S6_c) {
  char S7_tp[10];
  char S7_p[10];
  char S7_c[MAX_COD];
  char S6line_h[10];
  char S6line_s[10];
  char S6line_hp[10];
  char S6line_sp[10];
  char S6line_hc[MAX_COD];
  char S6line_sc[MAX_COD];

  if (S7(S7_tp, S7_p, S7_c)) {
    strcpy(S6line_h, S7_tp);
    strcpy(S6line_hp, S7_p);
    strcpy(S6line_hc, S7_c);
    if (S6new(S6line_h, S6line_s, S6line_hp, S6line_sp, S6line_hc, S6line_sc)) {
      strcpy(S6_tp, S6line_s);
      strcpy(S6_p, S6line_sp);
      strcpy(S6_c, S6line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S6new(char * S6line_h, char * S6line_s, char * S6line_hp, char * S6line_sp, char * S6line_hc, char * S6line_sc) {
  char S7_tp[10];
  char S7_p[10];
  char S7_c[MAX_COD];
  char S6linS2_h[10];
  char S6linS2_s[10];
  char S6linS2_hp[10];
  char S6linS2_sp[10];
  char S6linS2_hc[MAX_COD];
  char S6linS2_sc[MAX_COD];

  if (token == TKN_XOR) {
    readToken();
    if (S7(S7_tp, S7_p, S7_c)) {
      strcpy(S6linS2_h, "int");
      geratemp(S6linS2_hp);
      sprintf(S6linS2_hc, "%s%s\t%s = %s ^ %s\n", S6line_hc, S7_c, S6linS2_hp, S6line_hp, S7_p);
      if (S6new(S6linS2_h, S6linS2_s, S6linS2_hp, S6linS2_sp, S6linS2_hc, S6linS2_sc)) {
        strcpy(S6line_s, S6linS2_s);
        strcpy(S6line_sp, S6linS2_sp);
        strcpy(S6line_sc, S6linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S6line_s, S6line_h);
    strcpy(S6line_sp, S6line_hp);
    strcpy(S6line_sc, S6line_hc);
    return 1;
  }
}

int S7(char * S7_tp, char * S7_p, char * S7_c) {
  char S8_tp[10];
  char S8_p[10];
  char S8_c[MAX_COD];
  char S7line_h[10];
  char S7line_s[10];
  char S7line_hp[10];
  char S7line_sp[10];
  char S7line_hc[MAX_COD];
  char S7line_sc[MAX_COD];

  if (S8(S8_tp, S8_p, S8_c)) {
    strcpy(S7line_h, S8_tp);
    strcpy(S7line_hp, S8_p);
    strcpy(S7line_hc, S8_c);
    if (S7new(S7line_h, S7line_s, S7line_hp, S7line_sp, S7line_hc, S7line_sc)) {
      strcpy(S7_tp, S7line_s);
      strcpy(S7_p, S7line_sp);
      strcpy(S7_c, S7line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S7new(char * S7line_h, char * S7line_s, char * S7line_hp, char * S7line_sp, char * S7line_hc, char * S7line_sc) {
  char S8_tp[10];
  char S8_p[10];
  char S8_c[MAX_COD];
  char S7linS2_h[10];
  char S7linS2_s[10];
  char S7linS2_hp[10];
  char S7linS2_sp[10];
  char S7linS2_hc[MAX_COD];
  char S7linS2_sc[MAX_COD];

  if (token == TKN_LOGICAL_AND) {
    readToken();
    if (S8(S8_tp, S8_p, S8_c)) {
      strcpy(S7linS2_h, "int");
      geratemp(S7linS2_hp);
      sprintf(S7linS2_hc, "%s%s\t%s = %s & %s\n", S7line_hc, S8_c, S7linS2_hp, S7line_hp, S8_p);
      if (S7new(S7linS2_h, S7linS2_s, S7linS2_hp, S7linS2_sp, S7linS2_hc, S7linS2_sc)) {
        strcpy(S7line_s, S7linS2_s);
        strcpy(S7line_sp, S7linS2_sp);
        strcpy(S7line_sc, S7linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S7line_s, S7line_h);
    strcpy(S7line_sp, S7line_hp);
    strcpy(S7line_sc, S7line_hc);
    return 1;
  }
}

int S8(char * S8_tp, char * S8_p, char * S8_c) {
  char S9_tp[10];
  char S9_p[10];
  char S9_c[MAX_COD];
  char S8line_h[10];
  char S8line_s[10];
  char S8line_hp[10];
  char S8line_sp[10];
  char S8line_hc[MAX_COD];
  char S8line_sc[MAX_COD];

  if (S9(S9_tp, S9_p, S9_c)) {
    strcpy(S8line_h, S9_tp);
    strcpy(S8line_hp, S9_p);
    strcpy(S8line_hc, S9_c);
    if (S8new(S8line_h, S8line_s, S8line_hp, S8line_sp, S8line_hc, S8line_sc)) {
      strcpy(S8_tp, S8line_s);
      strcpy(S8_p, S8line_sp);
      strcpy(S8_c, S8line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S8new(char * S8line_h, char * S8line_s, char * S8line_hp, char * S8line_sp, char * S8line_hc, char * S8line_sc) {
  char S9_tp[10];
  char S9_p[10];
  char S9_c[MAX_COD];
  char S8linS2_h[10];
  char S8linS2_s[10];
  char S8linS2_hp[10];
  char S8linS2_sp[10];
  char S8linS2_hc[MAX_COD];
  char S8linS2_sc[MAX_COD];

  if (token == TKN_COMP_IGUAL) {
    readToken();
    if (S9(S9_tp, S9_p, S9_c)) {
      strcpy(S8linS2_h, "int");
      geratemp(S8linS2_hp);
      sprintf(S8linS2_hc, "%s%s\t%s = %s == %s\n", S8line_hc, S9_c, S8linS2_hp, S8line_hp, S9_p);
      if (S8new(S8linS2_h, S8linS2_s, S8linS2_hp, S8linS2_sp, S8linS2_hc, S8linS2_sc)) {
        strcpy(S8line_s, S8linS2_s);
        strcpy(S8line_sp, S8linS2_sp);
        strcpy(S8line_sc, S8linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_COMP_DIF) {
    readToken();
    if (S9(S9_tp, S9_p, S9_c)) {
      strcpy(S8linS2_h, "int");
      geratemp(S8linS2_hp);
      sprintf(S8linS2_hc, "%s%s\t%s = %s != %s\n", S8line_hc, S9_c, S8linS2_hp, S8line_hp, S9_p);
      if (S8new(S8linS2_h, S8linS2_s, S8linS2_hp, S8linS2_sp, S8linS2_hc, S8linS2_sc)) {
        strcpy(S8line_s, S8linS2_s);
        strcpy(S8line_sp, S8linS2_sp);
        strcpy(S8line_sc, S8linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S8line_s, S8line_h);
    strcpy(S8line_sp, S8line_hp);
    strcpy(S8line_sc, S8line_hc);
    return 1;
  }
}

int S9(char * S9_tp, char * S9_p, char * S9_c) {
  char S10_tp[10];
  char S10_p[10];
  char S10_c[MAX_COD];
  char S9line_h[10];
  char S9line_s[10];
  char S9line_hp[10];
  char S9line_sp[10];
  char S9line_hc[MAX_COD];
  char S9line_sc[MAX_COD];

  if (S10(S10_tp, S10_p, S10_c)) {
    strcpy(S9line_h, S10_tp);
    strcpy(S9line_hp, S10_p);
    strcpy(S9line_hc, S10_c);
    if (S9new(S9line_h, S9line_s, S9line_hp, S9line_sp, S9line_hc, S9line_sc)) {
      strcpy(S9_tp, S9line_s);
      strcpy(S9_p, S9line_sp);
      strcpy(S9_c, S9line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S9new(char * S9line_h, char * S9line_s, char * S9line_hp, char * S9line_sp, char * S9line_hc, char * S9line_sc) {
  char S10_tp[10];
  char S10_p[10];
  char S10_c[MAX_COD];
  char S9linS2_h[10];
  char S9linS2_s[10];
  char S9linS2_hp[10];
  char S9linS2_sp[10];
  char S9linS2_hc[MAX_COD];
  char S9linS2_sc[MAX_COD];

  if (token == TKN_COMP_MENOR) {
    readToken();
    if (S10(S10_tp, S10_p, S10_c)) {
      strcpy(S9linS2_h, "int");
      geratemp(S9linS2_hp);
      sprintf(S9linS2_hc, "%s%s\t%s = %s < %s\n", S9line_hc, S10_c, S9linS2_hp, S9line_hp, S10_p);
      if (S9new(S9linS2_h, S9linS2_s, S9linS2_hp, S9linS2_sp, S9linS2_hc, S9linS2_sc)) {
        strcpy(S9line_s, S9linS2_s);
        strcpy(S9line_sp, S9linS2_sp);
        strcpy(S9line_sc, S9linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_COMP_MAIOR) {
    readToken();
    if (S10(S10_tp, S10_p, S10_c)) {
      strcpy(S9linS2_h, "int");
      geratemp(S9linS2_hp);
      sprintf(S9linS2_hc, "%s%s\t%s = %s > %s\n", S9line_hc, S10_c, S9linS2_hp, S9line_hp, S10_p);
      if (S9new(S9linS2_h, S9linS2_s, S9linS2_hp, S9linS2_sp, S9linS2_hc, S9linS2_sc)) {
        strcpy(S9line_s, S9linS2_s);
        strcpy(S9line_sp, S9linS2_sp);
        strcpy(S9line_sc, S9linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_COMP_MENOR_IGUAL) {
    readToken();
    if (S10(S10_tp, S10_p, S10_c)) {
      strcpy(S9linS2_h, "int");
      geratemp(S9linS2_hp);
      sprintf(S9linS2_hc, "%s%s\t%s = %s <= %s\n", S9line_hc, S10_c, S9linS2_hp, S9line_hp, S10_p);
      if (S9new(S9linS2_h, S9linS2_s, S9linS2_hp, S9linS2_sp, S9linS2_hc, S9linS2_sc)) {
        strcpy(S9line_s, S9linS2_s);
        strcpy(S9line_sp, S9linS2_sp);
        strcpy(S9line_sc, S9linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_COMP_MAIOR_IGUAL) {
    readToken();
    if (S10(S10_tp, S10_p, S10_c)) {
      strcpy(S9linS2_h, "int");
      geratemp(S9linS2_hp);
      sprintf(S9linS2_hc, "%s%s\t%s = %s >= %s\n", S9line_hc, S10_c, S9linS2_hp, S9line_hp, S10_p);
      if (S9new(S9linS2_h, S9linS2_s, S9linS2_hp, S9linS2_sp, S9linS2_hc, S9linS2_sc)) {
        strcpy(S9line_s, S9linS2_s);
        strcpy(S9line_sp, S9linS2_sp);
        strcpy(S9line_sc, S9linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S9line_s, S9line_h);
    strcpy(S9line_sp, S9line_hp);
    strcpy(S9line_sc, S9line_hc);
    return 1;
  }
}

int S10(char * S10_tp, char * S10_p, char * S10_c) {
  char S11_tp[10];
  char S11_p[10];
  char S11_c[MAX_COD];
  char S10line_h[10];
  char S10line_s[10];
  char S10line_hp[10];
  char S10line_sp[10];
  char S10line_hc[MAX_COD];
  char S10line_sc[MAX_COD];

  if (S11(S11_tp, S11_p, S11_c)) {
    strcpy(S10line_h, S11_tp);
    strcpy(S10line_hp, S11_p);
    strcpy(S10line_hc, S11_c);
    if (S10new(S10line_h, S10line_s, S10line_hp, S10line_sp, S10line_hc, S10line_sc)) {
      strcpy(S10_tp, S10line_s);
      strcpy(S10_p, S10line_sp);
      strcpy(S10_c, S10line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S10new(char * S10line_h, char * S10line_s, char * S10line_hp, char * S10line_sp, char * S10line_hc, char * S10line_sc) {
  char S11_tp[10];
  char S11_p[10];
  char S11_c[MAX_COD];
  char S10linS2_h[10];
  char S10linS2_s[10];
  char S10linS2_hp[10];
  char S10linS2_sp[10];
  char S10linS2_hc[MAX_COD];
  char S10linS2_sc[MAX_COD];

  if (token == TKN_SHIFT_LEFT) {
    readToken();
    if (S11(S11_tp, S11_p, S11_c)) {
      strcpy(S10linS2_h, "int");
      geratemp(S10linS2_hp);
      sprintf(S10linS2_hc, "%s%s\t%s = %s << %s\n", S10line_hc, S11_c, S10linS2_hp, S10line_hp, S11_p);
      if (S10new(S10linS2_h, S10linS2_s, S10linS2_hp, S10linS2_sp, S10linS2_hc, S10linS2_sc)) {
        strcpy(S10line_s, S10linS2_s);
        strcpy(S10line_sp, S10linS2_sp);
        strcpy(S10line_sc, S10linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_SHIFT_RIGHT) {
    readToken();
    if (S11(S11_tp, S11_p, S11_c)) {
      strcpy(S10linS2_h, "int");
      geratemp(S10linS2_hp);
      sprintf(S10linS2_hc, "%s%s\t%s = %s >> %s\n", S10line_hc, S11_c, S10linS2_hp, S10line_hp, S11_p);
      if (S10new(S10linS2_h, S10linS2_s, S10linS2_hp, S10linS2_sp, S10linS2_hc, S10linS2_sc)) {
        strcpy(S10line_s, S10linS2_s);
        strcpy(S10line_sp, S10linS2_sp);
        strcpy(S10line_sc, S10linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S10line_s, S10line_h);
    strcpy(S10line_sp, S10line_hp);
    strcpy(S10line_sc, S10line_hc);
    return 1;
  }
}

int S11(char * S11_tp, char * S11_p, char * S11_c) {
  char S12_tp[10];
  char S12_p[10];
  char S12_c[MAX_COD];
  char S11line_h[10];
  char S11line_s[10];
  char S11line_hp[10];
  char S11line_sp[10];
  char S11line_hc[MAX_COD];
  char S11line_sc[MAX_COD];

  if (S12(S12_tp, S12_p, S12_c)) {
    strcpy(S11line_h, S12_tp);
    strcpy(S11line_hp, S12_p);
    strcpy(S11line_hc, S12_c);
    if (S11new(S11line_h, S11line_s, S11line_hp, S11line_sp, S11line_hc, S11line_sc)) {
      strcpy(S11_tp, S11line_s);
      strcpy(S11_p, S11line_sp);
      strcpy(S11_c, S11line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S11new(char * S11line_h, char * S11line_s, char * S11line_hp, char * S11line_sp, char * S11line_hc, char * S11line_sc) {
  char S12_tp[10];
  char S12_p[10];
  char S12_c[MAX_COD];
  char S11linS2_h[10];
  char S11linS2_s[10];
  char S11linS2_hp[10];
  char S11linS2_sp[10];
  char S11linS2_hc[MAX_COD];
  char S11linS2_sc[MAX_COD];

  if (token == TKN_SOMA) {
    readToken();
    if (S12(S12_tp, S12_p, S12_c)) {
      if (!strcmp(S11line_h, "int") && !strcmp(S12_tp, "int"))
        strcpy(S11linS2_h, "int");
      else
        strcpy(S11linS2_h, "float");
      geratemp(S11linS2_hp);
      sprintf(S11linS2_hc, "%s%s\t%s = %s + %s\n", S11line_hc, S12_c, S11linS2_hp, S11line_hp, S12_p);
      if (S11new(S11linS2_h, S11linS2_s, S11linS2_hp, S11linS2_sp, S11linS2_hc, S11linS2_sc)) {
        strcpy(S11line_s, S11linS2_s);
        strcpy(S11line_sp, S11linS2_sp);
        strcpy(S11line_sc, S11linS2_sc);
        return 1;
      } else
        return 0;
    }
  } else if (token == TKN_DIMINUI) {
    readToken();
    if (S12(S12_tp, S12_p, S12_c)) {
      if (!strcmp(S11line_h, "int") && !strcmp(S12_tp, "int"))
        strcpy(S11linS2_h, "int");
      else
        strcpy(S11linS2_h, "float");
      geratemp(S11linS2_hp);
      sprintf(S11linS2_hc, "%s%s\t%s = %s - %s\n", S11line_hc, S12_c, S11linS2_hp, S11line_hp, S12_p);
      if (S11new(S11linS2_h, S11linS2_s, S11linS2_hp, S11linS2_sp, S11linS2_hc, S11linS2_sc)) {
        strcpy(S11line_s, S11linS2_s);
        strcpy(S11line_sp, S11linS2_sp);
        strcpy(S11line_sc, S11linS2_sc);
        return 1;
      } else
        return 0;
    }
  } else {
    strcpy(S11line_s, S11line_h);
    strcpy(S11line_sp, S11line_hp);
    strcpy(S11line_sc, S11line_hc);
    return 1;
  }
}

int S12(char * S12_tp, char * S12_p, char * S12_c) {
  char S13_tp[10];
  char S13_p[10];
  char S13_c[MAX_COD];
  char S12line_h[10];
  char S12line_s[10];
  char S12line_hp[10];
  char S12line_sp[10];
  char S12line_hc[MAX_COD];
  char S12line_sc[MAX_COD];

  if (S13(S13_tp, S13_p, S13_c)) {
    strcpy(S12line_h, S13_tp);
    strcpy(S12line_hp, S13_p);
    strcpy(S12line_hc, S13_c);

    if (S12new(S12line_h, S12line_s, S12line_hp, S12line_sp, S12line_hc, S12line_sc)) {
      strcpy(S12_tp, S12line_s);
      strcpy(S12_p, S12line_sp);
      strcpy(S12_c, S12line_sc);
      return 1;
    } else
      return 0;
  } else
    return 0;
}

int S12new(char * S12line_h, char * S12line_s, char * S12line_hp, char * S12line_sp, char * S12line_hc, char * S12line_sc) {
  char S13_tp[10];
  char S13_p[10];
  char S13_c[MAX_COD];
  char S12linS2_h[10];
  char S12linS2_s[10];
  char S12linS2_hp[10];
  char S12linS2_sp[10];
  char S12linS2_hc[MAX_COD];
  char S12linS2_sc[MAX_COD];

  if (token == TKN_MULTIPLICA) {
    readToken();
    if (S13(S13_tp, S13_p, S13_c)) {

      if (!strcmp(S12line_h, "int") && strcmp(S13_tp, "int"))
        strcpy(S12linS2_h, "int");
      else
        strcpy(S12linS2_h, "float");
      geratemp(S12linS2_hp);
      sprintf(S12linS2_hc, "%s%s\t%s = %s * %s\n", S12line_hc, S13_c, S12linS2_hp, S12line_hp, S13_p);
      if (S12new(S12linS2_h, S12linS2_s, S12linS2_hp, S12linS2_sp, S12linS2_hc, S12linS2_sc)) {
        strcpy(S12line_s, S12linS2_s);
        strcpy(S12line_sp, S12linS2_sp);
        strcpy(S12line_sc, S12linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_DIVIDE) {
    readToken();
    if (S13(S13_tp, S13_p, S13_c)) {
      if (!strcmp(S12line_h, "int") && strcmp(S13_tp, "int"))
        strcpy(S12linS2_h, "int");
      else
        strcpy(S12linS2_h, "float");
      geratemp(S12linS2_hp);
      sprintf(S12linS2_hc, "%s%s\t%s = %s / %s\n", S12line_hc, S13_c, S12linS2_hp, S12line_hp, S13_p);
      if (S12new(S12linS2_h, S12linS2_s, S12linS2_hp, S12linS2_sp, S12linS2_hc, S12linS2_sc)) {
        strcpy(S12line_s, S12linS2_s);
        strcpy(S12line_sp, S12linS2_sp);
        strcpy(S12line_sc, S12linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else if (token == TKN_RESTO_DIVISAO) {
    readToken();
    if (S13(S13_tp, S13_p, S13_c)) {
      if (!strcmp(S12line_h, "int") && !strcmp(S13_tp, "int"))
        strcpy(S12linS2_h, "int");
      else {
        printf("An error occurred. >> %% << invalid");
        exit(0);
      }
      geratemp(S12linS2_hp);
      sprintf(S12linS2_hc, "%s%s\t%s = %s %c %s\n", S12line_hc, S13_c, S12linS2_hp, S12line_hp, 37, S13_p);
      if (S12new(S12linS2_h, S12linS2_s, S12linS2_hp, S12linS2_sp, S12linS2_hc, S12linS2_sc)) {
        strcpy(S12line_s, S12linS2_s);
        strcpy(S12line_sp, S12linS2_sp);
        strcpy(S12line_sc, S12linS2_sc);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else {
    strcpy(S12line_s, S12line_h);
    strcpy(S12line_sp, S12line_hp);
    strcpy(S12line_sc, S12line_hc);
    return 1;
  }
}

int S13(char * S13_tp, char * S13_p, char * S13_c) {
  char S14_tp[10];
  char S14_p[10];
  char S14_c[MAX_COD];
  char S13line_tp[10];
  char S13line_h[10];
  char S13line_s[10];

  if (S14(S14_tp, S14_p, S14_c)) {
    if (token == TKN_DIMINUI) {
      strcpy(S13line_h, S14_tp);
      readToken();
      if (S13(S13line_tp, S13line_h, S13line_s)) {
        strcpy(S13_tp, S13line_s);
        return 1;
      } else
        return 0;
    } else if (token == TKN_INCREMENT) {
      strcpy(S13line_h, S14_tp);
      readToken();

      strcpy(S13_tp, S13line_s);
      return 1;
    } else if (token == TKN_DECREMENT) {
      strcpy(S13line_h, S14_tp);
      readToken();

      strcpy(S13_tp, S13line_s);
      return 1;
    } else if (token == TKN_NEGACAO) {
      strcpy(S13line_h, S14_tp);
      readToken();
      if (S13(S13line_tp, S13line_h, S13line_s)) {
        strcpy(S13_tp, S13line_s);
        return 1;
      } else
        return 0;
    } else {
      strcpy(S13_tp, S14_tp);
      strcpy(S13_p, S14_p);
      strcpy(S13_c, S14_c);
      return 1;
    }
  }
  return 0;
}

int S14(char * S14_tp, char * S14_p, char * S14_c) {
  char E_tp[10];

  if (token == TKN_CONST_INT) {
    strcpy(S14_tp, "int");
    geratemp(S14_p);
    sprintf(S14_c, "\t%s = %s\n", S14_p, lex);
    readToken();
    return 1;
  } else if (token == TKN_CONST_FLOAT) {
    strcpy(S14_tp, "float");
    geratemp(S14_p);
    sprintf(S14_c, "\t%s = %s\n", S14_p, lex);
    readToken();
    return 1;
  } else if (token == TKN_ID) {
    whatTypeIsIt(lex, S14_tp, ts);
    if (strcmp(S14_tp, "int") && strcmp(S14_tp, "float")) {
      printf("An error occurred. Variavel %s nao foi declarada\n", lex);
      exit(0);
    }
    strcpy(S14_p, lex);
    strcpy(S14_c, "");

    readToken();
    if (RE())
      return 1;
    else
      return 0;
  } else if (token == TKN_CHAR) {
    strcpy(S14_tp, "char");
    geratemp(S14_p);
    sprintf(S14_c, "\t%s = %s\n", S14_p, lex);
    readToken();
    return 1;
  } else if (token == TKN_A_PAR) {
    char E_p[MAX_COD], E_c[MAX_COD];
    readToken();
    if (E(E_tp, E_p, E_c)) {
      if (token == TKN_F_PAR) {
        readToken();
        strcpy(S14_c, E_c);
        strcpy(S14_p, E_p);
        return 1;
      } else
        return 0;
    } else
      return 0;
  } else
    return 0;
}

int main() {
  setbuf(stdout, NULL);

  char character;
  char lex[20];
  char file[20];
  char content[20000];
  char PROGC_c[MAX_COD];
  int choice = 0;
  ts = NULL;
  FILE * font;

  setbuf(stdout, NULL);

  int i = 0;
  do {
    do {
      printf("************************************************\n");
      printf("************************************************\n");
      printf("***** S E M A N T I C      A N A L Y S I S *****\n");
      printf("************************************************\n");
      printf("************************************************\n");
      printf("******** 1 - Erro_Continue			    	  \n");
      printf("******** 2 - Erro_Break				    	  \n");
      printf("******** 3 - Erro_Type_Incompativel       	  \n");
      printf("******** 4 - Erro_Variavel_Duplicada	    	  \n");
      printf("******** 5 - Erro_Variavel_Nao_Declarada  	  \n");
      printf("******** 6 - Teste_Erro				          \n");
      printf("******** 7 - Teste_Ok					    	  \n");
      printf("************************************************\n");
      printf("************************************************\n");
      printf("************************************************\n");
      printf("************************************************\n");
      scanf("%d", & choice);
      fflush(stdin);

      if ((choice < 0) || (choice > 7)) {
        printf("Invalid option, select an option between 1 and 7! \n");
        system("pause");
      }
      switch (choice) {
      case 1:
        strcpy(file, "Error_Continue.txt");
        choice = 0;
        break;
      case 2:
        strcpy(file, "Error_Break.txt");
        choice = 0;
        break;
      case 3:
        strcpy(file, "Error_Type_Incompativel.txt");
        choice = 0;
        break;
      case 4:
        strcpy(file, "Error_Variavel_Duplicada.txt");
        choice = 0;
        break;
      case 5:
        strcpy(file, "Error_Variavel_Nao_Declarada.txt");
        choice = 0;
        break;
      case 6:
        strcpy(file, "Teste_Erro.txt");
        choice = 0;
        break;
      case 7:
        strcpy(file, "Teste_Ok.txt");
        choice = 0;
        break;
      }
    } while ((choice < 0) || (choice > 7));
  } while (choice != 0);

  if ((font = fopen(file, "r")) == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  while (1) {
    character = fgetc(font);
    if (feof(font))
      break;
    if (character != 9 && character != 10 && character != 13) {
      content[i++] = character;
    } else if (character == 10) {
      content[i++] = 127;
    } else if (character == 9) {
      content[i++] = 9;
    }
  }
  content[i] = '\0';

  for (i = 0; i < 1000; i++) {
    TKsParser[i] = -1;
  }

  while ((token = analizeTokens(content, lex)) != -1) {
    char lineSt[3];
    char columnSt[3];
    column = positionCol - subcolumn;

    snprintf(lineSt, sizeof(lineSt), "%d", line);
    snprintf(columnSt, sizeof(columnSt), "%d", column);

    TKsParser[posParser++] = token;
    TKsParser[posParser++] = line;
    TKsParser[posParser++] = column;
    strcpy(TKsParserLex[posParserLex++], lex);
  }

  fclose(font);
  posParser = 0;
  posParserLex = 0;
  readToken();

  FILE *saida;
  saida = fopen("saida.txt", "w+");

  if (PROGC(PROGC_c)) {
    printf("%s", PROGC_c);
    printf("Semantic analysis finished succesfully\n");

	fprintf(saida, "%s", PROGC_c);
	fclose(saida);

    getchar();
  } else {
    printf("Errors occurred during semantic analysis\n");

    remove("saida.txt");
  }


  return 0;
}
