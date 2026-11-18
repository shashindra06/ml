#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

void stackInit(CharStack *stack) {
    stack->top = -1;
}

int stackEmpty(CharStack *stack) {
    return stack->top == -1;
}

void stackPush(CharStack *stack, char c) {
    if (stack->top < MAX_SIZE - 1)
        stack->data[++stack->top] = c;
}

char stackPop(CharStack *stack) {
    if (!stackEmpty(stack))
        return stack->data[stack->top--];
    return '\0';
}

char stackPeek(CharStack *stack) {
    if (!stackEmpty(stack))
        return stack->data[stack->top];
    return '\0';
}

int getPrecedence(char op) {
    switch (op) {
        case '/': return 3;
        case '*': return 2;
        case '+': return 1;
        case '-': return 0;
        default: return -1;
    }
}

void convertInfixToPostfix(const char *infix, char *postfix) {
    CharStack operators;
    stackInit(&operators);

    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            stackPush(&operators, ch);
        } else if (ch == ')') {
            while (!stackEmpty(&operators) && stackPeek(&operators) != '(') {
                postfix[j++] = stackPop(&operators);
            }
            if (!stackEmpty(&operators))
                stackPop(&operators);
        } else {  // Operator
            while (!stackEmpty(&operators) && stackPeek(&operators) != '(' &&
                   getPrecedence(stackPeek(&operators)) >= getPrecedence(ch)) {
                postfix[j++] = stackPop(&operators);
            }
            stackPush(&operators, ch);
        }
    }

    while (!stackEmpty(&operators)) {
        postfix[j++] = stackPop(&operators);
    }

    postfix[j] = '\0';
}

int main() {
    char infixExp[MAX_SIZE], postfixExp[MAX_SIZE];
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!inputFile) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    if (!outputFile) {
        printf("Error: Could not create/open output.txt\n");
        fclose(inputFile);
        return 1;
    }

    if (fgets(infixExp, MAX_SIZE, inputFile) == NULL) {
        printf("Error: input.txt is empty or couldn't read\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    // Remove trailing newline
    int len = 0;
    while (infixExp[len] != '\0') {
        if (infixExp[len] == '\n') {
            infixExp[len] = '\0';
            break;
        }
        len++;
    }

    convertInfixToPostfix(infixExp, postfixExp);

    fprintf(outputFile, "%s\n", postfixExp);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
