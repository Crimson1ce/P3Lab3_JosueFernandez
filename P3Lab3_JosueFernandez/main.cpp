#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

//Prototipos
int** generarMatriz(int);
void liberarMemoria(int**&, int);

int main(int argc, char** argv) {

    srand(time(0));
    char opcion = 'S';
    int size=2;
    do{
        //Pedir tamaño de la matriz
        cout << endl << "Ingrese la dimension de la matriz A: ";
        cin >> size;
        
        //Validar el tamaño ingresado
        while(size<2){
            cout << "La dimension de la matriz debe ser por lo menos 2. Ingrese de nuevo: ";
            cin >> size;
        }
        
        //Matriz generada
        int** matriz = generarMatriz(size);
        
        
        
        liberarMemoria(matriz, size);
        //Preguntar por repetición
        cout << endl << "Desea calcular la inversa de otra matriz? (S=Si): ";
        cin >> opcion;
    }while(opcion=='S' || opcion=='s');
    
    cout << "Nos vemos!";
    
    return 0;
}

/* Recibe un entero n y retorna una matriz de n x n con números entre -9 y 9.
 */
int** generarMatriz(int n){
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++){
        matriz[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand()%19-9;
        }
    }
    return matriz;
}

/* Recibe un apuntador de apuntadores (matriz) de enteros con su tamaño 
 * y libera la memoria.
 */
void liberarMemoria(int**& matriz, int size){
    if(matriz != NULL && size>0){
        for (int i = 0; i < size; i++) {
            if(matriz[i] != NULL){
                delete [] matriz[i];
                matriz[i] = NULL;
            }
        }
        delete [] matriz;
        matriz = NULL;
    }
}