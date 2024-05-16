#include <iostream>
#include "Puzzle.h"

Puzzle::Puzzle(){  //Constructor vacio

    check = new DLL();
    generates = new TH();

}

State *Puzzle::read(){  //Lectura del tablero mediante un archivo de texto
    
    std::cout << "Nombre de archivo:";
    std::string filename;
    std::cin >> filename;
    std::cout << "Leyendo archivo " << filename << std::endl;
    std::ifstream file(filename);
    std::cout << std::endl;

    if (!file.is_open()) { //Verifica si se pudo abrir el archivo indicado

        std::cout<<"No se pudo abrir el archivo"<<std::endl;
        return nullptr;

    }

    std::string line;
    std::stringstream ss;
    int num, n=0;

    if(getline(file,line,'\n')){

        ss << line; 

        while(ss >> num) {

            n++;

        }

    }

    file.close();
    int **newBoard;
    newBoard = new int*[n];

    for (int i = 0; i < n; i++) { //Asigna cada elemento del archivo a un tablero incializado

        newBoard[i] = new int[n];

    }

    file.open(filename);

    int j;
    for (int i = 0; i < n; i++) {

        for ( j = 0; j < n; j++) {

            file >> newBoard[i][j];

        }

    } 

    file.close();
    
    State *s = new State(j,nullptr,newBoard); //Crea el estado que contendra el tablero leido
    return s;

}

void Puzzle::generateInitial(State *s){ //Genera el primer estado a revisar 

    if (s->board==nullptr) { //Si no hay tablero no se hace nada

        std::cout << "No se ha cargado el tablero" << std::endl;
        return;

    }

    for (int i=0;i<s->size;i++){ //Busqueda del vacio elemento a elemento
        
        for (int j=0;j<s->size;j++){
            
            if(s->board[i][j]==0){ //Si lo encuentra lo asigna e inserta el estado en la mayor prioridad al ser el primer elemento

                s->i0 = i;
                s->j0 = j;
                std::cout << "Se ha cargado el estado inicial" << std::endl;
                generates->sets[0]->insertFront(s);
                return;

            }

        }

    }

    std::cout << "No hay vacio en el estado inicial" << std::endl; //Si no se encuentra no hay vacio y no se hace nada
    return;
}

void Puzzle::solveNoHeuristic(){ //Resolucion del puzzle sin heuristicas

    clock_t start = clock(); //Medicion temporal
    int states = 1; //Numero de estados revisados
    
    while (!(generates->sets[0]->isEmpty())){ //Revisa si la lista de generados esta vacia, sino entra al ciclo 
        
        State *s = generates->sets[0]->removeFront(); //Remueve el primer elemento de la lista de generados
        std::cout << "Estados revisados: " << states << std::endl;
        if(!(check->find(s))){ //Verifica si no se encun encuentra en la lista de revisados
            
            if(s->isSolution()){ //Si es la solucion de le indica al usuario, se imprime su arbol genealogico (pasos a seguir) y se para el cronometro
                
                std::cout << std::endl;
                std::cout << "Se ha encontrado la solucion" << std::endl;
                std::cout << std::endl;
                s->printParents();
                clock_t end = clock();
                double elapsed = end - start;
                std::cout << "Tiempo transcurrido:" << elapsed << " Milisegundos" << std::endl;
                return;

            } else { //Sino se agrega a la lista de revisados y se generan todos los estados posibles desde el
                
                check->insertFront(s);
                State *sUp = s->up();
                State *sDown = s->down();
                State *sRight = s->right();
                State *sLeft = s->left();

                if (sUp != nullptr && !(check->find(sUp))){ //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                    
                    sUp->parent = s;
                    generates->sets[0]->insertBack(sUp);

                }
                    
                if (sDown != nullptr && !(check->find(sDown))){ //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                    
                    sDown->parent = s;
                    generates->sets[0]->insertBack(sDown);

                }

                if (sRight != nullptr && !(check->find(sRight))){ //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                    
                    sRight->parent = s;
                    generates->sets[0]->insertBack(sRight);
                    
                }

                if (sLeft != nullptr && !(check->find(sLeft))){ //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
    
                    sLeft->parent = s;
                    generates->sets[0]->insertBack(sLeft);

                }

            }
        }

        states++; 

    }

    std::cout << "No hay mas estados generados. No hay solucion" << std::endl;
    clock_t end = clock();
    double elapsed = end - start;
    std::cout << "Tiempo transcurrido:" << elapsed << " Milisegundos" << std::endl;
    
}

void Puzzle::solveHeuristic() { //Resolucion del puzzle con heuristicas

    clock_t start = clock(); //Medicion temporal
    int states = 1; //Numero de estados revisados
    State *s; //Estado en revision
    
    while (!(generates->isEmpty())) { //Revisa si la tabla hash de generados esta vacia, sino entra al ciclo 
        
        
        for(int i=0;i<49;i++){ //Busqueda del mejor estado en la lista no vacia con la prioridad mas alta
            
            if(!(generates->sets[i]->isEmpty())){
                
                s = generates->sets[i]->findBest(); //Asigna el estado encontrado al estado en revision y sale del ciclo for
                break;

            }

        }

        std::cout << "Estados revisados: " << states << std::endl;
        
        if (s->isSolution()) { //Si el estado es solucion se le indica al usuario, se imprime su arbol genealogico (pasos a seguir) y se para el cronometro
            
            std::cout << std::endl;
            std::cout << "Se ha encontrado la solucion" << std::endl;
            std::cout << std::endl;
            s->printParents();
            clock_t end = clock();
            double elapsed = end - start;
            std::cout << "Tiempo transcurrido: " << elapsed << " Milisegundos" << std::endl;
            return;

        } else { //Sino se agrega a la lista de revisados y se generan todos los estados posibles desde el 
            
            check->insertFront(s);
            State *sUp = s->up();
            State *sDown = s->down();
            State *sRight = s->right();
            State *sLeft = s->left();
           
            if (sUp != nullptr && !(check->find(sUp))) { //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                
                sUp->parent = s;
                generates->insert(sUp); //Se inserta en la tabla de generados segun su coeficiente Manhattan para indicar la prioridad de el

            }
                   
            if (sDown != nullptr && !(check->find(sDown))) { //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                
                sDown->parent = s;
                generates->insert(sDown); //Se inserta en la tabla de generados segun su coeficiente Manhattan para indicar la prioridad de el

            }
            
            if (sRight != nullptr && !(check->find(sRight))) { //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                
                sRight->parent = s;
                generates->insert(sRight); //Se inserta en la tabla de generados segun su coeficiente Manhattan para indicar la prioridad de el

            }
            
            if (sLeft != nullptr && !(check->find(sLeft))) { //Si el estado es nulo o esta en la lista de revisados no se agrega a generados
                
                sLeft->parent = s;
                generates->insert(sLeft); //Se inserta en la tabla de generados segun su coeficiente Manhattan para indicar la prioridad de el

            }
        }
        states++;
    }

    std::cout << "No hay mas estados generados. No hay solucion" << std::endl;
    clock_t end = clock();
    double elapsed = end - start;
    std::cout << "Tiempo transcurrido: " << elapsed << " Milisegundos" << std::endl;
}

void Puzzle::menu(){ //Menu de intteraccion del usuario

    std::cout << "Bienvenido al solucionador de rompecabezas" << std::endl;
    std::cout << std::endl;
    std::cout << "1) Cargar tablero desde archivo de texto" << std::endl;
    std::cout << "2) Cargar tablero manualmente" << std::endl;
    std::cout << "3) Salir" << std::endl;
    std::cout << std::endl;
    std::cout << "Digite su opcion: " << std::endl;
    std::cout << std::endl;
    int op1;
    std::cin >> op1;
    std::cout << std::endl;
    if (op1==1){ //Carga mediante archivo de texto del tablero

        State *s = read(); //Lectura del archivo
        std::cout << "1) Resolver sin heuristicas" << std::endl;
        std::cout << "2) Resolver con heuristicas" << std::endl;
        std::cout << "3) Salir" << std::endl;
        std::cout << std::endl;
        std::cout << "Digite su opcion: " << std::endl;
        std::cout << std::endl;
        int op2;
        std::cin >> op2;
        std::cout << std::endl;

        if (op2==1){ //Solucion sin heuristicas

            generateInitial(s);
            solveNoHeuristic();
            return;

        }

        if (op2==2){ //Solucion con heuristicas

            generateInitial(s);
            solveHeuristic();
            return;

        }

        if (op2==3){

            return;

        }
    }

    if (op1==2){ //Se le pide al usuario el tamano del tablero y los elementos en cada posicion

        std::cout << std::endl;
        std::cout << "Size del tablero: " << std::endl;
        int size;
        std::cin >> size;
        std::cout << std::endl;
        State *s = new State(size);
        int number;

        for(int i=0;i<size;i++){

            for(int j=0;j<size;j++){

                    std::cout << std::endl;
                    std::cout << "Posicion" << " " << i << "," << j << ":"<< std::endl;
                    std::cin >> number;
                    s->board[i][j] = number;

            }

        }

        std::cout << "1) Resolver sin heuristicas" << std::endl;
        std::cout << "2) Resolver con heuristicas" << std::endl;
        std::cout << "3) Salir" << std::endl;
        std::cout << std::endl;
        std::cout << "Digite su opcion: " << std::endl;
        std::cout << std::endl;
        int op3;
        std::cin >> op3;
        std::cout << std::endl;

        if (op3==1){ //Solucion sin heuristicas

            generateInitial(s);
            solveNoHeuristic();
            return;

        }

        if (op3==2){ //Solucion con heuristicas

            generateInitial(s);
            solveHeuristic();
            return;
            
        }

        if (op3==3){

            return;

        }

    }

    if (op1==3){

        return;

    }

}