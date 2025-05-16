#include <iostream>
#include <cstring>
#include <string>

template <typename T> struct Stack {
    T arr[255];
    int top = -1;

    void push(T num) {
        top++;
        arr[top] = num;
    }

    T pop() {
       return arr[top--];
    }

    T getTop() {
        return arr[top];
    }
};

int parseNumber(const char* expression, int &expressionPointer) {
    int numberLength = 0;
    int entryPoint = expressionPointer;

    while(isalnum(expression[expressionPointer])) {
        numberLength++;
        expressionPointer++;
    }

    char number[numberLength+1];
    number[numberLength] = '\0';

    for (int i = 0; i < numberLength; i++) {
        number[i] = expression[entryPoint+i];
    }

    return atoi(number);
}

bool isaoperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

int getOperatorPrecedence(char op) {
    switch(op) {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '/':
            return 2;
            break;
        case '*':
            return 2;
            break;
        default:
            return 0;
            break;
    }
}

void evaluateStack(Stack<int> &numberStack, Stack<char> &operatorStack) {
    int a = numberStack.pop();
    int b = numberStack.pop();
    char op = operatorStack.pop();
    switch (op) {
        case '+':
            numberStack.push(a+b);
            break;
        case '-':
            numberStack.push(b-a);
            break;
        case '*':
            numberStack.push(a*b);
            break;
        case '/':
            numberStack.push(b/a);
            break;
    }
}

int evaluate_expression(const char *expression) {
    Stack<int> numberStack;
    Stack<char> operatorStack;

    int i = 0;
    while (i < strlen(expression)) {
        char symbol = expression[i];
        // if is number place in number cellar
        if (isdigit(symbol)) {
            /* NOTE: parseNumber modifies i to be the index of the next char after the number
            I was too lazy to bundle the exit point into a struct */
            int number = parseNumber(expression, i);
            numberStack.push(number);
        }
        // if is operator evaluate operators until either
        else if (isaoperator(symbol)) {
            // The operator cellar is empty
            // The top of operator cellar is an open parenthesis
            // The precedence of the operator at the top of the operator cellar is lower than the precedence of X
            while(!(operatorStack.top == -1 || operatorStack.getTop() == '(' || getOperatorPrecedence(operatorStack.getTop()) < getOperatorPrecedence(symbol))) {
                evaluateStack(numberStack, operatorStack);
            }
            operatorStack.push(symbol);
            i++;
        }
        // If X is an open parenthesis, push X onto the operator cellars
        else if (symbol == '(') {
            operatorStack.push(symbol);
            i++;
        }

        else if (symbol == ')') {
            while (operatorStack.getTop() != '(') {
                evaluateStack(numberStack, operatorStack);
            }
            operatorStack.pop();
            i++;
        }

        else {
            std::cout << "invalid syntax \n";
            return 0;
        }
    }
    while (operatorStack.top != -1) {
        evaluateStack(numberStack, operatorStack);
    }

    return numberStack.pop();
}

int main() {
    const char* expression = "142+20*(40+5*3)+4*79/4-2";

    input:
    std::string test;
    std::cin >> test;
    if (test == "exit") {
        goto exit;
    }

    std::cout << evaluate_expression(test.c_str()) << "\n";
    goto input;

    exit:
    {}
}
