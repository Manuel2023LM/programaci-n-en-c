#include <stdio.h>
#include <stdlib.h>
#include <math.h>



// funcion 1

float promedio(int v[], int tam ) {

    int suma= 0; 
    
    

    for (int i= 0; i<tam ; i++){
        suma+= v[i];
    
    }


    float prom = (float)suma/tam; 
    
    printf("El promedio del vector es: %.2f\n", prom);
    return prom; 
    
    }


//funcion 2

int suma_multiplo3(int v[], int tam ){
    
    int suma= 0; 
    
    for (int i = 0; i<tam ; i++){
        if( v[i]%3 == 0 ){
            suma+= v[i];
        }
        
        
    }
    
    printf("la suma de los numeros multiplos de 3 es %i", suma);
    
    return suma;
}


// funcion 3
int producto(int v[], int tam ){
    
    int p= 1; 
    
    for(int i= 0 ; i<tam ; i++ ){
        if(v[i]>100 && v[i]%2 == 0){
            p*=v[i]; 
        }
        
        
    }
    
    printf("\nel producto de los numeros mayores a 100 pares es: %i\n ", p);
    
    return p; 
}



//funcion 4

int inicia_7(int m) {

    if(m < 0)
        m = -m;

    while(m >= 10){
        m = m / 10;
    }

    return m == 7;
}






int ultimo_digito5(int m){
    
        return(m%10==5);
        
    
    
}

int cantidad_digito(int m){
    
    if(m/10 == 0 ){
    
    return 1;
    }    
    else {
        return cantidad_digito(m/10)+1 ;
    }
    
}

int digitos3(int m){
    
    
   return (m>99 && m<1000);
    }    



// funcios 5 

int primos(int n ){
    
     
     
      
            if (n== 1){
                return 0;
            } else if (n==2 || n==3 ){
                
                return 1;
            } else   for(int i= 2 ; i<n ; i++ ){
                       if( n%i==0){
                        return 0;
                       } else  return 1 ; 
}
return 0; 
        }

int contador_primos(int v[], int tam){
    
    int primo=0; 
    
    
    
    for(int i= 0 ; i<tam ; i++ ){
        if (primos(v[i])){
            primo++;
            
        }
        
    }
    printf("los primos son: %i", primo);
    
    
    return primo;
    
} 


// funcion 6
int digito_multi3(int m){
    
    return(cantidad_digito(m)%3 == 0);
    
    
    
} 


int sumar_digitos1x1(int m ){
    
    int sum = 0; 
    
    
    if(digito_multi3(m)){
        
      while(m>0){
          
          sum +=  m%10; 
          
        m=   m/10; 
              
          }
          
          return sum;
          
      }  
     return 0;  
    
}


int suma_de_cuadrados(int V[], int tam){
     int m=0;
    
    for(int i=0 ; i<tam ; i++){
        if(V[i]>0){
            m+=pow(V[i],2);
        }
    }
    return m;
    
}   

float raiz_cuadrada(int m){


    return sqrt(m);
    
}






int main(){
   int tam; 
  
   
   printf("ingrese el tamaño del vector\n");
   scanf("%i", &tam); 
   
    int v[tam];
    printf("ingrese %i numeros para el vector\n", tam);
   
   for(int i=0 ; i<tam ; i++){
      printf("ingrese el numero %i de los %i numeros para el vector\n", i+1, tam); 
      scanf("%i", &v[i]); 
   }
 
    
    printf("el vector es\n");
    
    for(int i=0 ; i<tam ; i++){
    printf(" %i ", v[i]); 
       
   }

int opcion; 


do{ 
    
    


    printf("\n ===========   ⭐ *MENU DE OPCIONES* ⭐      ============\n");
    
    
    
    printf("1. Promedio de numeros en un vector  \n");
    printf("2. sumar los numeros multiplos de 3 \n");
    printf("3. producto de los numeros mayores a 100 pares \n");
    printf("4  los numeros que empiezan con 7 terminan en 5 y tienen 3 digitos \n");
    printf("5  la cantidad de numeros primos que hay en el vector \n");
    printf("6  suma de cada digito de un numero con digitos multiplos de 3  \n");
    printf("7   la norma del vector es \n");
    printf("8  el vector es\n");
    printf("9  el vector es\n");
    printf("10  el vector es\n");
    printf("11 el vector es\n");
    printf("12 el vector es\n");
    printf("13 el vector es\n");
    printf("14  el vector es\n");
    printf("15  el vector es\n"); 
    printf("16 SALIR DEL MENU \n"); 
    
     printf(" ingrese una de las opciones (1-16) \n"); 
     scanf("%i", &opcion);  
     
          
    if ( opcion ==1){
        float prom = promedio(v, tam);
     
        
    } else if ( opcion ==2){
        int suma_mul_3= suma_multiplo3( v, tam ); 
        
    }  else if ( opcion ==3){
        int produc= producto(v, tam );
   
    }  else if ( opcion ==4){
        printf("los numeros que empiezan con 7 terminan en 5 y tienen 3 digitos son: \n");
        for(int i=0 ; i<tam ; i++){
      
        if(inicia_7(v[i]) && ultimo_digito5(v[i]) && digitos3(v[i])){
            printf(" %i", v[i]);
        }
        } 
    }  else if ( opcion ==5){
        
        
        int pri= contador_primos(v , tam );
        
       
        
        
    }  else if ( opcion ==6){
        
        
        for(int i=0 ; i<tam ; i++){
        int sumar2= sumar_digitos1x1( v[i]);
        printf("%i - ",sumar2);
        
        }
        
        
    }  else if ( opcion ==7){

        
        int suma_cuadrados= suma_de_cuadrados(v, tam);
        float norma= raiz_cuadrada(suma_cuadrados);
        printf("la norma del vector es: %.2f", norma);
        
    }  else if ( opcion ==8){
        
    }  else if ( opcion ==9){
        
    }  else if ( opcion ==10){
        
    }  else if ( opcion ==11){
        
    }  else if ( opcion ==12){
        
    }  else if ( opcion ==13){
        
    }  else if ( opcion ==14){
        
    }  else if ( opcion ==15){
        
    }  else if ( opcion ==16){
        
    }  else {
        
        printf("opcion invalida por favor escoje otra opcion \n");
    } 
        
       } while ( opcion != 16 ); 
        
        
          
          
          
    


    return 0;
}