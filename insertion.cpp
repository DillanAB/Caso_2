#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

#define P1 int arr1[1000];\
    int arr2[2000];\
    int arr3[3000];\
    int arr4[4000];\
    int arr5[5000];\
    int arr6[6000];\
    int arr7[7000];\
    int arr8[8000];\
    int arr9[9000];\
    int arr10[10000];\
    vector<float> tams = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};\
    vector<int*> arrays = {arr1,arr2,arr3,arr4,arr5,arr6,arr7,arr8,arr9,arr10};\
    nArr = 10; //Número de arrays a probar.


#define P2 int arr1[10000];\
    int arr2[20000];\
    int arr3[30000];\
    vector<float> tams = {10000,20000,30000};\
    vector<int*> arrays = {arr1,arr2,arr3};\
    nArr = 3;


class Tiempos{
public:
    int total;
    int forIter;
    int whileIter;
    int forAnterior;
    float ticks;
    float ticksAnterior;
    Tiempos(){
        ticks = ticksAnterior = total = forIter = forAnterior = whileIter = 0;
    }
    void reset(){
        total = forIter = whileIter = ticks = 0;
    }
};

void insertionSort(int *arr, int n, Tiempos *T){
    int llave, previo;
    clock_t t1;
    t1 = clock();  
    for(int i = 1; i < n; i++){
        llave = arr[i];
        previo = i-1;
        T->forIter++;
        while(previo >= 0 && arr[previo]>llave){
            arr[previo+1] = arr[previo];
            previo--;
            T->whileIter++;
        }
        arr[previo+1] = llave;
    }
    clock_t t2 = clock() - t1;
    T->ticks = t2;
    T->total = T->forIter + T->whileIter;
    return;
}

int main(){
    cout<< endl;
    int nArr = 0;
    P1
    Tiempos* T = new Tiempos();
    int difForIter;
    float difTicks;
    float difN;

    //Prueba del crecimiento lineal:
    cout << "***********************Prueba del crecimiento lineal***********************" << endl;
    for(int i=0; i<nArr; i++){
        for(int j=0; j <tams[i] ;j++){
            arrays[i][j] = j;
        }
    }
    for(int i = 0; i<arrays.size(); i++){
        insertionSort(arrays[i], tams[i], T);
        cout<< endl;
        cout <<"Iteraciones del for: " << T->forIter << endl;
        cout <<"Iteraciones del while: " << T->whileIter << endl;
        if(i>0){
            difN = (tams[i])-(tams[i-1]);
            difForIter = T->forIter-T->forAnterior;
            cout <<"n = "<<tams[i] << " | n anterior = "<<tams[i-1]<<endl;
            cout <<"Iteraciones = "<<T->forIter<<" | Iteraciones del anterior = "<<T->forAnterior<<endl;
            cout <<"Diferencia entre n's: "<<tams[i]<<"-"<<tams[i-1]<<" = "<<difN<<endl;
            cout <<difN <<" = " <<difForIter <<endl;
        }
        else{
            cout <<"n = "<<tams[i]<<endl;
        }
        T->forAnterior = T->forIter;
        T->reset();
    }
    cout<<"Las iteraciones del for siempre aumentan en igual cantidad que el aumento en N."<<endl<<endl;


    //Prueba del crecimiento cuadrático:
    int cuadPositivos = 0;
    cout<< "***********************Prueba del crecimiento cuadratico***********************" << endl;
    cout<<"Se va a revisar que el crecimiento de los ticks sea proporcional al crecimiento de n^2."<<endl;
    cout<<"Margen de error: 15% (0.15)"<<endl;
    int val = 1;
    for(int i=0; i<nArr; i++){
        for(int j=tams[i]-1; j>=0; j--){
            arrays[i][j] = val;
            val++;
        }
        val = 1;
    }

    for(int i = 0; i<arrays.size(); i++){
        insertionSort(arrays[i], tams[i], T);
        cout<< endl;
        if(i>0){
            difN = (tams[i]*tams[i])/(tams[i-1]*tams[i-1]);
            difTicks = T->ticks/T->ticksAnterior;
            cout <<"n = "<<tams[i] << " | n anterior = "<<tams[i-1]<<endl;
            cout <<"Ticks = "<<T->ticks<<" | Ticks del anterior = "<<T->ticksAnterior<<endl;
            cout <<"Crecimiento entre n's al cuadrado: "<<tams[i]<<"^2 / "<<tams[i-1]<<"^2 = "<<difN<<endl;
            cout <<"Crecimiento entre ticks: "<<T->ticks << "/" << T->ticksAnterior<< " = " << difTicks <<endl;
            if(abs(difN-difTicks)<0.15){
                cout <<difN <<" ~ " <<difTicks<<"  | Dentro del margen de error"<<endl;
                cuadPositivos++;
            }else{
            cout <<difN <<" ~ " <<difTicks<<"  | Fuera del margen de error"<<endl;
            }
        }
        else{
            cout <<"n = "<<tams[i]<<endl;
            cout <<"Ticks: " << (T->ticks) << endl;
        }
        T->ticksAnterior = T->ticks;
        T->reset();
    }
    cout<<"De "<<nArr-1<<", "<<cuadPositivos<<" tuvieron un crecimiento proporcional entre ticks y N dentro del margen de error."<<endl;
    //Cuenta uno menos porque se empiezan a comparar desde el segundo.
    cout<<endl;
    return 0;
}