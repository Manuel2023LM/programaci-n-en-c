#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



// Función para verificar si un año es bisiesto
int es_bisiesto(int año) {
    return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
}

// Función para validar fecha en formato "día/mes/año"
int validar_fecha(const char* fecha_str, int* dia, int* mes, int* año) {
    // Intentar parsear la cadena: formato esperado "dd/mm/yyyy"
    if (sscanf(fecha_str, "%d/%d/%d", dia, mes, año) != 3) {
        return 0; // No se pudo parsear correctamente
    }
    
    // Validar rangos básicos
    if (*mes < 1 || *mes > 12 || *dia < 1 || *dia > 31 || *año < 1) {
        return 0;
    }
    
    // Días por mes (enero a diciembre)
    int dias_por_mes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Ajustar febrero si es bisiesto
    if (*mes == 2 && es_bisiesto(*año)) {
        dias_por_mes[2] = 29;
    }
    
    // Verificar que el día no exceda el máximo del mes
    if (*dia > dias_por_mes[*mes]) {
        return 0;
    }
    
    return 1; // Fecha válida
}



// menu de opciones para el usuario


void menu(){
    printf("/////////Libreria: el libro favorito////////\n");
    printf("///////// Menu opciones ////////\n");
    printf("1. Agregar libro\n");
    printf("2. Editar libro\n");
    printf("3. Eliminar libro\n");
    printf("4. Buscar/imprimir libro\n");
    printf("5. vender libro\n");
    printf("6. Editar venta\n");
    printf("7. Eliminar venta \n");
    printf("8. Imprimir Factura\n");
    printf("9. SALIR\n");

}


// definicion de la estructura de datos para el libro


typedef struct libro  {
    char titulo[100];
    char autor[100];
    char genero[50];
    int cantidad_paginas;
    char editorial[100];
    int ISSN; 
    char idioma[50];
    char fecha_publicacion[11];  // Cambiado a 11 para "dd/mm/yyyy" + null
    char estado[50];
    float precio;
    int cantidad_ejemplares;
} libro;








int buscar_libro(int ISSN){
    libro libro;



    return 0;
}

// 1. Agregar libro

void agreagar_libro(){
    libro libro;
    char fecha_input[20];  // Buffer para leer la entrada
    int dia, mes, año;
    
    printf("Titulo: ");
    scanf("%s", libro.titulo);
    printf("Autor: ");
    scanf("%s", libro.autor);
    
    // Leer y validar fecha de publicación

        printf("Fecha de publicación (formato dd/mm/yyyy): ");
        scanf("%s", libro.fecha_publicacion);
    
    
    printf("Genero: ");
    scanf("%s", libro.genero);
    printf("Cantidad de paginas: ");
    scanf("%d", &libro.cantidad_paginas);
    printf("Editorial: ");
    scanf("%s", libro.editorial);

    printf("ISSN: ");
    scanf("%d", &libro.ISSN);
    if(buscar_libro(libro.ISSN) == 0){
        scanf("%d", &libro.ISSN);
    }else{
        printf("El libro ya existe\n");
    }
    

    printf("Idioma: ");
    scanf("%s", libro.idioma);
    printf("Estado nuevo o usado: ");
    scanf("%s", libro.estado);
    printf("Precio: ");
    scanf("%f", &libro.precio);
    printf("Cantidad de ejemplares: ");
    scanf("%d", &libro.cantidad_ejemplares);
    printf("Agregado exitosamente\n");
}





// 2. Editar libro
void editar_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a editar: ");
    scanf("%d", &ISSN);
    

}

// 3. Eliminar libro
void eliminar_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a eliminar: ");
    scanf("%d", &ISSN);
    
}

// 4. Buscar/imprimir libro
void buscar_imprimir_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a buscar: ");
    scanf("%d", &ISSN);
    
}

// 5. vender libro

typedef struct comprador{
    char nombre[100];
    int telefono;
    int documento_identidad;
}comprador;

void vender_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a vender: ");
    scanf("%d", &ISSN);
    
}








// 6. Editar venta

// 7. Eliminar venta

// 8. Imprimir Factura


int main(){
    int opcion = 0;

    while(opcion != 9){
        menu();
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("Agregar libro\n");
                agreagar_libro();
                break;
            case 2:
                printf("Editar libro\n");
                editar_libro();
                break;
            case 3:
                printf("Eliminar libro\n");
                eliminar_libro();
                break;
            case 4:
                printf("Buscar/imprimir libro\n");
                buscar_imprimir_libro();
                break;
            case 5:
                printf("vender libro\n");
                vender_libro();
                break;
            case 6:
                printf("Editar venta\n");
                editar_venta();
                break;
            case 7:
                printf("Eliminar venta\n");
                eliminar_venta();
                break;
            case 8:
                printf("Imprimir Factura\n");
                imprimir_factura();
                break;
            case 9:
                printf("Saliendo!!!\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }

return 0;
}  



















