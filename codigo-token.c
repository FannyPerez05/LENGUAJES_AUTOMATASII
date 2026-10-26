#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int es_digito(char c) {
    return (c >= '0' && c <= '9');
}

int es_palabra_reservada(char *token) {
    if (strcmp(token, "for") == 0 ||
        strcmp(token, "if") == 0 ||
        strcmp(token, "while") == 0 ||
        strcmp(token, "long") == 0 ||
        strcmp(token, "char") == 0 ||
        strcmp(token, "int") == 0 ||
        strcmp(token, "float") == 0 ||
        strcmp(token, "short") == 0) {
        return 1;
    }

    return 0;
}

void clasificar_palabra_reservada(char *token) {
    if (strcmp(token, "long") == 0 ||
        strcmp(token, "char") == 0 ||
        strcmp(token, "int") == 0 ||
        strcmp(token, "float") == 0 ||
        strcmp(token, "short") == 0) {
        printf("Tipo\n");
    }
    else if (strcmp(token, "while") == 0 ||
             strcmp(token, "for") == 0 ||
             strcmp(token, "if") == 0) {
        printf("Instruccion\n");
    }
}

int es_operador(char c) {
    return (c == '+' || c == '-' ||
            c == '*' || c == '/');
}

int es_parentesis(char c) {
    return (c == '(' || c == ')');
}

int es_asignacion(char c) {
    return (c == '=');
}

int es_fin_instruccion(char c) {
    return (c == ';');
}

int token_es_variable(char *token) {
    int i = 0;

    if (token[0] == '\0') {
        return 0;
    }

    if (!isalpha((unsigned char)token[0]) &&
        token[0] != '_') {
        return 0;
    }

    for (i = 1; token[i] != '\0'; i++) {
        if (!isalnum((unsigned char)token[i]) &&
            token[i] != '_') {
            return 0;
        }
    }

    if (es_palabra_reservada(token)) {
        return 0;
    }

    return 1;
}

void print_token(char *token) {
    printf("El token es: %s\n", token);
}

int token_es_numero(char *token) {
    int i = 0;

    if (token[0] == '\0') {
        return 0;
    }

    while (token[i] != '\0') {
        if (!es_digito(token[i])) {
            return 0;
        }

        i++;
    }

    return 1;
}

int token_es_operador(char *token) {
    if (strlen(token) == 1) {
        return es_operador(token[0]);
    }

    return 0;
}

int token_es_parentesis(char *token) {
    if (strlen(token) == 1) {
        return es_parentesis(token[0]);
    }

    return 0;
}

int token_es_asignacion(char *token) {
    if (strlen(token) == 1) {
        return es_asignacion(token[0]);
    }

    return 0;
}

int token_es_fin_instruccion(char *token) {
    if (strlen(token) == 1) {
        return es_fin_instruccion(token[0]);
    }

    return 0;
}

int token_es_palabra_reservada(char *token) {
    return es_palabra_reservada(token);
}

int main() {
    FILE *archivo;
    char buffer[256];
    char *token;

    // Abrir el archivo en modo lectura
    archivo = fopen("leer-archivo.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo leer-archivo.txt\n");
        return 1;
    }

    printf("Contenido y analisis del archivo:\n\n");

    // Leer el archivo linea por linea
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {

        // Separar tokens usando espacios y saltos de linea
        token = strtok(buffer, " \t\r\n");

        while (token != NULL) {

            print_token(token);

            if (token_es_numero(token)) {
                printf("Es un numero\n");
            }
            else if (token_es_operador(token)) {
                printf("Es un operador\n");
            }
            else if (token_es_parentesis(token)) {
                printf("Es un parentesis\n");
            }
            else if (token_es_asignacion(token)) {
                printf("Es una asignacion\n");
            }
            else if (token_es_fin_instruccion(token)) {
                printf("Es un fin de instruccion\n");
            }
            else if (token_es_palabra_reservada(token)) {
                clasificar_palabra_reservada(token);
            }
            else if (token_es_variable(token)) {
                printf("Es una variable\n");
            }
            else {
                printf("Token no valido\n");
            }

            printf("\n");

            token = strtok(NULL, " \t\r\n");
        }
    }

    fclose(archivo);

    return 0;
}
