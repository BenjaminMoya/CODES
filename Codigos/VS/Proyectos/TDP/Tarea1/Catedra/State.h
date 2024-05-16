#include <iostream>

class State {

  public:
  
    int **board;
    int size;
    int i0; 
    int j0; 
    State *parent;
    State();
    State(int size);
    State(int size, State *parent);
    State(int size, State *parent, int **board);
    bool isSolution(); 
    ~State();
    void print(); 
    void print_board();
    State *up();
    State *down();
    State *left();
    State *right();
    State *copy();
    bool equals(State *s); 

};