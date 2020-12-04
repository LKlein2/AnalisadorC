#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TK_Id 1
#define TK_Void 2
#define TK_Int 4
#define TK_Float 6
#define TK_Double 7
#define TK_Char 69
#define TK_Break 10
#define TK_If 11
#define TK_Else 12
#define TK_While 13
#define TK_Do 14
#define TK_For 15
#define TK_Switch 16
#define TK_Case 17
#define TK_Continue 18
#define TK_Return 25
#define TK_AbrePar 34
#define TK_FechaPar 35
#define TK_AbreChave 36
#define TK_FechaChave 37
#define TK_AbreColchete 38
#define TK_FechaColchete 39
#define TK_PontoeVirg 40
#define TK_DoisPontos 41
#define TK_Virgula 42
#define TK_Atrib 43
#define TK_Mais 44
#define TK_Menos 45
#define TK_Multiplicacao 46
#define TK_Divisao 47
#define TK_RestoDivisao 48
#define TK_Maior 49
#define TK_Menor 50
#define TK_MenosIgual 52
#define TK_MaisIgual 53
#define TK_MultiplicacaoIgual 54
#define TK_DivisaoIgual 55
#define TK_ComparadorMaiorIgual 57
#define TK_ComparadorMenorIgual 58
#define TK_MenosMenos 59
#define TK_MaisMais 60
#define TK_ComparadorIgual 61
#define TK_ComparadorDiferente 62
#define TK_Negacao 63
#define TK_Ternario 64
#define TK_ShiftLeft 65
#define TK_ShiftRight 66
#define TK_OU 67
#define TK_AND 68
#define TK_ELogico 70
#define TK_OULogico 71
#define TK_XOR 72
#define TK_ConstInt 80
#define TK_ConstFloat 81
#define TK_ConstOctal 82
#define TK_ConstHexa 83
#define TK_ErroE 100
#define TK_ErroConstFloat 101
#define TK_ErroOU 102
#define TK_ErroAND 103
#define TK_ErroConstHexa 104
#define MAX_COD 1000

char TKsParserLex[1000][20];
char lex[10];
int  pos = 0;
int  estado_anterior = 0;
int  posColuna = 0;
int  subColuna = 0;
int  linha = 0;
int  coluna = 0;
int  tab = 0;
int  TKsParser[1000];
int  posParser = 0;
int  posParserLex = 0;
int  token = 0;
int  doWhile = 0;
int  laco = 0;

int PROGC();

int LD();

int RLD();

int DEC();

int RDEC();

int DV(char *DV_t);

int RDV(char *RDV_t);

int TIPO(char *Tipo_t);

int DF();

int LP();

int RLP();

int CORPO();

int LCD();

int COM(char *COM_c);

int COMIF(char *COMIF_c);

int RIF(char *RIF_c);

int COMFOR(char *COMFOR_c);

int RFOR(char *RFOR_c);

int EIF(char *EIF_c, char *EIF_p);

int COMWHILE(char *COMWHILE_c);

int RWHILE(char *RWHILE_c);

int COMDOWHILE(char *COMDOWHILE_c);

int RDOWHILE(char *RDOWHILE_c);

int E(char *E_tp, char *E_p, char *E_c);

int ELinha(char *ELinha_h, char *ELinha_s, char *ELinha_p, char *ELinha_hp, char *ELinha_sp, char *ELinha_c, char *ELinha_hc, char *ELinha_sc);

int E1(char *E1_tp, char *E1_h, char *E1_s, char *E1_p, char *E1_c);

int E2(char *E2_tp, char *E2_h, char *E2_s, char *E2_p, char *E2_c);

int E2Linha(char *E2Linha_h, char *E2Linha_s, char *E2Linha_hp, char *E2Linha_sp, char *E2Linha_hc, char *E2Linha_sc);

int E3(char *E3_tp, char *E3_p, char *E3_c);

int E3Linha(char *E3Linha_h, char *E3Linha_s, char *E3Linha_hp, char *E3Linha_sp, char *E3Linha_hc, char *E3Linha_sc);

int E4(char *E4_tp, char *E4_p, char *E4_c);

int E4Linha(char *E4Linha_h, char *E4Linha_s, char *E4Linha_hp, char *E4Linha_sp, char *E4Linha_hc, char *E4Linha_sc);

int E5(char *E5_tp, char *E5_p, char *E5_c);

int E5Linha(char *E5Linha_h, char *E5Linha_s, char *E5Linha_hp, char *E5Linha_sp, char *E5Linha_hc, char *E5Linha_sc);

int E6(char *E6_tp, char *E6_p, char *E6_c);

int E6Linha(char *E6Linha_h, char *E6Linha_s, char *E6Linha_hp, char *E6Linha_sp, char *E6Linha_hc, char *E6Linha_sc);

int E7(char *E7_tp, char *E7_p, char *E7_c);

int E7Linha(char *E7Linha_h, char *E7Linha_s, char *E7Linha_hp, char *E7Linha_sp, char *E7Linha_hc, char *E7Linha_sc);

int E8(char *E8_tp, char *E8_p, char *E8_c);

int E8Linha(char *E8Linha_h, char *E8Linha_s, char *E8Linha_hp, char *E8Linha_sp, char *E8Linha_hc, char *E8Linha_sc);

int E9(char *E9_tp, char *E9_p, char *E9_c);

int E9Linha(char *E9Linha_h, char *E9Linha_s, char *E9Linha_hp, char *E9Linha_sp, char *E9Linha_hc, char *E9Linha_sc);

int E10(char *E10_tp, char *E10_p, char *E10_c);

int E10Linha(char *E10Linha_h, char *E10Linha_s, char *E10Linha_hp, char *E10Linha_sp, char *E10Linha_hc, char *E10Linha_sc);

int E11(char *E11_tp, char *E11_p, char *E11_c);

int E11Linha(char *E11Linha_h, char *E11Linha_s, char *E11Linha_hp, char *E11Linha_sp, char *E11Linha_hc, char *E11Linha_sc);

int E12(char *E12_tp, char *E12_p, char *E12_c);

int E12Linha(char *E12Linha_h, char *E12Linha_s, char *E12Linha_hp, char *E12Linha_sp, char *E12Linha_hc, char *E12Linha_sc);

int E13(char *E13_tp, char *E13_p, char *E13_c);

int E14(char *E14_tp, char *E14_p, char *E14_c);

int RE();

struct pal_res {
    char palavra[20];
    int token;
};

struct pal_res lista_pal[] = {{"void",      TK_Void},
    {"int",       TK_Int},
    {"float",     TK_Float},
    {"double",    TK_Double},
    {"break",     TK_Break},
    {"if",        TK_If},
    {"else",      TK_Else},
    {"while",     TK_While},
    {"do",        TK_Do},
    {"for",       TK_For},
    {"switch",    TK_Switch},
    {"case",      TK_Case},
    {"continue",  TK_Continue},
    {"return",    TK_Return},
    {"fimtabela", TK_Id}
};

int palavra_reservada(char lex[]) {
    int postab = 0;

    while (strcmp("fimtabela", lista_pal[postab].palavra) != 0) {
        if (strcmp(lex, lista_pal[postab].palavra) == 0) return lista_pal[postab].token;
        postab++;
    }
    return TK_Id;
}

int le_token(char st[], char lex[]) {
    int estado = 0, fim = 0, posl = 0;
    posColuna = pos;

    while (!fim) {
        char c = st[pos];

        lex[posl++] = c;

        switch (estado) {
        case 0:
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
                pos++;
                estado = 1;
                estado_anterior = 0;
                break;
            }

            if (c >= '0' && c <= '9') {
                if (c == '0') {
                    pos++;
                    estado = 8;
                    estado_anterior = 0;
                    break;
                }

                pos++;
                estado = 2;
                estado_anterior = 0;
                break;
            }

            if (c == '.') {
                pos++;
                estado = 3;
                estado_anterior = 0;
                break;
            }

            if (c == '=') {
                c = st[++pos];
                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ComparadorIgual;
                } else {
                    lex[posl] = '\0';
                    return TK_Atrib;
                }
            }

            if (c == '!') {
                c = st[++pos];
                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ComparadorDiferente;
                } else {
                    lex[posl] = '\0';
                    return TK_Negacao;
                }
            }

            if (c == '?') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_Ternario;
            }

            if (c == '+') {
                c = st[++pos];

                if (c == '+') {
                    lex[posl++] = '+';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_MaisMais;
                } else if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_MaisIgual;
                } else {
                    lex[posl] = '\0';
                    return TK_Mais;
                }
            }

            if (c == '-') {
                c = st[++pos];

                if (c == '-') {
                    lex[posl++] = '-';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_MenosMenos;
                } else if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_MenosIgual;
                } else {
                    lex[posl] = '\0';
                    return TK_Menos;
                }
            }

            if (c == '*') {
                c = st[++pos];

                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_MultiplicacaoIgual;
                } else {
                    lex[posl] = '\0';
                    return TK_Multiplicacao;
                }
            }

            if (c == '/') {
                c = st[++pos];

                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_DivisaoIgual;
                } else {
                    lex[posl] = '\0';
                    return TK_Divisao;
                }
            }

            if (c == '%') {
                c = st[++pos];

                lex[posl] = '\0';
                return TK_RestoDivisao;
            }

            if (c == '|') {
                c = st[++pos];

                if (c == '|') {
                    lex[posl++] = '|';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_OU;
                } return TK_ErroOU;
            }

            if (c == '&') {
                c = st[++pos];

                if (c == '&') {
                    lex[posl++] = '&';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_AND;
                } return TK_ErroAND;
            }

            if (c == '>') {
                c = st[++pos];

                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ComparadorMaiorIgual;
                } else if (c == '>') {
                    lex[posl++] = '>';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ShiftRight;
                } else {
                    lex[posl] = '\0';
                    return TK_Maior;
                }
            }

            if (c == '<') {
                c = st[++pos];

                if (c == '=') {
                    lex[posl++] = '=';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ComparadorMenorIgual;
                } else if (c == '<') {
                    lex[posl++] = '<';
                    lex[posl] = '\0';
                    pos++;
                    estado_anterior = 0;
                    return TK_ShiftLeft;
                }
                else {
                    lex[posl] = '\0';
                    return TK_Menor;
                }
            }

            if (c == '(') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_AbrePar;
            }

            if (c == ')') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_FechaPar;
            }

            if (c == '{') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_AbreChave;
            }

            if (c == '}') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_FechaChave;
            }

            if (c == '[') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_AbreColchete;
            }

            if (c == ']') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_FechaColchete;
            }

            if (c == ',') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_Virgula;
            }

            if (c == ';') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_PontoeVirg;
            }

            if (c == ':') {
                lex[posl] = '\0';
                pos++;
                estado_anterior = 0;
                return TK_DoisPontos;
            }

            if (c == ' ' || c == '\n') {
                pos++;
                posl--;
                posColuna = pos;
            }

            if (c == 127) {
                pos++;
                posl--;
                linha++;
                subColuna = pos;
                posColuna = pos;
            }

            if (c == 9) {
                tab++;
                pos++;
                posColuna = pos;
                posl--;
                subColuna -= 3;
            }

            if (c == '\0') return -1;

            break;
        case 1:
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9')) {
                pos++;
                break;
            }

            lex[--posl] = '\0';
            estado_anterior = 1;
            return palavra_reservada(lex);
        case 2:
            if (c >= '0' && c <= '9') {
                pos++;
                break;
            }

            if (c == '.') {
                pos++;
                estado = 3;
                estado_anterior = 2;
                break;
            }

            if (c == 'E') {
                pos++;
                estado = 4;
                estado_anterior = 2;
                break;
            }

            lex[--posl] = '\0';
            estado_anterior = 2;
            return TK_ConstInt;
        case 3:
            if (c >= '0' && c <= '9') {
                pos++;
                estado = 7;
                break;
            }
            else {
                return TK_ErroConstFloat;
            }
        case 4:
            if (c >= '0' && c <= '9') {
                pos++;
                estado = 6;
                break;
            }
            else if (c == '-' || c == '+') {
                pos++;
                estado = 5;
                break;
            }
            return TK_ErroE;
        case 5:
            if (c >= '0' && c <= '9') {
                pos++;
                estado = 6;
                break;
            }
            return TK_ErroE;
        case 6:
            if (c >= '0' && c <= '9') {
                pos++;
                break;
            }
            if (estado_anterior == 2) {
                lex[--posl] = '\0';
                estado_anterior = 6;
                return TK_ConstInt;
            } else {
                lex[--posl] = '\0';
                estado_anterior = 6;
                return TK_ConstFloat;
            }
        case 7:
            if (c >= '0' && c <= '9') {
                pos++;
                break;
            }
            if (c == 'E') {
                pos++;
                estado = 4;
                estado_anterior = 7;
                break;
            }
            lex[--posl] = '\0';
            estado_anterior = 7;
            return TK_ConstFloat;
        case 8:
            if (c >= '0' && c <= '9') {
                pos++;
                break;
            } if (c == 'x' || c == 'X') {
                pos++;
                estado = 9;
                estado_anterior = 8;
                break;
            }
            lex[--posl] = '\0';
            return TK_ConstInt;
        case 9:
            if (c >= '0' && c <= '9') {
                pos++;
                estado_anterior = 9;
                break;
            } else {
                if (estado_anterior == 8) return TK_ErroConstHexa;
            }
            lex[--posl] = '\0';
            return TK_ConstInt;
        }
    }
}

void leToken() {
    token = TKsParser[posParser++];
    linha = TKsParser[posParser++];
    coluna = TKsParser[posParser++];
    strcpy(lex, TKsParserLex[posParserLex++]);
}

typedef struct TS {
    char id[10];
    char tipo[10];
    struct TS *prox;
} tabela;

tabela *ts;

void addTabelaSimbolos(char *id, char *tipo) {
    tabela *aux = (tabela *) malloc(sizeof(tabela));
    strcpy(aux->id, id);
    strcpy(aux->tipo, tipo);
    aux->prox = ts;
    ts = aux;
}

int verificaDuplicacao(char *lex, tabela *tab) {
    if (tab == NULL) return 1;

    if (!strcmp(tab->id, lex)) {
        printf("Variavel %s ja foi declarada\n", lex);
        printf("Erro ocorreu na linha %d, coluna %d",linha,coluna);
        exit(0);
    }

    return verificaDuplicacao(lex, tab->prox);
}

void consultaTipo(char *id, char *Tipo, tabela *tab) {
    if (tab == NULL)
        return;

    if (!strcmp(tab->id, id))
    {
        strcpy(Tipo,tab->tipo);
    }
    consultaTipo(id, Tipo, tab->prox);
}

int PROGC() {
    if (LD()) {
        return 1;
    } else return 0;
}

int LD() {
    if (DEC()) {
        if (RLD()) {
            return 1;
        } else return 0;
    } else return 0;
}

int RLD(char *RLD_c) {
    char LD_c[MAX_COD];

    if (LD(LD_c)) {
        strcpy(RLD_c, LD_c);
        return 1;
    } else return 1;
}

int DEC() {
    char RDEC_t[10], Tipo_t[10];

    if (TIPO(Tipo_t)) {
        strcpy(RDEC_t, Tipo_t);
        if (token == TK_Id) {
            if (verificaDuplicacao(lex,ts)) addTabelaSimbolos(lex, Tipo_t);
            leToken();
            if (RDEC(RDEC_t)) {
                return 1;
            } else return 0;
        } else {
            printf("Erro: esperava token 'id' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else return 0;
}

int RDEC() {
    char DF_c[MAX_COD];

    char DV_t[10];
    if (token == TK_Virgula) {
        leToken();
        if (DV(DV_t)) return 1;
        else return 0;
    } else if (token == TK_AbrePar) {
        leToken();
        if (DF(DF_c)) {
            return 1;
        } else return 0;
    } else if (token == TK_PontoeVirg) {
        leToken();
        return 1;
    } else if (token == TK_Atrib) {
        leToken();
        if (token == TK_ConstInt) {
            leToken();
            if (token == TK_PontoeVirg) {
                leToken();
                return 1;
            } else {
                printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        } else {
            printf("Erro: esperava token contante inteira na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else {
        printf("Erro: esperava token ';', ')' ou ',' na linha %d coluna %d\n", linha, coluna);
        return 0;
    }
}

int DV(char *DV_t) {
	char RDV_t[10];
    if (token == TK_Id) {
        strcpy(RDV_t, DV_t);
        if (verificaDuplicacao(lex,ts)) addTabelaSimbolos(lex, DV_t);
        leToken();
        if (RDV(RDV_t)) return 1;
        else return 0;
    } else {
        printf("Erro: esperava token 'id' na linha %d coluna %d\n", linha, coluna);
        return 0;
    }
}

int RDV(char *RDV_t) {
    char DV_t[10];
    if (token == TK_Virgula) {
        strcpy(DV_t, RDV_t);
        leToken();
        if (DV(DV_t)) return 1;
        else return 0;
    } else if (token == TK_PontoeVirg) {
        leToken();
        return 1;
    } else {
        printf("Erro: esperava token ',' ou ';' na linha %d coluna %d\n", linha, coluna);
        return 0;
    }
}

int TIPO(char *Tipo_t) {
    if ((token == TK_Char) || (token == TK_Int) || (token == TK_Float)) {
        switch (token)
        {
        case TK_Char:
            strcpy(Tipo_t, "char");
            break;
        case TK_Int:
            strcpy(Tipo_t, "int");
            break;
        case TK_Float:
            strcpy(Tipo_t, "float");
            break;
        case TK_Double:
            strcpy(Tipo_t, "double");
            break;
        }
        leToken();
        return 1;
    } else {
        return 0;
    }
}

int DF() {

    if (LP()) {
        if (token == TK_FechaPar) {
            leToken();
            if (token == TK_AbreChave) {
                leToken();
                if (CORPO()) {
                    if (token == TK_FechaChave) {
                        leToken();
                        return 1;
                    } else {
                        printf("Erro: esperava token '}' na linha %d coluna %d\n", linha, coluna);
                        return 0;
                    }
                } else return 0;
            } else {
                printf("Erro: esperava token '{' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        } else {
            printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else return 0;
}

int LP() {
    char TIPO_t[10];

    if (TIPO(TIPO_t)) {
        if (token == TK_Id) {
            if (verificaDuplicacao(lex,ts))
                addTabelaSimbolos(lex, TIPO_t);
            leToken();
            if (RLP()) return 1;
            else return 0;
        } else {
            printf("Erro: esperava token 'id' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else return 1;
}

int RLP() {
    char TIPO_t[10];

    if (token == TK_Virgula) {
        leToken();
        if (TIPO(TIPO_t)) {
            if (token == TK_Id) {
                if (verificaDuplicacao(lex,ts)) addTabelaSimbolos(lex, TIPO_t);
                leToken();
                if (RLP()) return 1;
                else return 0;
            } else {
                printf("Erro: esperava token 'id' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        }
        else return 0;
    } else return 1;
}

int CORPO() {
    if (LCD()) {
        return 1;
    } else {
        return 0;
    }
}

int LCD() {
    char DV_t[10], TIPO_t[10], COM_c[MAX_COD];

    if (COM(COM_c)) {
        if (LCD()) {
            return 1;
        } else {
            return 0;
        }
    } else if (TIPO(TIPO_t)) {
        strcpy(DV_t,TIPO_t);
        if (DV(DV_t)) {
            if (LCD()) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else return 1;
}

int COM(char *COM_c) {
    char TIPO_t[10], E_tp[10], E_p[10], E_c[MAX_COD], LCD_c[MAX_COD], RDEC_c[MAX_COD];
    char COMWHILE_c[MAX_COD], COMFOR_c[MAX_COD], COMDOWHILE_c[MAX_COD], COMIF_c[MAX_COD];

    if (E(E_tp, E_p, E_c)) {
        if (token == TK_PontoeVirg) {
            strcpy(COM_c, E_c);
            leToken();
            return 1;
        } else {
            printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else if (COMWHILE(COMWHILE_c)) {
        strcpy(COM_c, COMWHILE_c);
        return 1;
    } else if (COMDOWHILE(COMDOWHILE_c)) {
        strcpy(COM_c, COMDOWHILE_c);
        return 1;
    } else if (COMIF(COMIF_c)) {
        strcpy(COM_c,COMIF_c);
        return 1;
    } else if (COMFOR(COMFOR_c)) {
        strcpy(COM_c, COMFOR_c);
        return 1;
    } else if (token == TK_Return) {
        leToken();
        if (token == TK_PontoeVirg) {
            leToken();
            return 1;
        } else {
            printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else if (token == TK_Break) {
        if(laco == 0) {
            printf("Erro: comando break fora de laco de repeticao");
            exit(0);
        }
        leToken();
        if (token == TK_PontoeVirg) {
            leToken();
            return 1;
        } else {
            printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else if (token == TK_Continue) {
        if(laco == 0) {
            printf("Erro: comando continue fora de laco de repeticao");
            exit(0);
        }
        leToken();
        if (token == TK_PontoeVirg) {
            leToken();
            return 1;
        } else {
            printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else if (token == TK_AbreChave) {
        leToken();
        if (LCD(LCD_c)) {
            if (token == TK_FechaChave) {
                strcpy(COM_c, LCD_c);
                leToken();
                return 1;
            } else {
                printf("Erro: esperava token '}' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        } else return 0;
    } else if (TIPO(TIPO_t)) {
        if (token == TK_Id) {
            if (verificaDuplicacao(lex,ts)) addTabelaSimbolos(lex, TIPO_t);
            leToken();
            if (RDEC()) {
                strcpy(COM_c, RDEC_c);
                return 1;
            } else return 0;
        } else {
            printf("Erro: esperava token 'id' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else {
        return 0;
    }
}

int COMIF(char *COMIF_c) {
    char E_tp[10], E_p[MAX_COD],E_c[MAX_COD], COM_c[MAX_COD];
    char RIF_c[MAX_COD];

    strcpy(RIF_c,"");

    if (token == TK_If) {
        leToken();
        if (token == TK_AbrePar) {
            leToken();
            if (E(E_tp, E_p, E_c)) {
                if (token == TK_FechaPar) {
                    leToken();
                    if (COM(COM_c)) {
                        if (RIF(RIF_c)) {
                            return 1;
                        } else return 0;
                    } else return 0;
                } else {
                    printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
                    return 0;
                }
            } else return 0;
        } else {
            printf("Erro: esperava token '(' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else {
        return 0;
    }
}

int RIF(char *RIF_c) {
    char COM_c[MAX_COD];

    if (token == TK_Else) {
        leToken();
        if (COM(COM_c)) {
            strcpy(RIF_c,COM_c);
            return 1;
        } else return 0;
    } else return 1;
}

int COMFOR(char *COMFOR_c) {
    char COM_c[MAX_COD], RFOR_c[MAX_COD];
    char EIF1_c[MAX_COD], EIF2_c[MAX_COD], EIF3_c[MAX_COD];
    char EIF1_p[MAX_COD], EIF2_p[MAX_COD], EIF3_p[MAX_COD];

    if (token == TK_For) {
        laco = 1;
        leToken();
        if (token == TK_AbrePar) {
            leToken();
            if (EIF(EIF1_c, EIF1_p)) {
                if (token == TK_PontoeVirg) {
                    leToken();
                    if (EIF(EIF2_c, EIF2_p)) {
                        if (token == TK_PontoeVirg) {
                            leToken();
                            if (EIF(EIF3_c, EIF3_p)) {
                                if (token == TK_FechaPar) {
                                    leToken();
                                    if (COM(COM_c)) {
                                        laco = 0;
                                        if (RFOR(RFOR_c)) {
                                        	return 1;
                                        } else return 0;
                                    } else return 0;
                                } else {
                                    printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
                                    return 0;
                                }
                            } else return 0;
                        } else {
                            printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
                            return 0;
                        }
                    } else return 0;
                } else {
                    printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
                    return 0;
                }
            } else return 0;
        } else {
            printf("Erro: esperava token '(' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else return 0;
}

int RFOR(char *RFOR_c) {
    char COM_c[MAX_COD];

    if (COM(COM_c)) {
        strcpy(RFOR_c, COM_c);
        return 1;
    } else return 1;
}

int EIF(char *EIF_c, char *EIF_p) {
    char E_tp[10], E_p[MAX_COD],E_c[MAX_COD];   ;

    if (E(E_tp, E_p, E_c)) {
        strcpy(EIF_c, E_c);
        strcpy(EIF_p, E_p);
        return 1;
    } else return 1;
}

int COMWHILE(char *COMWHILE_c) {
    char E_tp[10], E_p[MAX_COD],E_c[MAX_COD], COM_c[MAX_COD], RWHILE_c[MAX_COD];

    if (token == TK_While && doWhile != 1) {
        laco = 1;
        leToken();
        if (token == TK_AbrePar) {
            leToken();
            if (E(E_tp, E_p, E_c)) {
                if (token == TK_FechaPar) {
                    leToken();
                    if (COM(COM_c)) {
                        if (RWHILE(RWHILE_c)) {
                            laco = 0;
                            return 1;
                        } else return 0;
                    } else return 0;
                } else {
                    printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
                    return 0;
                }
            } else return 0;
        } else {
            printf("Erro: esperava token '(' na linha %d coluna %d\n", linha, coluna);
            return 0;
        }
    } else {
        return 0;
    }
}

int RWHILE(char *RWHILE_c) {
    char COM_c[MAX_COD];

    if (COM(COM_c)) {
        strcpy(RWHILE_c, COM_c);
        return 1;
    } else return 1;
}

int COMDOWHILE(char *COMDOWHILE_c) {
    char E_tp[10], E_p[MAX_COD], E_c[MAX_COD], COM_c[MAX_COD], RDOWHILE_c[MAX_COD];

    if (token == TK_Do) {
        laco = 1;
        doWhile = 1;
        leToken();
        if (COM(COM_c)) {
            if (RDOWHILE(RDOWHILE_c)) {
                if (token == TK_While) {
                    leToken();
                    if (token == TK_AbrePar) {
                        leToken();
                        if (E(E_tp, E_p, E_c)) {
                            if (token == TK_FechaPar) {
                                leToken();
                                if (token == TK_PontoeVirg) {
                                    leToken();
                                    doWhile = 0;
                                    laco = 0;
                                    return 1;
                                } else {
                                    printf("Erro: esperava token ';' na linha %d coluna %d\n", linha, coluna);
                                }
                            } else {
                                printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
                                return 0;
                            }
                        } else return 0;
                    } else {
                        printf("Erro: esperava token '(' na linha %d coluna %d\n", linha, coluna);
                        return 0;
                    }
                } else {
                    printf("Erro: esperava token 'while' na linha %d coluna %d\n", linha, coluna);
                    return 0;
                }
            } else return 0;
        } else return 0;
    } else {
        return 0;
    }
}

int RDOWHILE(char *RDOWHILE_c) {
    char COM_c[MAX_COD];

    if (COM(COM_c)) {
        strcpy(RDOWHILE_c, COM_c);
        return 1;
    } else return 1;
}

int E(char *E_tp, char *E_p, char *E_c) {
    char ELinha_h[10], ELinha_s[10], ELinha_c[MAX_COD], ELinha_p[10],ELinha_hp[10], ELinha_hc[MAX_COD], ELinha_sp[10], ELinha_sc[MAX_COD];
    char E1_tp[10], E1_h[10], E1_s[10], E1_p[10], E1_c[MAX_COD];

    if (E1(E1_tp, E1_h, E1_s, E1_p, E1_c)) {
        strcpy(ELinha_h, E1_tp);
        strcpy(ELinha_hp, E1_p);
        strcpy(ELinha_hc, E1_c);
        if (ELinha(ELinha_h, ELinha_s, ELinha_p, ELinha_hp, ELinha_sp, ELinha_c, ELinha_hc, ELinha_sc)) {
            strcpy(E_tp, ELinha_s);
            strcpy(E_p, ELinha_sp);
            strcpy(E_c, ELinha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int ELinha(char *ELinha_h, char *ELinha_s, char *ELinha_p, char *ELinha_hp, char *ELinha_sp, char *ELinha_c, char *ELinha_hc, char *ELinha_sc) {
    char ELinha2_sp[10], ELinha2_sc[MAX_COD], ELinha2_hp[10], ELinha2_hc[MAX_COD];
    char ELinha2_h[10], ELinha2_s[10], ELinha2_p[10], ELinha2_c[MAX_COD];
    char E1_tp[10], E1_h[10], E1_s[10], E1_p[10], E1_c[MAX_COD];

    if (token == TK_Virgula) {
        leToken();
        if (E1(E1_tp, E1_h, E1_s, E1_p, E1_c)) {
            strcpy(ELinha2_h, E1_tp);
            if (ELinha(ELinha2_h, ELinha2_s, ELinha2_p, ELinha2_hp, ELinha2_sp, ELinha2_c, ELinha2_hc, ELinha2_sc)) {
                strcpy(ELinha_s,ELinha2_s);
                strcpy(ELinha_p, ELinha2_p);
                sprintf(ELinha_c, "%s %s", E1_c, ELinha2_c);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(ELinha_s,ELinha_h);
        strcpy(ELinha_sp, ELinha_hp);
        strcpy(ELinha_sc, ELinha_hc);
        return 1;
    }
}

int E1(char *E1_tp, char *E1_h, char *E1_s, char *E1_p, char *E1_c) {
    char E1Linha_h[10], E1Linha_s[10], E1Linha_tp[10], E1Linha_p[10], E1Linha_c[MAX_COD];
    char E2_tp[10], E2_h[10], E2_s[10], E2_p[10], E2_c[MAX_COD];

    if (E2(E2_tp, E2_h, E2_s, E2_p, E2_c)) {
        if (token == TK_Atrib) {
            strcpy(E1Linha_h,E2_tp);
            leToken();
            if (E1(E1Linha_tp, E1Linha_h, E1Linha_s, E1Linha_p, E1Linha_c)) {
                strcpy(E1_tp, E1Linha_s);
                strcpy(E1_p, E2_p);
                sprintf(E1_c, "%s\t%s = %s\n", E1Linha_c, E2_p, E1Linha_p);
                return 1;
            }
            else return 0;
        } else if (token == TK_MultiplicacaoIgual) {
            strcpy(E1Linha_h,E2_tp);
            leToken();
            if (E1(E1Linha_tp, E1Linha_h, E1Linha_s, E1Linha_p, E1Linha_c)) {
                strcpy(E1_tp, E1Linha_s);
                strcpy(E1_p, E2_p);
                sprintf(E1_c, "%s\t%s = %s * %s\n", E1Linha_c, E2_p, E2_p, E1Linha_p);
                return 1;
            } else return 0;
        } else if (token == TK_DivisaoIgual) {
            strcpy(E1Linha_h,E2_tp);
            leToken();
            if (E1(E1Linha_tp, E1Linha_h, E1Linha_s, E1Linha_p, E1Linha_c)) {
                strcpy(E1_tp, E1Linha_s);
                strcpy(E1_p, E2_p);
                sprintf(E1_c, "%s\t%s = %s / %s\n", E1Linha_c, E2_p, E2_p, E1Linha_p);
                return 1;
            } else return 0;
        } else if (token == TK_MaisIgual) {
            strcpy(E1Linha_h,E2_tp);
            leToken();
            if (E1(E1Linha_tp, E1Linha_h, E1Linha_s, E1Linha_p, E1Linha_c)) {
                strcpy(E1_tp, E1Linha_s);
                strcpy(E1_p, E2_p);
                sprintf(E1_c, "%s\t%s = %s + %s\n", E1Linha_c, E2_p, E2_p, E1Linha_p);
                return 1;
            } else return 0;
        } else if (token == TK_MenosIgual) {
            strcpy(E1Linha_h,E2_tp);
            leToken();
            if (E1(E1Linha_tp, E1Linha_h, E1Linha_s, E1Linha_p, E1Linha_c)) {
                strcpy(E1_tp, E1Linha_s);
                strcpy(E1_p, E2_p);
                sprintf(E1_c, "%s\t%s = %s - %s\n", E1Linha_c, E2_p, E2_p, E1Linha_p);
                return 1;
            } else return 0;
        } else {
            strcpy(E1_tp, E2_tp);
            strcpy(E1_p, E2_p);
            strcpy(E1_c, E2_c);
            return 1;
        }
    }
}

int E2(char *E2_tp, char *E2_h, char *E2_s, char *E2_p, char *E2_c) {
    char E2Linha_h[10], E2Linha_s[10], E2Linha_hp[10], E2Linha_sp[10], E2Linha_hc[MAX_COD], E2Linha_sc[MAX_COD];
    char E3_tp[10], E3_p[10], E3_c[MAX_COD];

    if (E3(E3_tp, E3_p, E3_c)) {
        strcpy(E2Linha_h, E3_tp);
        strcpy(E2Linha_hp, E3_p);
        strcpy(E2Linha_hc, E3_c);
        if (E2Linha(E2Linha_h, E2Linha_s, E2Linha_hp, E2Linha_sp, E2Linha_hc, E2Linha_sc)) {
            strcpy(E2_tp, E2Linha_s);
            strcpy(E2_p, E2Linha_sp);
            strcpy(E2_c, E2Linha_sc );
            return 1;
        } else return 0;
    } else return 0;
}

int E2Linha(char *E2Linha_h, char *E2Linha_s, char *E2Linha_hp, char *E2Linha_sp, char *E2Linha_hc, char *E2Linha_sc) {
    char E2_tp[10], E2_h[10], E2_s[10], E2_p[10], E2_c[MAX_COD];
    char E2Linha2_h[10], E2Linha2_s[10], E2Linha2_hp[10], E2Linha2_sp[10], E2Linha2_hc[MAX_COD], E2Linha2_sc[MAX_COD];

    if (token == TK_Ternario) {
        leToken();
        if (E2(E2_tp, E2_h, E2_s, E2_p, E2_c)) {
            if (token == TK_DoisPontos) {
                leToken();
                if (E2(E2_tp, E2_h, E2_s, E2_p, E2_c)) {
                    if (E2Linha(E2Linha2_h, E2Linha2_s, E2Linha2_hp, E2Linha2_sp, E2Linha2_hc, E2Linha2_sc)) return 1;
                    else return 0;
                } else return 0;
            } else {
                printf("Erro: esperava token ':' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        } else return 0;
    } else {
        strcpy(E2Linha_s, E2Linha_h);
        strcpy(E2Linha_sp, E2Linha_hp);
        strcpy(E2Linha_sc, E2Linha_hc);
        return 1;
    }
}

int E3(char *E3_tp, char *E3_p, char *E3_c) {
    char E3Linha_h[10], E3Linha_s[10], E3Linha_hp[10], E3Linha_sp[10], E3Linha_hc[MAX_COD], E3Linha_sc[MAX_COD];
    char E4_tp[10], E4_p[10], E4_c[MAX_COD];

    if (E4(E4_tp, E4_p, E4_c)) {
        strcpy(E3Linha_h,E4_tp);
        strcpy(E3Linha_hp, E4_p);
        strcpy(E3Linha_hc, E4_c);
        if (E3Linha(E3Linha_h, E3Linha_s, E3Linha_hp, E3Linha_sp, E3Linha_hc, E3Linha_sc)) {
            strcpy(E3_tp, E3Linha_s);
            strcpy(E3_p, E3Linha_sp);
            strcpy(E3_c, E3Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E3Linha(char *E3Linha_h, char *E3Linha_s, char *E3Linha_hp, char *E3Linha_sp, char *E3Linha_hc, char *E3Linha_sc) {
    char E3Linha2_h[10], E3Linha2_s[10], E3Linha2_hp[10], E3Linha2_sp[10], E3Linha2_hc[MAX_COD], E3Linha2_sc[MAX_COD];
    char E4_tp[10], E4_p[10], E4_c[MAX_COD];

    if (token == TK_OU) {
        leToken();
        if (E4(E4_tp, E4_p, E4_c)) {
            strcpy(E3Linha2_h,"int");
            if (E3Linha(E3Linha2_h, E3Linha2_s, E3Linha2_hp, E3Linha2_sp, E3Linha2_hc, E3Linha2_sc)) {
                strcpy(E3Linha_s,E3Linha2_s);
                strcpy(E3Linha_sp, E3Linha2_sp);
                strcpy(E3Linha_sc, E3Linha2_sc);
                return 1;
            }
        } else return 0;
    } else {
        strcpy(E3Linha_s, E3Linha_h);
        strcpy(E3Linha_sp, E3Linha_hp);
        strcpy(E3Linha_sc, E3Linha_hc);
        return 1;
    }
}

int E4(char *E4_tp, char *E4_p, char *E4_c) {
    char E4Linha_h[10], E4Linha_s[10], E4Linha_hp[10], E4Linha_sp[10], E4Linha_hc[MAX_COD], E4Linha_sc[MAX_COD];
    char E5_tp[10], E5_p[10], E5_c[MAX_COD];

    if (E5(E5_tp, E5_p, E5_c)) {
        strcpy(E4Linha_h, E5_tp);
        strcpy(E4Linha_hp, E5_p);
        strcpy(E4Linha_hc, E5_c);
        if (E4Linha(E4Linha_h, E4Linha_s, E4Linha_hp, E4Linha_sp, E4Linha_hc, E4Linha_sc)) {
            strcpy(E4_tp, E4Linha_s);
            strcpy(E4_p, E4Linha_sp);
            strcpy(E4_c, E4Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E4Linha(char *E4Linha_h, char *E4Linha_s, char *E4Linha_hp, char *E4Linha_sp, char *E4Linha_hc, char *E4Linha_sc) {
    char E4Linha2_h[10], E4Linha2_s[10], E4Linha2_hp[10], E4Linha2_sp[10], E4Linha2_hc[MAX_COD], E4Linha2_sc[MAX_COD];
    char E5_tp[10], E5_p[10], E5_c[MAX_COD];

    if (token == TK_AND) {
    	leToken();
        if (E5(E5_tp, E5_p, E5_c)) {
            strcpy(E4Linha2_h, "int");
            if (E4Linha(E4Linha2_h, E4Linha2_s, E4Linha2_hp, E4Linha2_sp, E4Linha2_hc, E4Linha2_sc)) {
                strcpy(E4Linha_s, E4Linha2_s);
                strcpy(E4Linha_sp, E4Linha2_sp);
                strcpy(E4Linha_sc, E4Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E4Linha_s, E4Linha_h);
        strcpy(E4Linha_sp, E4Linha_hp);
        strcpy(E4Linha_sc, E4Linha_hc);
        return 1;
    }
}

int E5(char *E5_tp, char *E5_p, char *E5_c) {
    char E6_tp[10], E6_p[10], E6_c[MAX_COD];
    char E5Linha_h[10], E5Linha_s[10], E5Linha_hp[10], E5Linha_sp[10], E5Linha_hc[MAX_COD], E5Linha_sc[MAX_COD];

    if (E6(E6_tp, E6_p, E6_c)) {
        strcpy(E5Linha_h, E6_tp);
        strcpy(E5Linha_hp, E6_p);
        strcpy(E5Linha_hc, E6_c);
        if (E5Linha(E5Linha_h, E5Linha_s, E5Linha_hp, E5Linha_sp, E5Linha_hc, E5Linha_sc)) {
            strcpy(E5_tp, E5Linha_s);
            strcpy(E5_p, E5Linha_sp);
            strcpy(E5_c, E5Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E5Linha(char *E5Linha_h, char *E5Linha_s, char *E5Linha_hp, char *E5Linha_sp, char *E5Linha_hc, char *E5Linha_sc) {
    char E6_tp[10], E6_p[10], E6_c[MAX_COD];
    char E5Linha2_h[10], E5Linha2_s[10], E5Linha2_hp[10], E5Linha2_sp[10], E5Linha2_hc[MAX_COD], E5Linha2_sc[MAX_COD];

    if (token == TK_OULogico) {
        leToken();
        if (E6(E6_tp, E6_p, E6_c)) {
            strcpy(E5Linha2_h, "int");
            if (E5Linha(E5Linha2_h, E5Linha2_s, E5Linha2_hp, E5Linha2_sp, E5Linha2_hc, E5Linha2_sc)) {
                strcpy(E5Linha_s, E5Linha2_s);
                strcpy(E5Linha_sp, E5Linha2_sp);
                strcpy(E5Linha_sc, E5Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E5Linha_s, E5Linha_h);
        strcpy(E5Linha_sp, E5Linha_hp);
        strcpy(E5Linha_sc, E5Linha_hc);
        return 1;
    }
}

int E6(char *E6_tp, char *E6_p, char *E6_c) {
    char E7_tp[10], E7_p[10], E7_c[MAX_COD];
    char E6Linha_h[10], E6Linha_s[10], E6Linha_hp[10], E6Linha_sp[10], E6Linha_hc[MAX_COD], E6Linha_sc[MAX_COD];

    if (E7(E7_tp, E7_p, E7_c)) {
        strcpy(E6Linha_h, E7_tp);
        strcpy(E6Linha_hp, E7_p);
        strcpy(E6Linha_hc, E7_c);
        if (E6Linha(E6Linha_h, E6Linha_s, E6Linha_hp, E6Linha_sp, E6Linha_hc, E6Linha_sc)) {
            strcpy(E6_tp, E6Linha_s);
            strcpy(E6_p, E6Linha_sp);
            strcpy(E6_c, E6Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E6Linha(char *E6Linha_h, char *E6Linha_s, char *E6Linha_hp, char *E6Linha_sp, char *E6Linha_hc, char *E6Linha_sc) {
    char E7_tp[10], E7_p[10], E7_c[MAX_COD];
    char E6Linha2_h[10], E6Linha2_s[10], E6Linha2_hp[10], E6Linha2_sp[10], E6Linha2_hc[MAX_COD], E6Linha2_sc[MAX_COD];

    if (token == TK_XOR) {
        leToken();
        if (E7(E7_tp, E7_p, E7_c)) {
            strcpy(E6Linha2_h, "int");
            if (E6Linha(E6Linha2_h, E6Linha2_s, E6Linha2_hp, E6Linha2_sp, E6Linha2_hc, E6Linha2_sc)) {
                strcpy(E6Linha_s, E6Linha2_s);
                strcpy(E6Linha_sp, E6Linha2_sp);
                strcpy(E6Linha_sc, E6Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E6Linha_s, E6Linha_h);
        strcpy(E6Linha_sp, E6Linha_hp);
        strcpy(E6Linha_sc, E6Linha_hc);
        return 1;
    }
}

int E7(char *E7_tp, char *E7_p, char *E7_c) {
    char E8_tp[10], E8_p[10], E8_c[MAX_COD];
    char E7Linha_h[10], E7Linha_s[10], E7Linha_hp[10], E7Linha_sp[10], E7Linha_hc[MAX_COD], E7Linha_sc[MAX_COD];

    if (E8(E8_tp, E8_p, E8_c)) {
        strcpy(E7Linha_h, E8_tp);
        strcpy(E7Linha_hp, E8_p);
        strcpy(E7Linha_hc, E8_c);
        if (E7Linha(E7Linha_h, E7Linha_s, E7Linha_hp, E7Linha_sp, E7Linha_hc, E7Linha_sc)) {
            strcpy(E7_tp, E7Linha_s);
            strcpy(E7_p, E7Linha_sp);
            strcpy(E7_c, E7Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E7Linha(char *E7Linha_h, char *E7Linha_s, char *E7Linha_hp, char *E7Linha_sp, char *E7Linha_hc, char *E7Linha_sc) {
    char E8_tp[10], E8_p[10], E8_c[MAX_COD];
    char E7Linha2_h[10], E7Linha2_s[10], E7Linha2_hp[10], E7Linha2_sp[10], E7Linha2_hc[MAX_COD], E7Linha2_sc[MAX_COD];

    if (token == TK_ELogico) {
        leToken();
        if (E8(E8_tp, E8_p, E8_c)) {
            strcpy(E7Linha2_h, "int");
            if (E7Linha(E7Linha2_h, E7Linha2_s, E7Linha2_hp, E7Linha2_sp, E7Linha2_hc, E7Linha2_sc)) {
                strcpy(E7Linha_s, E7Linha2_s);
                strcpy(E7Linha_sp, E7Linha2_sp);
                strcpy(E7Linha_sc, E7Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E7Linha_s, E7Linha_h);
        strcpy(E7Linha_sp, E7Linha_hp);
        strcpy(E7Linha_sc, E7Linha_hc);
        return 1;
    }
}

int E8(char *E8_tp, char *E8_p, char *E8_c) {
    char E9_tp[10], E9_p[10], E9_c[MAX_COD];
    char E8Linha_h[10], E8Linha_s[10], E8Linha_hp[10], E8Linha_sp[10], E8Linha_hc[MAX_COD], E8Linha_sc[MAX_COD];

    if (E9(E9_tp, E9_p, E9_c)) {
        strcpy(E8Linha_h, E9_tp);
        strcpy(E8Linha_hp, E9_p);
        strcpy(E8Linha_hc, E9_c);
        if (E8Linha(E8Linha_h, E8Linha_s, E8Linha_hp, E8Linha_sp, E8Linha_hc, E8Linha_sc)) {
            strcpy(E8_tp, E8Linha_s);
            strcpy(E8_p, E8Linha_sp);
            strcpy(E8_c, E8Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E8Linha(char *E8Linha_h, char *E8Linha_s, char *E8Linha_hp, char *E8Linha_sp, char *E8Linha_hc, char *E8Linha_sc) {
    char E9_tp[10], E9_p[10], E9_c[MAX_COD];
    char E8Linha2_h[10], E8Linha2_s[10], E8Linha2_hp[10], E8Linha2_sp[10], E8Linha2_hc[MAX_COD], E8Linha2_sc[MAX_COD];

    if (token == TK_ComparadorIgual) {
        leToken();
        if (E9(E9_tp, E9_p, E9_c)) {
            strcpy(E8Linha2_h, "int");
            if (E8Linha(E8Linha2_h, E8Linha2_s, E8Linha2_hp, E8Linha2_sp, E8Linha2_hc, E8Linha2_sc)) {
                strcpy(E8Linha_s, E8Linha2_s);
                strcpy(E8Linha_sp, E8Linha2_sp);
                strcpy(E8Linha_sc, E8Linha2_sc);
                return 1;
            } else return 0;
        }
        else return 0;
    } else if (token == TK_ComparadorDiferente) {
        leToken();
        if (E9(E9_tp, E9_p, E9_c)) {
            strcpy(E8Linha2_h, "int");
            if (E8Linha(E8Linha2_h, E8Linha2_s, E8Linha2_hp, E8Linha2_sp, E8Linha2_hc, E8Linha2_sc)) {
                strcpy(E8Linha_s, E8Linha2_s);
                strcpy(E8Linha_sp, E8Linha2_sp);
                strcpy(E8Linha_sc, E8Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E8Linha_s, E8Linha_h);
        strcpy(E8Linha_sp, E8Linha_hp);
        strcpy(E8Linha_sc, E8Linha_hc);
        return 1;
    }
}

int E9(char *E9_tp, char *E9_p, char *E9_c) {
    char E10_tp[10], E10_p[10], E10_c[MAX_COD];
    char E9Linha_h[10], E9Linha_s[10], E9Linha_hp[10], E9Linha_sp[10], E9Linha_hc[MAX_COD], E9Linha_sc[MAX_COD];

    if (E10(E10_tp, E10_p, E10_c)) {
        strcpy(E9Linha_h, E10_tp);
        strcpy(E9Linha_hp, E10_p);
        strcpy(E9Linha_hc, E10_c);
        if (E9Linha(E9Linha_h, E9Linha_s, E9Linha_hp, E9Linha_sp, E9Linha_hc, E9Linha_sc)) {
            strcpy(E9_tp, E9Linha_s);
            strcpy(E9_p, E9Linha_sp);
            strcpy(E9_c, E9Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E9Linha(char *E9Linha_h, char *E9Linha_s, char *E9Linha_hp, char *E9Linha_sp, char *E9Linha_hc, char *E9Linha_sc) {
    char E10_tp[10], E10_p[10], E10_c[MAX_COD];
    char E9Linha2_h[10], E9Linha2_s[10], E9Linha2_hp[10], E9Linha2_sp[10], E9Linha2_hc[MAX_COD], E9Linha2_sc[MAX_COD];

    if (token == TK_Menor) {
        leToken();
        if (E10(E10_tp, E10_p, E10_c)) {
            strcpy(E9Linha2_h, "int");
            if (E9Linha(E9Linha2_h, E9Linha2_s, E9Linha2_hp, E9Linha2_sp, E9Linha2_hc, E9Linha2_sc)) {
                strcpy(E9Linha_s, E9Linha2_s);
                strcpy(E9Linha_sp, E9Linha2_sp);
                strcpy(E9Linha_sc, E9Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else if (token == TK_Maior) {
        leToken();
        if (E10(E10_tp, E10_p, E10_c)) {
            strcpy(E9Linha2_h, "int");
            if (E9Linha(E9Linha2_h, E9Linha2_s, E9Linha2_hp, E9Linha2_sp, E9Linha2_hc, E9Linha2_sc)) {
                strcpy(E9Linha_s, E9Linha2_s);
                strcpy(E9Linha_sp, E9Linha2_sp);
                strcpy(E9Linha_sc, E9Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else if (token == TK_ComparadorMenorIgual) {
        leToken();
        if (E10(E10_tp, E10_p, E10_c)) {
            strcpy(E9Linha2_h, "int");
            if (E9Linha(E9Linha2_h, E9Linha2_s, E9Linha2_hp, E9Linha2_sp, E9Linha2_hc, E9Linha2_sc)) {
                strcpy(E9Linha_s, E9Linha2_s);
                strcpy(E9Linha_sp, E9Linha2_sp);
                strcpy(E9Linha_sc, E9Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else if (token == TK_ComparadorMaiorIgual) {
        leToken();
        if (E10(E10_tp, E10_p, E10_c)) {
            strcpy(E9Linha2_h, "int");
            if (E9Linha(E9Linha2_h, E9Linha2_s, E9Linha2_hp, E9Linha2_sp, E9Linha2_hc, E9Linha2_sc)) {
                strcpy(E9Linha_s, E9Linha2_s);
                strcpy(E9Linha_sp, E9Linha2_sp);
                strcpy(E9Linha_sc, E9Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E9Linha_s, E9Linha_h);
        strcpy(E9Linha_sp, E9Linha_hp);
        strcpy(E9Linha_sc, E9Linha_hc);
        return 1;
    }
}

int E10(char *E10_tp, char *E10_p, char *E10_c) {
    char E11_tp[10], E11_p[10], E11_c[MAX_COD];
    char E10Linha_h[10], E10Linha_s[10], E10Linha_hp[10], E10Linha_sp[10], E10Linha_hc[MAX_COD], E10Linha_sc[MAX_COD];

    if (E11(E11_tp, E11_p, E11_c)) {
        strcpy(E10Linha_h, E11_tp);
        strcpy(E10Linha_hp, E11_p);
        strcpy(E10Linha_hc, E11_c);
        if (E10Linha(E10Linha_h, E10Linha_s, E10Linha_hp, E10Linha_sp, E10Linha_hc, E10Linha_sc)) {
            strcpy(E10_tp, E10Linha_s);
            strcpy(E10_p, E10Linha_sp);
            strcpy(E10_c, E10Linha_sc);
            return 1;
        } else return 0;
    } else return 0;
}

int E10Linha(char *E10Linha_h, char *E10Linha_s, char *E10Linha_hp, char *E10Linha_sp, char *E10Linha_hc, char *E10Linha_sc) {
    char E11_tp[10], E11_p[10], E11_c[MAX_COD];
    char E10Linha2_h[10], E10Linha2_s[10], E10Linha2_hp[10], E10Linha2_sp[10], E10Linha2_hc[MAX_COD], E10Linha2_sc[MAX_COD];

    if (token == TK_ShiftLeft) {
        leToken();
        if (E11(E11_tp, E11_p, E11_c)) {
            strcpy(E10Linha2_h, "int");
            if (E10Linha(E10Linha2_h, E10Linha2_s, E10Linha2_hp, E10Linha2_sp, E10Linha2_hc, E10Linha2_sc)) {
                strcpy(E10Linha_s, E10Linha2_s);
                strcpy(E10Linha_sp, E10Linha2_sp);
                strcpy(E10Linha_sc, E10Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else if (token == TK_ShiftRight) {
        leToken();
        if (E11(E11_tp, E11_p, E11_c)) {
            strcpy(E10Linha2_h, "int");
            if (E10Linha(E10Linha2_h, E10Linha2_s, E10Linha2_hp, E10Linha2_sp, E10Linha2_hc, E10Linha2_sc)) {
                strcpy(E10Linha_s, E10Linha2_s);
                strcpy(E10Linha_sp, E10Linha2_sp);
                strcpy(E10Linha_sc, E10Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else {
        strcpy(E10Linha_s, E10Linha_h);
        strcpy(E10Linha_sp, E10Linha_hp);
        strcpy(E10Linha_sc, E10Linha_hc);
        return 1;
    }
}

int E11(char *E11_tp, char *E11_p, char *E11_c) {
    char E12_tp[10], E12_p[10], E12_c[MAX_COD];
    char E11Linha_h[10], E11Linha_s[10], E11Linha_hp[10], E11Linha_sp[10], E11Linha_hc[MAX_COD], E11Linha_sc[MAX_COD];

    if (E12(E12_tp, E12_p, E12_c)) {
        strcpy(E11Linha_h, E12_tp);
        strcpy(E11Linha_hp, E12_p);
        strcpy(E11Linha_hc, E12_c);
        if (E11Linha(E11Linha_h, E11Linha_s, E11Linha_hp, E11Linha_sp, E11Linha_hc, E11Linha_sc)) {
            strcpy(E11_tp, E11Linha_s);
            strcpy(E11_p, E11Linha_sp);
            strcpy(E11_c, E11Linha_sc);
            return 1;
        }
        else return 0;
    } else return 0;
}

int E11Linha(char *E11Linha_h, char *E11Linha_s, char *E11Linha_hp, char *E11Linha_sp, char *E11Linha_hc, char *E11Linha_sc) {
    char E12_tp[10], E12_p[10], E12_c[MAX_COD];
    char E11Linha2_h[10], E11Linha2_s[10], E11Linha2_hp[10], E11Linha2_sp[10], E11Linha2_hc[MAX_COD], E11Linha2_sc[MAX_COD];

    if (token == TK_Mais) {
        leToken();
        if (E12(E12_tp, E12_p, E12_c)) {
            if(!strcmp(E11Linha_h, "int") && !strcmp(E12_tp, "int")) strcpy(E11Linha2_h, "int");
            else strcpy(E11Linha2_h, "float");
            if (E11Linha(E11Linha2_h, E11Linha2_s, E11Linha2_hp, E11Linha2_sp, E11Linha2_hc, E11Linha2_sc)) {
                strcpy(E11Linha_s, E11Linha2_s);
                strcpy(E11Linha_sp, E11Linha2_sp);
                strcpy(E11Linha_sc, E11Linha2_sc);
                return 1;
            }
            else return 0;
        }
    }
    else if (token == TK_Menos) {
        leToken();
        if (E12(E12_tp, E12_p, E12_c)) {
            if(!strcmp(E11Linha_h, "int") && !strcmp(E12_tp, "int")) strcpy(E11Linha2_h, "int");
            else strcpy(E11Linha2_h, "float");
            if (E11Linha(E11Linha2_h, E11Linha2_s, E11Linha2_hp, E11Linha2_sp, E11Linha2_hc, E11Linha2_sc)) {
                strcpy(E11Linha_s, E11Linha2_s);
                strcpy(E11Linha_sp, E11Linha2_sp);
                strcpy(E11Linha_sc, E11Linha2_sc);
                return 1;
            }
            else return 0;
        }
    }
    else {
        strcpy(E11Linha_s, E11Linha_h);
        strcpy(E11Linha_sp, E11Linha_hp);
        strcpy(E11Linha_sc, E11Linha_hc);
        return 1;
    }
}

int E12(char *E12_tp, char *E12_p, char *E12_c) {
    char E13_tp[10], E13_p[10], E13_c[MAX_COD];
    char E12Linha_h[10], E12Linha_s[10], E12Linha_hp[10], E12Linha_sp[10], E12Linha_hc[MAX_COD], E12Linha_sc[MAX_COD];

    if (E13(E13_tp, E13_p, E13_c)) {
        strcpy(E12Linha_h, E13_tp);
        strcpy(E12Linha_hp, E13_p);
        strcpy(E12Linha_hc, E13_c);

        if (E12Linha(E12Linha_h, E12Linha_s, E12Linha_hp, E12Linha_sp, E12Linha_hc, E12Linha_sc)) {
            strcpy(E12_tp, E12Linha_s);
            strcpy(E12_p, E12Linha_sp);
            strcpy(E12_c, E12Linha_sc);
            return 1;
        }
        else return 0;
    } else return 0;
}

int E12Linha(char *E12Linha_h, char *E12Linha_s, char *E12Linha_hp, char *E12Linha_sp, char *E12Linha_hc, char *E12Linha_sc) {
    char E13_tp[10], E13_p[10], E13_c[MAX_COD];
    char E12Linha2_h[10], E12Linha2_s[10], E12Linha2_hp[10], E12Linha2_sp[10], E12Linha2_hc[MAX_COD], E12Linha2_sc[MAX_COD];

    if (token == TK_Multiplicacao) {
        leToken();
        if (E13(E13_tp, E13_p, E13_c)) {

            if(!strcmp(E12Linha_h, "int") && strcmp(E13_tp, "int")) strcpy(E12Linha2_h, "int");
            else strcpy(E12Linha2_h, "float");
            if (E12Linha(E12Linha2_h, E12Linha2_s, E12Linha2_hp, E12Linha2_sp, E12Linha2_hc, E12Linha2_sc)) {
                strcpy(E12Linha_s, E12Linha2_s);
                strcpy(E12Linha_sp, E12Linha2_sp);
                strcpy(E12Linha_sc, E12Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    } else if (token == TK_Divisao) {
        leToken();
        if (E13(E13_tp, E13_p, E13_c)) {
            if(!strcmp(E12Linha_h, "int") && strcmp(E13_tp, "int")) strcpy(E12Linha2_h, "int");
            else strcpy(E12Linha2_h, "float");
            if (E12Linha(E12Linha2_h, E12Linha2_s, E12Linha2_hp, E12Linha2_sp, E12Linha2_hc, E12Linha2_sc)) {
                strcpy(E12Linha_s, E12Linha2_s);
                strcpy(E12Linha_sp, E12Linha2_sp);
                strcpy(E12Linha_sc, E12Linha2_sc);
                return 1;
            } else return 0;
        } else return 0;
    }
    else if (token == TK_RestoDivisao) {
        leToken();
        if (E13(E13_tp, E13_p, E13_c)) {
            if(!strcmp(E12Linha_h, "int") && !strcmp(E13_tp, "int"))
                strcpy(E12Linha2_h, "int");
            else {
                printf("Erro: operação de resto inválida");
                exit(0);
            }
            if (E12Linha(E12Linha2_h, E12Linha2_s, E12Linha2_hp, E12Linha2_sp, E12Linha2_hc, E12Linha2_sc)) {
                strcpy(E12Linha_s, E12Linha2_s);
                strcpy(E12Linha_sp, E12Linha2_sp);
                strcpy(E12Linha_sc, E12Linha2_sc);
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else {
        strcpy(E12Linha_s, E12Linha_h);
        strcpy(E12Linha_sp, E12Linha_hp);
        strcpy(E12Linha_sc, E12Linha_hc);
        return 1;
    }
}

int E13(char *E13_tp, char *E13_p, char *E13_c) {
    char E14_tp[10], E14_p[10], E14_c[MAX_COD];
    char E13Linha_tp[10], E13Linha_h[10], E13Linha_s[10];

    if (E14(E14_tp, E14_p, E14_c)) {
        if (token == TK_Menos) {
            strcpy(E13Linha_h, E14_tp);
            leToken();
            if (E13(E13Linha_tp, E13Linha_h, E13Linha_s)) {
                strcpy(E13_tp, E13Linha_s);
                return 1;
            }
            else return 0;
        }
        else if (token == TK_MaisMais) {
            strcpy(E13Linha_h, E14_tp);
            leToken();

            strcpy(E13_tp, E13Linha_s);
            return 1;
        }
        else if (token == TK_MenosMenos) {
            strcpy(E13Linha_h, E14_tp);
            leToken();

            strcpy(E13_tp, E13Linha_s);
            return 1;
        }
        else if (token == TK_Negacao) {
            strcpy(E13Linha_h, E14_tp);
            leToken();
            if (E13(E13Linha_tp, E13Linha_h, E13Linha_s)) {
                strcpy(E13_tp, E13Linha_s);
                return 1;
            }
            else return 0;
        }
        else {
            strcpy(E13_tp, E14_tp);
            strcpy(E13_p, E14_p);
            strcpy(E13_c, E14_c);
            return 1;
        }
    }
    return 0;
}

int E14(char *E14_tp, char *E14_p, char *E14_c) {
    char E_tp[10];

    if (token == TK_ConstInt) {
        strcpy(E14_tp, "int");
        leToken();
        return 1;
    }
    else if (token == TK_ConstFloat) {
        strcpy(E14_tp, "float");
        leToken();
        return 1;
    }
    else if (token == TK_Id) {
        consultaTipo(lex, E14_tp, ts);
        if(strcmp(E14_tp, "int") && strcmp(E14_tp, "float")) {
            printf("Erro: Variavel %s nao foi declarada\n", lex);
            exit(0);
        }
        strcpy(E14_p,lex);
        strcpy(E14_c,"");

        leToken();
        if (RE()) return 1;
        else return 0;
    }
    else if (token == TK_AbrePar) {
        char E_p[MAX_COD],E_c[MAX_COD];
        leToken();
        if (E(E_tp, E_p, E_c)) {
            if (token == TK_FechaPar) {
                leToken();
                strcpy(E14_c,E_c);
                strcpy(E14_p,E_p);
                return 1;
            } else return 0;
        } else return 0;
    } else return 0;
}

int RE() {
    if (token == TK_AbrePar) {
        leToken();
        if (LP()) {
            if (token == TK_FechaPar) {
                leToken();
                return 1;
            }
            else {
                printf("Erro: esperava token ')' na linha %d coluna %d\n", linha, coluna);
                return 0;
            }
        } else return 0;
    } else return 1;
}

int main() {
    setbuf(stdout, NULL);
    FILE *fonte;
    ts = NULL;
    char conteudo[20000];
    char lex[20];
    char caracter;
    char arquivo[50];
    int escolha = 0;

    int i = 0;

    printf("-----------------------\n");
    printf("-- Analise semantica --\n");
    printf("-----------------------\n");

    do {
        do {
            printf("1 - Erro_Continue\n");
            printf("2 - Erro_Break\n");
            printf("3 - Erro_Tipo_Incompativel\n");
            printf("4 - Erro_Variavel_Duplicada\n");
            printf("5 - Erro_Variavel_Nao_Declarada\n");
            printf("6 - Teste_Erro\n");
            printf("7 - Teste_Ok\n");
            printf("-----------------------\n");
            scanf("%d", &escolha);
            fflush(stdin);

            if ((escolha < 0) || (escolha > 7))
            {
                printf("Opcao incorreta! \n");
                system("pause");
            }
            switch (escolha)
            {
            case 1:
                strcpy(arquivo,"Erro_Continue.txt");
                escolha = 0;
                break;
            case 2:
                strcpy(arquivo,"Erro_Break.txt");
                escolha = 0;
                break;
            case 3:
                strcpy(arquivo,"Erro_Tipo_Incompativel.txt");
                escolha = 0;
                break;
            case 4:
                strcpy(arquivo,"Erro_Variavel_Duplicada.txt");
                escolha = 0;
                break;
            case 5:
                strcpy(arquivo,"Erro_Variavel_Nao_Declarada.txt");
                escolha = 0;
                break;
            case 6:
                strcpy(arquivo,"Teste_Erro.txt");
                escolha = 0;
                break;
            case 7:
                strcpy(arquivo,"Teste_Ok.txt");
                escolha = 0;
                break;

            }
        } while ((escolha < 0) || (escolha > 7));
    } while (escolha != 0);

    if ((fonte = fopen(arquivo, "r")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    while (1) {
        caracter = fgetc(fonte);
        if (feof(fonte))
            break;
        if (caracter != 9 && caracter != 10 && caracter != 13) {
            conteudo[i++] = caracter;
        }
        else if (caracter == 10) {
            conteudo[i++] = 127;
        }
        else if (caracter == 9) {
            conteudo[i++] = 9;
        }
    }
    conteudo[i] = '\0';

    for (i = 0; i < 1000; i++) {
        TKsParser[i] = -1;
    }

    while ((token = le_token(conteudo, lex)) != -1) {
        coluna = posColuna - subColuna;

        TKsParser[posParser++] = token;
        TKsParser[posParser++] = linha;
        TKsParser[posParser++] = coluna;
        strcpy(TKsParserLex[posParserLex++], lex);
    }

    fclose(fonte);
    posParser = 0;
    posParserLex = 0;
    leToken();

    if (PROGC()) {
        printf("Reconhecimento semantico concluido\n");
        printf("-----------------------\n");
        getchar();
    }
    else {
        printf("Reconhecimento semantico com falhas\n");
        printf("-----------------------\n");
        getchar();
    }

    return 0;
}
