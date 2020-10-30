#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

//Prototipos
int** generarMatriz(int);
void liberarMemoria(int**&, int);
int** adjunta(int**&, int);
int determinante(int**&, int);
int** submatriz(int**&, int, int, int);
int cofactor(int**&, int, int, int);

int main(int argc, char** argv) {

    srand(time(0));
    char opcion = 'S';
    int size = 2;
    do {
        //Pedir tamaño de la matriz
        cout << endl << "Ingrese la dimension de la matriz A: ";
        cin >> size;

        //Validar el tamaño ingresado
        while (size < 2) {
            cout << "La dimension de la matriz debe ser por lo menos 2. Ingrese de nuevo: ";
            cin >> size;
        }

        //Matriz generada
        int** matriz = generarMatriz(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matriz[i][j] << "  ";
            }
            cout << endl;
        }


        cout << endl << "El determinante de la matriz es: " << determinante(matriz, size) << endl;

        //Liberar la memoria de la matriz
        liberarMemoria(matriz, size);

        //Preguntar por repetición
        do {
            cout << endl << "Desea calcular la inversa de otra matriz? (S=Si / N=No): ";
            cin >> opcion;
        } while (opcion!='S' && opcion!='s' && opcion!='N' && opcion!='n');
        
    } while (opcion == 'S' || opcion == 's');

    cout << endl << "Nos vemos!";

    return 0;
}

/* Recibe un entero n y retorna una matriz de n x n con números entre -9 y 9.
 */
int** generarMatriz(int n) {
    int** matriz = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 19 - 9;
        }
    }
    return matriz;
}

/* Recibe un apuntador de apuntadores (matriz) de enteros con su tamaño 
 * y libera la memoria.
 */
void liberarMemoria(int**& matriz, int size) {
    if (matriz != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            if (matriz[i] != NULL) {
                delete [] matriz[i];
                matriz[i] = NULL;
            }
        }
        delete [] matriz;
        matriz = NULL;
    }
}

int** adjunta(int**& matriz, int size) {
    return NULL;
}

/*Retorna el determinante de una matriz dada la matriz y su dimensión.
 */
int determinante(int**& matriz, int size) {

    if (size < 2) // Ocurrió un error
    {
        cout << "Error con dimension de la matriz.";
        return 0;
    } else if (size == 2) // Caso base
    {
        return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    }
    //    cout << endl << numero++ << endl;
    //Caso recursivo
    // a[i][1]A[i][1] + a[i][2]A[i][2] + ... a[i][n]A[i][n]
    int det = 0, i = 0;
    for (int j = 0; j < size; j++) {
        int** subM = submatriz(matriz, size, i, j);
        // Recursión
        //        cout << endl << "    " << numero++ << endl;
        if (matriz[i][j]) {
            det += matriz[i][j] * cofactor(subM, size - 1, i, j);
            liberarMemoria(subM, size - 1);
        }
    }

    return det;
}

/* Calcula el cofactor de un elemento dada la matriz original, el tamaño,
 * la fila del elemento (i) y la columna del elemento (j).
 */
int** submatriz(int**& matriz, int size, int fila, int columna) {
    int m = 0, n = 0;

    //Creamos una nueva matriz de orden n-1
    int** submatriz = new int*[size - 1];

    //Inicializamos la nueva matriz
    for (int i = 0; i < size - 1; i++) {
        submatriz[i] = new int[size - 1];

        //Llenamos la nueva matriz
        for (int j = 0; j < size - 1; j++) {
            m = i >= fila ? i + 1 : i;
            n = j >= columna ? j + 1 : j;
            submatriz[i][j] = matriz[m][n];
        }
    }

    //    cout << "Submatriz:" << endl;
    //    for (int i = 0; i < size-1; i++) {
    //        for (int j = 0; j < size-1; j++) {
    //            cout << submatriz[i][j] << "  ";
    //        }
    //        cout << endl;
    //    }

    return submatriz;
}

int cofactor(int**& submatriz, int size, int fila, int columna) {
    int signo = (fila + columna) % 2 == 0 ? 1 : -1;
    return signo * determinante(submatriz, size);
}