#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
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
    int nArr = 10; //Número de arrays a probar.

class Tiempos{
public:
    int total;
    int forIter;
    int whileIter;
    Tiempos(){
        total = forIter = whileIter = 0;
    }
    void reset(){
        total = forIter = whileIter = 0;
    }
};

void cambiar(int arr[], int k, int j){
    int copia = arr[k];
    arr[k] = arr[j];
    arr[j] = copia;
    return;
}

//0=min, 1=mitad, 2=Aleatorio
int particionar(int arr[], int iMin, int iMax, int tipoPivote) {
    int iPivote;
    if(tipoPivote==0)
        iPivote = iMin;
    if(tipoPivote==1)
        iPivote = iMax/2;
    if(tipoPivote==2)
        iPivote = iMin + rand() % ((iMax+1)-iMin);
    
    int k = iMin;
    int j = k+1;
    while (j<=iMax) {
        if (arr[j]<arr[iPivote] ) {
            k++;
            cambiar(arr,k, j);
        }
        j++;
    }
    cambiar(arr, k, iPivote);
 return k;
}

void quicksort(int arr[], int iMin, int iMax, int tipoPivote, Tiempos* t) {
    int cant= 0;
    for(int i=0; i < iMax - iMin; i++){
        cant++;
    }
    if (iMin>=iMax)
        return;
    int k = particionar(arr, iMin, iMax, tipoPivote);
    quicksort(arr, iMin, k-1, tipoPivote, t);
    quicksort(arr, k+1, iMax, tipoPivote, t);
}

int main(){
    P1
    Tiempos * T = new Tiempos();
    float ticksAnterior;
    float difTicks;
    float difN;
    clock_t t1;
    clock_t t2;
    vector<float> ticksCuad;


    cout<<"**********************Quicksort logaritmico**********************"<<endl;
    for(int i=0; i<nArr; i++){
        int mitad = (tams[i]/2)+1;
        bool par = true;
        arrays[i][mitad] = mitad;
        for(int j=1; j < mitad ;j++){
            if(par){
                arrays[i][mitad+j] = mitad-j;
                arrays[i][mitad-j] = mitad+j;
            }else{
                arrays[i][mitad-j] = mitad-j;
                arrays[i][mitad+j] = mitad+j;
            }
        }
    }
    int linealPositivos = 0;
    for(int i = 0; i<tams.size(); i++){
        t1 = clock();
        quicksort(arrays[i], 0, tams[i], 1, T);
        t2 = clock()-t1;
        cout<< endl;
        if(i>0){
            difN = (tams[i]*log2(tams[i]))/(tams[i-1]*log2(tams[i-1]));
            //difN = (log(tams[i]))/(log(tams[i-1]));
            difTicks = t2/ticksAnterior;
            cout <<"n = "<<tams[i] << " | n anterior = "<<tams[i-1]<<endl;
            cout <<"Ticks = "<<t2<<" | Ticks del anterior = "<<ticksAnterior<<endl;
            cout <<"Crecimiento entre n's : "<<tams[i]<<"*log("<<tams[i]<<") / "<<tams[i-1]<<"*log("<<tams[i-1]<<") * "<<tams[i]<<" = "<<difN<<endl;
            cout <<"Crecimiento entre ticks: "<<t2<< "/" <<ticksAnterior<< " = " <<difTicks<<endl;
            if(abs(difN-difTicks)<0.20){
                cout <<difN <<" ~ " <<difTicks<<"  | Dentro del margen de error"<<endl;
                linealPositivos++;
            }else{
                cout <<difN <<" ~ " <<difTicks<<"  | Fuera del margen de error"<<endl;
            }
        }
        else{
            cout <<"n = "<<tams[i]<<endl;
            cout <<"Ticks: " << t2 << endl;
        }
        ticksAnterior = t2;
    }
    cout<<"De "<<nArr-1<<", "<<linealPositivos<<" tuvieron un crecimiento proporcional entre ticks y N dentro del margen de error."<<endl;
    


    //**********************Quicksort cuadratico**********************
    for(int i=0; i<nArr; i++){
        for(int j=1; j <tams[i] ;j++){
            arrays[i][j] = j;
        }
    }
    cout<<"**********************Quicksort cuadratico**********************"<<endl;
    int cuadPositivos = 0;
    for(int i = 0; i<arrays.size(); i++){
        t1 = clock();
        quicksort(arrays[i], 0, tams[i], 0, T);
        t2 = clock()-t1;
        cout<< endl;
        if(i>0){
            difN = (tams[i]*tams[i])/(tams[i-1]*tams[i-1]);
            difTicks =t2/ticksAnterior;
            cout <<"n = "<<tams[i] << " | n anterior = "<<tams[i-1]<<endl;
            cout <<"Ticks = "<<t2<<" | Ticks del anterior = "<<ticksAnterior<<endl;
            cout <<"Crecimiento entre n's al cuadrado: "<<tams[i]<<"^2 / "<<tams[i-1]<<"^2 = "<<difN<<endl;
            cout <<"Crecimiento entre ticks: "<<t2<< "/" <<ticksAnterior<< " = " <<difTicks<<endl;
            if(abs(difN-difTicks)<0.15){
                cout <<difN <<" ~ " <<difTicks<<"  | Dentro del margen de error"<<endl;
                cuadPositivos++;
            }else{
                cout <<difN <<" ~ " <<difTicks<<"  | Fuera del margen de error"<<endl;
            }
        }
        else{
            cout <<"n = "<<tams[i]<<endl;
            cout <<"Ticks: " << t2 << endl;
        }
        ticksAnterior = t2;
        ticksCuad.push_back(t2);
    }
    cout<<"De "<<nArr-1<<", "<<cuadPositivos<<" tuvieron un crecimiento proporcional entre ticks y N dentro del margen de error."<<endl;
    //Cuenta uno menos porque se empiezan a comparar desde el segundo.
    cout<<endl;

    //**********************Pivote fijo y aleatorio**********************
    cout<<"**********************Pivote fijo y aleatorio**********************"<<endl;
    vector<float> ticksAleatorio;
    for(int i=0;i<10;i++){
        t1 = clock();
        quicksort(arrays[i], 0, tams[i], 2, T);
        t2 = clock()-t1;
        ticksAleatorio.push_back(t2);
    }
    cout<<"Comparacion entre los ticks con pivote fijo y aleatorio: "<<endl;
    for(int i=0;i<10;i++){
        cout<<"N: "<<tams[i]<<"  Fijo: "<<ticksCuad[i]<<" | Aleatorio: "<<ticksAleatorio[i]<<endl;
    }
    
    return 0;
}