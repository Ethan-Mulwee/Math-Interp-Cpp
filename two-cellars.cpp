#include <iostream>
#include <cstring>

template <typename T> struct Stack {
    T arr[255];
    int top = 0;
    
    void push(T num) {
        arr[top] = num;
        top++;
    }
    
    T pop() {
       return arr[--top]; 
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
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == ')' || op == '(');
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
    }
}

int main() {
    const char* expression = "142+20*(40+5*3)+4*79/4-2";

    Stack<int> numberStack;
    Stack<char> operatorStack;

    int i = 0;
    while (i < strlen(expression)) {
        char symbol = expression[i];
        // if is number place in number cellar
        if (isalnum(symbol)) {
            /* NOTE: parseNumber modifies i to be the index of the next char after the number
            I was too lazy to bundle the exit point into a struct */
            int number = parseNumber(expression, i);
            numberStack.push(number);
        }
        // if is operator evaluate operators until either
        else if (isaoperator(symbol)) {
            // The operator cellar is empty
            if (operatorStack.top == 0) {
                operatorStack.push(symbol);
                i++;
            }
            // The top of operator cellar is an open parenthesis
            if (operatorStack.arr[operatorStack.top] == '(') {
                i++;
            }
            i++;
        } else {
            i++;
        }
    }

    // print out number stack at the end
    std::cout << "numberStack: ";
    while (numberStack.top != 1) {
        std::cout << numberStack.pop() << ", ";
    }
    std::cout << numberStack.pop() << "\n";

    // print out operator stack at the ned
    std::cout << "operatorStack: ";
    while (operatorStack.top != 1) {
        std::cout << operatorStack.pop() << ", ";
    }
    std::cout << operatorStack.pop() << "\n";
}