#include <iostream>
#include <cstring>

int main() {
    // 8-(80/((2+3)*4)) = 8-80/(4(2+3))
    const char* expression = "8 80 4 2 3 + * / -";

    
    struct Stack {
        int arr[100];
        int top = 0;
        
        void push(int num) {
            arr[top] = num;
            top++;
        }
        
        int pop() {
           return arr[--top]; 
        }
    };
    
    Stack stack;
    int i = 0;

    while (i < strlen(expression)) {
        char symbol = expression[i];
        if (isalnum(symbol)) {
            // parse full number
            int numberLength = 0;
            while(expression[i] != ' ') {
                i++;
                numberLength++;
            }

            char number[numberLength+1];
            number[numberLength] = '\0';
            for (int j = 0; j < numberLength; j++) {
                number[j] = expression[(i-numberLength)+j];
            }

            stack.push(atoi(number));
            i++;
        } else switch(symbol) {
            default:
                i++;
                break;
            case '+':
                {
                    int a = stack.pop();
                    int b = stack.pop();
                    stack.push(a+b);
                }
                i++;
                break;
            case '*':
                {
                    int a = stack.pop();
                    int b = stack.pop();
                    stack.push(a*b);
                }
                i++;
                break;
            case '/':
                {
                    int a = stack.pop();
                    int b = stack.pop();
                    stack.push(b/a);
                }
                i++;
                break;
            case '-':
                {
                    int a = stack.pop();
                    int b = stack.pop();
                    stack.push(b-a);
                }
                i++;
                break;
        }
    }

    while (stack.top != 0) {
        std::cout << stack.pop() << "\n";
    }
}