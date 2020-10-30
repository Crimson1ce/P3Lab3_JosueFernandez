#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

//Prototipos
int** generarMatriz(int);
void liberarMemoria(int**&, int);
int** adjunta(int**&, int);
int determinante(int**&, int);
int** submatriz(int**&, int, int, int);
int cofactor(int**&, int, int, int);
void transponer(int**&, int);
void calcularInversa(int**&, int, int);

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
            cout << "La dimension de la matriz debe ser por lo menos 2. "
                    "Ingrese de nuevo: ";
            cin >> size;
        }
        //Matriz generada
        
        int** matriz = generarMatriz(size);
        int** adjMatriz = NULL;
        adjMatriz = adjunta(matriz, size);
        
        cout << "La matriz A es: " << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matriz[i][j] << "\t ";
            }
            cout << endl;
        }
        
        
        int determinanteA = determinante(matriz, size);
        cout << endl << "El determinante de la matriz A es: " 
                << determinanteA << endl;
        
        
        cout << endl << "La adjunta de la matriz A es: " << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << adjMatriz[i][j] << "\t ";
            }
            cout << endl;
        }
        
        if(determinanteA)
        {
            calcularInversa(adjMatriz,size,determinanteA);
        }
        else
        {
            cout << endl << "La matriz A no tiene una matriz inversa. Es singular." << endl;
        }

        //Liberar la memoria de las matrices
        liberarMemoria(matriz, size);
        liberarMemoria(adjMatriz, size);

        cout << "---------------------------------------------------" << endl;
        
        //Preguntar por repetición
        do {
            cout << endl << "Desea calcular la inversa de otra matriz? (S=Si / N=No): ";
            cin >> opcion;
        } while (opcion != 'S' && opcion != 's' && opcion != 'N' && opcion != 'n');

        cout << "---------------------------------------------------" << endl;
        
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

/* Calcula la adjunta de una matriz dados la matriz y su tamaño.
 */
int** adjunta(int**& matriz, int size) {
    int** adjMatriz = new int*[size];
    for (int i = 0; i < size; i++) {
        adjMatriz[i] = new int[size];
        for (int j = 0; j < size; j++) {
            adjMatriz[i][j] = cofactor(matriz, size, i, j);
        }
    }
    transponer(adjMatriz, size);
    return adjMatriz;
}

/*Retorna el determinante de una matriz dada la matriz y su dimensión.
 */
int determinante(int**& matriz, int size) {

    if (size <= 0) // Ocurrió un error
    {
        cout << "Error con dimension de la matriz." << endl;
        return 0;
    } 
    else if (size == 1) // Por si acaso
    {
        return matriz[0][0];
    } 
    else if (size == 2) // Caso base
    {
        return (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    }

    //Caso recursivo 
    //a[i][1]A[i][1] + a[i][2]A[i][2] + ... a[i][n]A[i][n]
    int det = 0, i = 0;
    for (int j = 0; j < size; j++) {
        if (matriz[i][j]) {
            det += matriz[i][j] * cofactor(matriz, size, i, j); // Recursión
        }
    }

    return det;
}

/* Calcula la submatriz de un elemento dada la matriz original, el tamaño,
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
    return submatriz;
}

/* Calcula el cofactor de una matriz, dados la matriz, su tamaño, la fila y 
 * la columna del elemento referido.
 */
int cofactor(int**& matriz, int size, int fila, int columna) {
    int signo = (fila + columna) % 2 == 0 ? 1 : -1;
    int** subM = submatriz(matriz, size, fila, columna);
    int calculo = signo * determinante(subM, size - 1);
    liberarMemoria(subM, size - 1);
    return calculo;
}

/* Transpone una matriz por referencia.
 */
void transponer(int**& matriz, int size) {
    if (matriz != NULL) {
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                int value = matriz[i][j];
                matriz[i][j] = matriz[j][i];
                matriz[j][i] = value;
            }
        }
    }
}

int factorComun(int a, int b){
    
    a = a<0 ? -a : a;
    b = b<0 ? -b : b;
    
    int min = a>b ? b : a;
    int factor=1;
    for (int i = 2; i <= min; i++) {
        if(a % i==0 && b % i==0){
            factor = i;
        }
    }
    return factor;
}

void calcularInversa(int**& adjMatriz, int size, int determinant){
    
    cout << endl << "La inversa de la matriz A es: " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(adjMatriz[i][j]%determinant==0)
            {
                cout << setw(8) << adjMatriz[i][j] / determinant << "\t";
            }
            else
            {
                int factor = factorComun(adjMatriz[i][j],determinant);
                int numerador = adjMatriz[i][j]/factor;
                int denominador = determinant/factor;
                cout << setw(4) << (denominador<0 ? -numerador:numerador) << "/" << setw(3) << (denominador<0 ? -denominador:denominador) << "\t";
            }
        }
        cout << endl;
    }
}