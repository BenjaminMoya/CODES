#include "Stack.h"

int main() {
    Stack *s = new Stack(10);
    State *s1 = new State(2);
    s->push(s1);
    State *s2 = s->pop();
}