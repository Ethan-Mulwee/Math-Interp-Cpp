#include <iostream>
#include <cstring>

int main() {
    // 8-(80/((2+3)*4)) = 8-80/(4(2+3))
    const char* input = "8 80 4 2 3 + * / -";

    
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

    while (i < strlen(input)) {
        char symbol = input[i];
        if (isalnum(symbol)) {
            int numberLength = 0;
            while(input[i] != ' ') {
                i++;
                numberLength++;
            }

            char number[numberLength];
            number[numberLength] = '\0';
            for (int j = 0; j < numberLength; j++) {
                number[j] = input[(i-numberLength)+j];
            }

            // std::cout << "pushing number: " << number << "\n";
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