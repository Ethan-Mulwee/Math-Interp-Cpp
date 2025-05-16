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

int main() {
    const char* expression = "142+20*(40+5*3)+4*79/4-2";

    Stack<int> numberStack;
    Stack<char> operatorStack;

    for (int i = 0; i < strlen(expression); i++) {
        char symbol = expression[i];
        if (isalnum(symbol)) {
            
        } 
    }
}