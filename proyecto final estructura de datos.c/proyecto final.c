#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// menu de opciones para el usuario

void menu(){
    // Colores
    printf("\033[1;36m"); // Cyan brillante
    printf("\n=========================================\n");
    printf("     LIBRERIA: EL LIBRO FAVORITO\n");
    printf("=========================================\n");

    printf("\033[1;33m"); // Amarillo
    printf("            MENU DE OPCIONES\n\n");

    printf("\033[1;32m"); // Verde
    printf(" 1.  Agregar libro\n");
    printf(" 2.  Editar libro\n");
    printf(" 3.  Eliminar libro\n");

    printf("\033[1;34m"); // Azul
    printf(" 4.  Buscar / Imprimir libro\n");

    printf("\033[1;35m"); // Magenta
    printf(" 5.  Vender libro\n");
    printf(" 6.  Editar venta\n");
    printf(" 7.  Eliminar venta\n");

    printf("\033[1;36m"); // Cyan
    printf(" 8.  Imprimir factura\n");

    printf("\033[1;32m"); // Verde
    printf(" 9.  Imprimir todos los libros\n");
    printf("10.  Buscar por titulo\n");

    printf("\033[1;35m"); // Magenta
    printf("11.  Imprimir todas las ventas\n");

    printf("\033[1;31m"); // Rojo
    printf("12.  SALIR\n");

    printf("\033[0m"); // Reset color
    printf("\nSeleccione una opcion: ");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// definicion de la estructura de datos para el libro


typedef struct libro {
    char titulo[100];
    char autor[100];
    char genero[50];
    int cantidad_paginas;
    char editorial[100];
    int ISSN;
    char idioma[50];
    char fecha_publicacion[11];
    char estado[50];
    float precio;
    int cantidad_ejemplares;

    struct libro *anterior;
    struct libro *siguiente; 
} libro;


libro *lista_libros = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct venta {
    char nombre[100];
    int telefono;
    int documento;

    int ISSN;
    char titulo[100]; 
    char autor[100];
    int cantidad;
    float precio_unitario;

    float total;
    float descuento;

    struct venta *siguiente;
} venta;

venta *lista_ventas = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



libro* buscar_libro(int ISSN){
    libro *aux = lista_libros;

    while(aux != NULL){
        if(aux->ISSN == ISSN){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1. Agregar libro

void agregar_libro(){
    libro *nuevo = (libro*) malloc(sizeof(libro));

    int dia, mes, año;

    printf("ISSN: ");
    scanf("%d", &nuevo->ISSN);

    if(buscar_libro(nuevo->ISSN) != NULL){
        printf("El libro ya existe\n");
        free(nuevo);
        return;
    }

    printf("Titulo: ");
    scanf(" %[^\n]", nuevo->titulo);

    printf("Autor: ");
    scanf(" %[^\n]", nuevo->autor);

    // Validar fecha
    int valida;

do {
    printf("Fecha (dd/mm/yyyy): ");
    scanf("%10s", nuevo->fecha_publicacion);

    valida = validar_fecha(nuevo->fecha_publicacion, &dia, &mes, &año);

    if(valida == 0){
        printf("Fecha invalida, intente de nuevo\n");
    }

} while(valida == 0);
    printf("Genero: ");
    scanf(" %[^\n]", nuevo->genero);

    printf("Paginas: ");
    scanf("%d", &nuevo->cantidad_paginas);

    printf("Editorial: ");
    scanf("%s", nuevo->editorial);

    printf("Idioma: ");
    scanf("%s", nuevo->idioma);

    printf("Estado (nuevo/usado): ");
    scanf("%s", nuevo->estado);

    printf("Precio: ");
    scanf("%f", &nuevo->precio);

    printf("Cantidad: ");
    scanf("%d", &nuevo->cantidad_ejemplares);

    // insertar al inicio (lista doble)
    nuevo->siguiente = lista_libros;
    nuevo->anterior = NULL;

    if(lista_libros != NULL){
        lista_libros->anterior = nuevo;
    }

    lista_libros = nuevo;

    printf("Libro agregado correctamente\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 2. Editar libro
void editar_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a editar: ");
    scanf("%d", &ISSN);

    libro *encontrado = buscar_libro(ISSN);

    if(encontrado == NULL){
        printf("El libro no existe\n");
        return;
    }

    int opcion;

    printf("\nLibro encontrado: %s\n", encontrado->titulo);
    printf("1. Editar precio\n");
    printf("2. Editar cantidad\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);

    switch(opcion){
        case 1:
            printf("Precio actual: %.2f\n", encontrado->precio);
            printf("Nuevo precio: ");
            scanf("%f", &encontrado->precio);
            printf("Precio actualizado correctamente\n");
            break;

        case 2:
            printf("Cantidad actual: %d\n", encontrado->cantidad_ejemplares);
            printf("Nueva cantidad: ");
            scanf("%d", &encontrado->cantidad_ejemplares);
            printf("Cantidad actualizada correctamente\n");
            break;

        default:
            printf("Opcion invalida\n");
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// 3. Eliminar libro
void eliminar_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a eliminar: ");
    scanf("%d", &ISSN);

    libro *eliminar = buscar_libro(ISSN);

    if(eliminar == NULL){
        printf("El libro no existe\n");
        return;
    }

    if(eliminar->cantidad_ejemplares > 0){
        printf("No se puede eliminar, aun hay ejemplares disponibles\n");
        return;
    }

    //  CASO 1: es el primero
    if(eliminar == lista_libros){
        lista_libros = eliminar->siguiente;
        if(lista_libros != NULL){
            lista_libros->anterior = NULL;
        }
    }
    //  CASO 2 y 3: medio o último
    else{
        if(eliminar->anterior != NULL){
            eliminar->anterior->siguiente = eliminar->siguiente;
        }
        if(eliminar->siguiente != NULL){
            eliminar->siguiente->anterior = eliminar->anterior;
        }
    }

    free(eliminar);

    printf("Libro eliminado correctamente\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimir_libro(libro *l){
    if(l == NULL) return;

    printf("\n-----------------------------\n");
    printf("Titulo: %s\n", l->titulo);
    printf("Autor: %s\n", l->autor);
    printf("Genero: %s\n", l->genero);
    printf("Paginas: %d\n", l->cantidad_paginas);
    printf("Editorial: %s\n", l->editorial);
    printf("ISSN: %d\n", l->ISSN);
    printf("Idioma: %s\n", l->idioma);
    printf("Fecha: %s\n", l->fecha_publicacion);
    printf("Estado: %s\n", l->estado);
    printf("Precio: %.2f\n", l->precio);
    printf("Cantidad: %d\n", l->cantidad_ejemplares);
}



// 4. Buscar/imprimir libro
void buscar_imprimir_libro(){
    int opcion;
    printf("\nBuscar por:\n");
    printf("1. ISSN\n");
    printf("2. Autor\n");
    printf("3. Estado\n");
    printf("4. Precio\n");
    printf("Seleccione: ");
    scanf("%d", &opcion);

    libro *aux = lista_libros;
    int encontrado = 0;

    if(opcion == 1){
        int ISSN;
        printf("Ingrese ISSN: ");
        scanf("%d", &ISSN);

        libro *lib = buscar_libro(ISSN);

        if(lib != NULL){
            printf("Titulo: %s\n", lib->titulo);
            encontrado = 1;
        } else {
                printf("No existe libro con ese ISSN\n");
}
    }

    else if(opcion == 2){
        char autor[100];
        printf("Ingrese autor: ");
        scanf(" %[^\n]", autor);

        while(aux != NULL){
            if(strcmp(aux->autor, autor) == 0){
                imprimir_libro(aux);
                encontrado = 1;
            }
            aux = aux->siguiente;
        }
    }

    else if(opcion == 3){
        char estado[50];
        printf("Ingrese estado (nuevo/usado): ");
        scanf("%s", estado);

        while(aux != NULL){
            if(strcmp(aux->estado, estado) == 0){
                printf("Titulo: %s\n", aux->titulo);
                encontrado = 1;
            }
            aux = aux->siguiente;
        }
    }


    else if(opcion == 4){
    float min, max;

    printf("Precio minimo: ");
    scanf("%f", &min);

    printf("Precio maximo: ");
    scanf("%f", &max);


    while(aux != NULL){
        if(aux->precio >= min && aux->precio <= max){
            printf("\nTitulo: %s\n", aux->titulo);
            printf("Precio: %.2f\n", aux->precio);
            printf("-----------------\n");
            encontrado = 1;
        }
        aux = aux->siguiente;
    }

}

    if(!encontrado){
        printf("No se encontraron resultados\n");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 5. vender libro



void vender_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a vender: ");
    scanf("%d", &ISSN);

    libro *lib = buscar_libro(ISSN);

    if(lib == NULL){
        printf("El libro no existe\n");
        return;
    }

    if(lib->cantidad_ejemplares == 0){
        printf("No hay stock disponible\n");
        return;
    }

    int cantidad;
    printf("Cantidad a comprar (max 5): ");
    scanf("%d", &cantidad);



    if(cantidad > 5){
        printf("No puede comprar más de 5 unidades\n");
        return;
    }

    if(cantidad > lib->cantidad_ejemplares){
        printf("No hay suficiente stock\n");
        return;
    }

    if(cantidad <= 0){
    printf("Cantidad invalida\n");
    return;
}


    // crear venta
    venta *nueva = (venta*) malloc(sizeof(venta));

    printf("Nombre: ");
    scanf(" %[^\n]", nueva->nombre);

    printf("Telefono: ");
    scanf("%d", &nueva->telefono);

    printf("Documento: ");
    scanf("%d", &nueva->documento);

    nueva->ISSN = ISSN;
    nueva->cantidad = cantidad;
    nueva->precio_unitario = lib->precio;


//  GUARDAR DATOS DEL LIBRO
strcpy(nueva->titulo, lib->titulo);
strcpy(nueva->autor, lib->autor);


    // calcular total
    nueva->total = lib->precio * cantidad;

    // descuento
    if(nueva->total > 200000){
        nueva->descuento = nueva->total * 0.15;
        nueva->total = nueva->total - nueva->descuento;
    } else {
        nueva->descuento = 0;
    }

    // actualizar inventario
    lib->cantidad_ejemplares -= cantidad;

    // insertar en lista de ventas
    nueva->siguiente = lista_ventas;
    lista_ventas = nueva;

    printf("\n===== VENTA REALIZADA =====\n");
    printf("Cliente: %s\n", nueva->nombre);
    printf("Total: %.2f\n", nueva->total);
    printf("Descuento: %.2f\n", nueva->descuento);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


venta* buscar_venta(int documento){
    venta *aux = lista_ventas;

    while(aux != NULL){
        if(aux->documento == documento){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}




// 6. Editar venta


void editar_venta(){
    int documento;
    printf("Ingrese documento de la venta: ");
    scanf("%d", &documento);

    venta *v = buscar_venta(documento);

    if(v == NULL){
        printf("Venta no encontrada\n");
        return;
    }

    int opcion;
    printf("\n1. Editar nombre\n");
    printf("2. Editar telefono\n");
    printf("3. Editar cantidad\n");
    printf("Seleccione: ");
    scanf("%d", &opcion);

    if(opcion == 1){
        printf("Nuevo nombre: ");
        scanf(" %[^\n]", v->nombre);
    }
    else if(opcion == 2){
        printf("Nuevo telefono: ");
        scanf("%d", &v->telefono);
    }
    else if(opcion == 3){
        libro *lib = buscar_libro(v->ISSN);

        if(lib == NULL){
            printf("Error: libro no encontrado\n");
            return;
        }

        // 🔥 devolver stock anterior
        lib->cantidad_ejemplares += v->cantidad;

        int nueva_cantidad;
        printf("Nueva cantidad: ");
        scanf("%d", &nueva_cantidad);

        if(nueva_cantidad > 5){
            printf("Maximo 5 unidades\n");
            lib->cantidad_ejemplares -= v->cantidad; // revertir
            return;
        }

        if(nueva_cantidad > lib->cantidad_ejemplares){
            printf("No hay suficiente stock\n");
            lib->cantidad_ejemplares -= v->cantidad; // revertir
            return;
        }

        // aplicar nueva venta
        v->cantidad = nueva_cantidad;

        lib->cantidad_ejemplares -= nueva_cantidad;

        // recalcular total
        v->total = lib->precio * nueva_cantidad;

        if(v->total > 200000){
            v->descuento = v->total * 0.15;
            v->total -= v->descuento;
        } else {
            v->descuento = 0;
        }

        printf("Cantidad actualizada correctamente\n");
    }
    else{
        printf("Opcion invalida\n");
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 7. Eliminar venta

void eliminar_venta(){
    int documento;
    printf("Ingrese documento de la venta a eliminar: ");
    scanf("%d", &documento);

    venta *actual = lista_ventas;
    venta *anterior = NULL;

    while(actual != NULL && actual->documento != documento){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual == NULL){
        printf("Venta no encontrada\n");
        return;
    }

    // 🔥 devolver stock
    libro *lib = buscar_libro(actual->ISSN);

    if(lib != NULL){
        lib->cantidad_ejemplares += actual->cantidad;
    }

    // 🔥 eliminar nodo
    if(anterior == NULL){
        // es el primero
        lista_ventas = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);

    printf("Venta eliminada y stock restaurado correctamente\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 8. Imprimir Factura

void imprimir_factura(){
    int documento;
    printf("Ingrese documento de la venta: ");
    scanf("%d", &documento);

    venta *v = buscar_venta(documento);

    if(v == NULL){
        printf("Venta no encontrada\n");
        return;
    }

    printf("\n=====================================\n");
    printf("           FACTURA DE COMPRA\n");
    printf("=====================================\n");

    printf("Cliente: %s\n", v->nombre);
    printf("Documento: %d\n", v->documento);
    printf("Telefono: %d\n", v->telefono);

    printf("\n--- Detalle ---\n");
    printf("Libro: %s\n", v->titulo);
    printf("Autor: %s\n", v->autor);
    printf("Cantidad: %d\n", v->cantidad);
    printf("Precio unitario: %.2f\n", v->precio_unitario);

    printf("\n-------------------------------\n");
    printf("Subtotal: %.2f\n", v->precio_unitario * v->cantidad);
    printf("Descuento: %.2f\n", v->descuento);
    printf("TOTAL A PAGAR: %.2f\n", v->total);
    printf("=====================================\n");
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








void imprimir_todos_libros(){
    libro *aux = lista_libros;
    int total = 0;

    if(aux == NULL){
        printf("No hay libros registrados\n");
        return;
    }

    while(aux != NULL){
        imprimir_libro(aux);
        total++;
        aux = aux->siguiente;
    }

    printf("\nTotal de libros: %d\n", total);
}



void buscar_por_titulo(){
    char titulo[100];
    int encontrado = 0;

    printf("Ingrese el titulo: ");
    scanf(" %[^\n]", titulo);

    libro *aux = lista_libros;

    while(aux != NULL){
        if(strcmp(aux->titulo, titulo) == 0){
            imprimir_libro(aux);
            encontrado = 1;
        }
        aux = aux->siguiente;
    }

    if(!encontrado){
        printf("No se encontro el libro\n");
    }
}



void imprimir_todas_ventas(){
    venta *aux = lista_ventas;
    int total = 0;

    if(aux == NULL){
        printf("No hay ventas registradas\n");
        return;
    }

    while(aux != NULL){
        printf("\n=============================\n");
        printf("Cliente: %s\n", aux->nombre);
        printf("Documento: %d\n", aux->documento);
        printf("Telefono: %d\n", aux->telefono);

        printf("Libro: %s\n", aux->titulo);
        printf("Autor: %s\n", aux->autor);
        printf("Cantidad: %d\n", aux->cantidad);
        printf("Precio unitario: %.2f\n", aux->precio_unitario);

        printf("Descuento: %.2f\n", aux->descuento);
        printf("Total: %.2f\n", aux->total);

        total++;
        aux = aux->siguiente;
    }

    printf("\nTotal de ventas: %d\n", total);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int opcion = 0;

    while(opcion != 14){
        menu();
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                printf("Agregar libro\n");
                agregar_libro();
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
            case 11:
                imprimir_todos_libros();
                break;

            case 12:
                buscar_por_titulo();
                break;

            case 13:
                imprimir_todas_ventas();
                break;
            case 14:
                    printf("Saliendo!!!\n");
                    break;

            default:
                printf("Opcion incorrecta\n");
                break;
        }
    }

return 0;
}  


