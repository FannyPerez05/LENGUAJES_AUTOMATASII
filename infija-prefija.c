#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

/* Obtiene la prioridad de los operadores */
int prioridad(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}

/* Comprueba si el caracter es un operador */
int es_operador(char c) {
    return c == '+' || c == '-' ||
           c == '*' || c == '/' || c == '^';
}

/* Comprueba si es un operando */
int es_operando(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

/* Invierte la expresion y cambia los parentesis */
void invertir(char origen[], char destino[]) {
    int i;
    int n = strlen(origen);

    for (i = 0; i < n; i++) {
        char c = origen[n - 1 - i];

        if (c == '(')
            destino[i] = ')';
        else if (c == ')')
            destino[i] = '(';
        else
            destino[i] = c;
    }

    destino[n] = '\0';
}

/* Convierte la expresion infija a prefija */
int convertir(char infija[], char prefija[]) {
    char invertida[MAX];
    char postfija[MAX];
    char pila[MAX];

    int tope = -1;
    int j = 0;
    int i;

    invertir(infija, invertida);

    for (i = 0; invertida[i] != '\0'; i++) {
        char c = invertida[i];

        if (isspace((unsigned char)c))
            continue;

        if (es_operando(c)) {
            postfija[j++] = c;
        }
        else if (c == '(') {
            pila[++tope] = c;
        }
        else if (c == ')') {
            while (tope >= 0 && pila[tope] != '(')
                postfija[j++] = pila[tope--];

            if (tope < 0)
                return 0;

            tope--;
        }
        else if (es_operador(c)) {
            while (tope >= 0 && pila[tope] != '(' &&
                   (prioridad(pila[tope]) > prioridad(c) ||
                   (prioridad(pila[tope]) == prioridad(c)
                    && c == '^'))) {
                postfija[j++] = pila[tope--];
            }

            if (tope >= MAX - 1)
                return 0;

            pila[++tope] = c;
        }
        else {
            return 0;
        }

        if (j >= MAX - 1)
            return 0;
    }

    while (tope >= 0) {
        if (pila[tope] == '(')
            return 0;

        postfija[j++] = pila[tope--];
    }

    postfija[j] = '\0';

    invertir(postfija, prefija);

    return 1;
}

/* Lee el archivo linea por linea */
int main(void) {
    FILE *archivo;
    char linea[MAX];
    char prefija[MAX];
    int numero = 0;

    archivo = fopen("expresiones.txt", "r");

    if (archivo == NULL) {
        printf("Error: no se pudo abrir expresiones.txt\n");
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';

        /* Ignora las lineas vacias */
        int i = 0;
        while (isspace((unsigned char)linea[i]))
            i++;

        if (linea[i] == '\0')
            continue;

        numero++;

        printf("\nExpresion %d: %s\n", numero, linea);

        if (convertir(linea, prefija))
            printf("Expresion prefija: %s\n", prefija);
        else
            printf("Error: expresion o parentesis incorrectos.\n");
    }

    if (ferror(archivo))
        printf("Error al leer el archivo.\n");

    fclose(archivo);

    return 0;
}
