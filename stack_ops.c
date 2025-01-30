#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int top;
    char elem[MAX];
} Stack;

typedef struct
{
    int top;
    char elem[MAX][MAX];
} StringStack;

void push(Stack *s, char c)
{
    if (s->top >= (MAX - 1))
    {
        printf("Stack Overflow\n");
        return;
    }
    s->elem[++(s->top)] = c;
}

char pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return 0;
    }
    return s->elem[(s->top)--];
}

char display(Stack *s)
{
    if (s->top == -1)
    {
        return 0;
    }
    return s->elem[s->top];
}

void pushString(StringStack *s, const char *str)
{
    if (s->top >= (MAX - 1))
    {
        printf("Stack Overflow\n");
        return;
    }
    strcpy(s->elem[++(s->top)], str);
}

void popString(StringStack *s, char *str)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        str[0] = '\0';
        return;
    }
    strcpy(str, s->elem[(s->top)--]);
}

int isOperand(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

void infixToPostfix(char *infix, char *postfix)
{
    Stack stack;
    stack.top = -1;
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];
        if (ch == '(')
        {
            push(&stack, ch);
        }
        else if (ch == ')')
        {
            while (display(&stack) != '(' && stack.top != -1)
            {
                postfix[k++] = pop(&stack);
            }
            if (display(&stack) == '(')
            {
                pop(&stack);
            }
        }
        else if (isOperand(ch))
        {
            postfix[k++] = ch;
        }
        else
        {
            while (stack.top != -1 && precedence(ch) <= precedence(display(&stack)))
            {
                postfix[k++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }
    while (stack.top != -1)
    {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0';
}

void infixToPrefix(char *infix, char *prefix)
{
    Stack stack;
    stack.top = -1;
    int i, k = 0;
    int length = strlen(infix);
    char revInfix[MAX];

    for (i = 0; i < length; i++)
    {
        if (infix[i] == '(') revInfix[length - i - 1] = ')';
        else if (infix[i] == ')') revInfix[length - i - 1] = '(';
        else revInfix[length - i - 1] = infix[i];
    }
    revInfix[length] = '\0';

    char reversedPostfix[MAX];
    infixToPostfix(revInfix, reversedPostfix);

    int len = strlen(reversedPostfix);
    for (i = 0; i < len; i++)
    {
        prefix[i] = reversedPostfix[len - i - 1];
    }
    prefix[len] = '\0';
}

void postfixToInfix(const char *postfix, char *infix)
{
    StringStack stack;
    stack.top = -1;

    int length = strlen(postfix);
    char op1[MAX], op2[MAX];

    for (int i = 0; i < length; i++)
    {
        char ch = postfix[i];

        if (ch == ' ' || ch == '\t') continue;

        if (isOperand(ch))
        {
            char operand[2] = {ch, '\0'};
            pushString(&stack, operand);
        }
        else
        {
            popString(&stack, op1);
            popString(&stack, op2);

            infix[0] = '(';
            int pos = 1;
            strcpy(&infix[pos], op2);
            pos += strlen(op2);
            infix[pos++] = ch;
            strcpy(&infix[pos], op1);
            pos += strlen(op1);
            infix[pos++] = ')';
            infix[pos] = '\0';

            pushString(&stack, infix);
        }
    }

    popString(&stack, infix);
}

void postfixToPrefix(const char *postfix, char *prefix)
{
    StringStack stack;
    stack.top = -1;

    int length = strlen(postfix);
    char op1[MAX], op2[MAX];

    for (int i = 0; i < length; i++)
    {
        char ch = postfix[i];

        if (ch == ' ' || ch == '\t') continue;

        if (isOperand(ch))
        {
            char operand[2] = {ch, '\0'};
            pushString(&stack, operand);
        }
        else
        {
            popString(&stack, op1);
            popString(&stack, op2);

            int pos = 0;
            prefix[pos++] = ch;
            strcpy(&prefix[pos], op2);
            pos += strlen(op2);
            strcpy(&prefix[pos], op1);
            pos += strlen(op1);
            prefix[pos] = '\0';

            pushString(&stack, prefix);
        }
    }

    popString(&stack, prefix);
}

void prefixToInfix(const char *prefix, char *infix)
{
    StringStack stack;
    stack.top = -1;

    int length = strlen(prefix);
    char op1[MAX], op2[MAX];

    for (int i = length - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (ch == ' ' || ch == '\t') continue;

        if (isOperand(ch))
        {
            char operand[2] = {ch, '\0'};
            pushString(&stack, operand);
        }
        else
        {
            popString(&stack, op1);
            popString(&stack, op2);

            infix[0] = '(';
            int pos = 1;
            strcpy(&infix[pos], op1);
            pos += strlen(op1);
            infix[pos++] = ch;
            strcpy(&infix[pos], op2);
            pos += strlen(op2);
            infix[pos++] = ')';
            infix[pos] = '\0';

            pushString(&stack, infix);
        }
    }

    popString(&stack, infix);
}

void prefixToPostfix(const char *prefix, char *postfix)
{
    StringStack stack;
    stack.top = -1;

    int length = strlen(prefix);
    char op1[MAX], op2[MAX];

    for (int i = length - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (ch == ' ' || ch == '\t') continue;

        if (isOperand(ch))
        {
            char operand[2] = {ch, '\0'};
            pushString(&stack, operand);
        }
        else
        {
            popString(&stack, op1);
            popString(&stack, op2);

            int pos = 0;
            strcpy(&postfix[pos], op1);
            pos += strlen(op1);
            strcpy(&postfix[pos], op2);
            pos += strlen(op2);
            postfix[pos++] = ch;
            postfix[pos] = '\0';

            pushString(&stack, postfix);
        }
    }

    popString(&stack, postfix);
}

int main()
{
    char infix[MAX];
    char postfix[MAX];
    char prefix[MAX];
    char result[MAX];

    int choice;
    do
    {
        printf("Choose an option:\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Convert Infix to Prefix\n");
        printf("3. Convert Postfix to Infix\n");
        printf("4. Convert Postfix to Prefix\n");
        printf("5. Convert Prefix to Infix\n");
        printf("6. Convert Prefix to Postfix\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        // Clear input buffer after reading choice
        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
                printf("Enter the infix expression: ");
                if (fgets(infix, sizeof(infix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                size_t len = strlen(infix);
                if (len > 0 && infix[len - 1] == '\n')
                {
                    infix[len - 1] = '\0';
                }
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 2:
                printf("Enter the infix expression: ");
                if (fgets(infix, sizeof(infix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                len = strlen(infix);
                if (len > 0 && infix[len - 1] == '\n')
                {
                    infix[len - 1] = '\0';
                }
                infixToPrefix(infix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;

            case 3:
                printf("Enter the postfix expression: ");
                if (fgets(postfix, sizeof(postfix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                len = strlen(postfix);
                if (len > 0 && postfix[len - 1] == '\n')
                {
                    postfix[len - 1] = '\0';
                }
                postfixToInfix(postfix, result);
                printf("Infix Expression: %s\n", result);
                break;

            case 4:
                printf("Enter the postfix expression: ");
                if (fgets(postfix, sizeof(postfix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                len = strlen(postfix);
                if (len > 0 && postfix[len - 1] == '\n')
                {
                    postfix[len - 1] = '\0';
                }
                postfixToPrefix(postfix, result);
                printf("Prefix Expression: %s\n", result);
                break;

            case 5:
                printf("Enter the prefix expression: ");
                if (fgets(prefix, sizeof(prefix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                len = strlen(prefix);
                if (len > 0 && prefix[len - 1] == '\n')
                {
                    prefix[len - 1] = '\0';
                }
                prefixToInfix(prefix, result);
                printf("Infix Expression: %s\n", result);
                break;

            case 6:
                printf("Enter the prefix expression: ");
                if (fgets(prefix, sizeof(prefix), stdin) == NULL)
                {
                    printf("Error reading input\n");
                    return 1;
                }
                len = strlen(prefix);
                if (len > 0 && prefix[len - 1] == '\n')
                {
                    prefix[len - 1] = '\0';
                }
                prefixToPostfix(prefix, result);
                printf("Postfix Expression: %s\n", result);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
