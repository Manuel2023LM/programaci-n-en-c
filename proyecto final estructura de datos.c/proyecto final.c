#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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




void guardar_libros();
void cargar_libros();

void guardar_ventas();
void cargar_ventas();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// menu de opciones para el usuario

void menu(){
    printf("\033[0;35m\n==============================================================================\n");
    printf("                        \033[1;36m\033[4m**LIBRERIA: EL LIBRO FAVORITO**\033[0m                     \n");
    printf("\033[0;35m==============================================================================\n\n");

    printf("\033[1;33m \033[4m");
    printf("                          ** MENU DE OPCIONES **                          \033[0m  \n\n");

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
    printf("12.  Generar reporte de inventario\n");

    printf("\033[1;33m13.  Libros agotados\n");
    printf("14.  Total vendido\n");

    

    printf("\033[0;31m\033[4m15.  Borrar todos los libros\n");
    printf("16.  Borrar todas las ventas\n");
    printf("17.  SALIR\033[0m\n");

    printf("\033[1;34m"); // Azul
    printf("\nSeleccione una opcion: ");

    printf("\033[0m\n");
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
    char telefono[30];
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
venta* buscar_venta(int documento);



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




typedef struct{
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
} LibroArchivo;

typedef struct{
    char nombre[100];
    char telefono[30];
    int documento;

    int ISSN;
    char titulo[100];
    char autor[100];
    int cantidad;
    float precio_unitario;

    float total;
    float descuento;
} VentaArchivo;

void guardar_libros(){

    FILE *archivo = fopen("libros.dat", "wb");

    if(archivo == NULL){
        printf("\033[1;31mError al guardar libros\033[0m\n");
        return;
    }

    libro *aux = lista_libros;

    while(aux != NULL){

        LibroArchivo temp;

        strcpy(temp.titulo, aux->titulo);
        strcpy(temp.autor, aux->autor);
        strcpy(temp.genero, aux->genero);

        temp.cantidad_paginas = aux->cantidad_paginas;

        strcpy(temp.editorial, aux->editorial);

        temp.ISSN = aux->ISSN;

        strcpy(temp.idioma, aux->idioma);

        strcpy(temp.fecha_publicacion,
            aux->fecha_publicacion);

        strcpy(temp.estado, aux->estado);

        temp.precio = aux->precio;

        temp.cantidad_ejemplares =
            aux->cantidad_ejemplares;

        fwrite(&temp, sizeof(LibroArchivo), 1, archivo);

        aux = aux->siguiente;
    }

    fclose(archivo);
}



void cargar_libros(){

    FILE *archivo = fopen("libros.dat", "rb");

    if(archivo == NULL){
        return;
    }

    LibroArchivo temp;

    while(fread(&temp, sizeof(LibroArchivo), 1, archivo)){

        libro *nuevo = (libro*) malloc(sizeof(libro));
        if(nuevo == NULL){
            printf("Error de memoria\n");
            return;
        }

        // copiar datos
        strcpy(nuevo->titulo, temp.titulo);
        strcpy(nuevo->autor, temp.autor);
        strcpy(nuevo->genero, temp.genero);

        nuevo->cantidad_paginas = temp.cantidad_paginas;

        strcpy(nuevo->editorial, temp.editorial);

        nuevo->ISSN = temp.ISSN;

        strcpy(nuevo->idioma, temp.idioma);

        strcpy(nuevo->fecha_publicacion,
            temp.fecha_publicacion);

        strcpy(nuevo->estado, temp.estado);

        nuevo->precio = temp.precio;

        nuevo->cantidad_ejemplares =
            temp.cantidad_ejemplares;

        // reconstruir punteros
        nuevo->siguiente = lista_libros;
        nuevo->anterior = NULL;

        if(lista_libros != NULL){
            lista_libros->anterior = nuevo;
        }

        lista_libros = nuevo;
    }

    fclose(archivo);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1. Agregar libro

void agregar_libro(){
    libro *nuevo = (libro*) malloc(sizeof(libro));
    if(nuevo == NULL){
        printf("\033[1;31mError de memoria\033[0m\n");
        return;
    }

    int dia, mes, año;

    printf("\033[1;33mISSN: \033[0m");
    if(scanf("%d", &nuevo->ISSN) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");
        free(nuevo);

        while(getchar() != '\n');

        return;
    }
    if(nuevo->ISSN <= 0){
        printf("\033[1;31mISSN invalido\033[0m\n");
        free(nuevo);
        return;
    }

    if(buscar_libro(nuevo->ISSN) != NULL){
        printf("\033[1;31mEl libro ya existe\033[0m\n");
        free(nuevo);
        return;
    }

    printf("\033[1;33mTitulo: \033[0m");
    scanf(" %99[^\n]", nuevo->titulo);

    printf("\033[1;33mAutor: \033[0m");
    scanf(" %99[^\n]", nuevo->autor);

    // Validar fecha
    int valida;

    do {
        printf("\033[1;33mFecha (dd/mm/yyyy): \033[0m");
        scanf("%10s", nuevo->fecha_publicacion);

        valida = validar_fecha(nuevo->fecha_publicacion, &dia, &mes, &año);

        if(valida == 0){
            printf("\033[1;31mFecha invalida, intente de nuevo\033[0m\n");
        }

    } while(valida == 0);
    printf("\033[1;33mGenero: \033[0m");
    scanf(" %49[^\n]", nuevo->genero);

    printf("Paginas: ");
    if(scanf("%d", &nuevo->cantidad_paginas) != 1){
        printf("Entrada invalida\n");
        free(nuevo);
    

        while(getchar() != '\n');

        return;
    }

    if(nuevo->cantidad_paginas <= 0){
    printf("Cantidad de paginas invalida\n");
    free(nuevo);
    return;
}


    printf("Editorial: ");
    scanf(" %99[^\n]", nuevo->editorial);

    printf("Idioma: ");
    scanf(" %49[^\n]", nuevo->idioma);

    do{
    printf("Estado (nuevo/usado): ");
    scanf(" %49s", nuevo->estado);

    if(strcmp(nuevo->estado, "nuevo") != 0 && strcmp(nuevo->estado, "usado") != 0){
            printf("Estado invalido\n");
        }

    }while(strcmp(nuevo->estado, "nuevo") != 0 && strcmp(nuevo->estado, "usado") != 0);




    printf("Precio: ");
    if(scanf("%f", &nuevo->precio) != 1){
        printf("Entrada invalida\n");
        free(nuevo);

        while(getchar() != '\n');

        return;
    }


    if(nuevo->precio <= 0){
        printf("Precio invalido\n");
        free(nuevo);
        return;
    }

    printf("Cantidad: ");
    if(scanf("%d", &nuevo->cantidad_ejemplares) != 1){
        printf("Entrada invalida\n");
        free(nuevo);

        while(getchar() != '\n');

        return;
    }


    if(nuevo->cantidad_ejemplares < 0){
    printf("Cantidad invalida\n");
    free(nuevo);
    return;
}

    // insertar al inicio (lista doble)
    nuevo->siguiente = lista_libros;
    nuevo->anterior = NULL;

    if(lista_libros != NULL){
        lista_libros->anterior = nuevo;
    }

    lista_libros = nuevo;

    printf("\033[1;32mLibro agregado correctamente\033[0m\n");
    guardar_libros();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 2. Editar libro
void editar_libro(){
    int ISSN;
    printf("Ingrese el ISSN del libro a editar: ");
    if(scanf("%d", &ISSN) != 1){
        printf("Entrada invalida\n");

        while(getchar() != '\n');

        return;
    }

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
    if(scanf("%d", &opcion) != 1){
        printf("Entrada invalida\n");
        while(getchar() != '\n');
        return;
    }

    switch(opcion){
        case 1:
            printf("Precio actual: %.2f\n", encontrado->precio);
            printf("Nuevo precio: ");
            if(scanf("%f", &encontrado->precio) != 1){
                printf("Entrada invalida\n");
                while(getchar() != '\n');
                return;
            }
            if(encontrado->precio <= 0){
                printf("Precio invalido\n");
                return;
            }
            printf("\033[1;32mPrecio actualizado correctamente\033[0m\n");
            guardar_libros();
            break;

        case 2:
            printf("Cantidad actual: %d\n", encontrado->cantidad_ejemplares);
            printf("Nueva cantidad: ");
            if(scanf("%d", &encontrado->cantidad_ejemplares) != 1){
                printf("Entrada invalida\n");
                while(getchar() != '\n');
                return;
            }
            if(encontrado->cantidad_ejemplares < 0){
                    printf("Cantidad invalida\n");
                    return;
                }
            printf("\033[1;32mCantidad actualizada correctamente\033[0m\n");
            guardar_libros();
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
    if(scanf("%d", &ISSN) != 1){
        printf("Entrada invalida\n");

        while(getchar() != '\n');

        return;
    }

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

    printf("\033[1;32mLibro eliminado correctamente\033[0m\n");
    guardar_libros();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimir_libro(libro *l){
    if(l == NULL) return;

    printf("\033[1;36m\n-----------------------------\n");
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
    printf("Cantidad: %d\033[0m\n", l->cantidad_ejemplares);
}



// 4. Buscar/imprimir libro
void buscar_imprimir_libro(){
    int opcion;
    printf("\033[1;35m\nBuscar por:\n");
    printf("1. ISSN\n");
    printf("2. Autor\n");
    printf("3. Estado\n");
    printf("4. Precio\033[0m\n");
    printf("\033[1;33mSeleccione: \033[0m");
    if(scanf("%d", &opcion) != 1){
        printf("Entrada invalida\n");
        while(getchar() != '\n');
        return;
    }

    libro *aux = lista_libros;
    int encontrado = 0;

    if(opcion == 1){
        int ISSN;
        printf("Ingrese ISSN: ");
        if(scanf("%d", &ISSN) != 1){
            printf("Entrada invalida\n");
            while(getchar() != '\n');
            return;
        }

        libro *lib = buscar_libro(ISSN);

        if(lib != NULL){
            imprimir_libro(lib);
            encontrado = 1;
        } else {
                printf("\033[1;31mNo existe libro con ese ISSN\033[0m\n");
}
    }

    else if(opcion == 2){
        char autor[100];
        printf("Ingrese autor: ");
        scanf(" %99[^\n]", autor);

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
        scanf(" %49s", estado);

        while(aux != NULL){
            if(strcmp(aux->estado, estado) == 0){
                imprimir_libro(aux);
                encontrado = 1;
            }
            aux = aux->siguiente;
        }
    }


    else if(opcion == 4){
    float min, max;

    printf("Precio minimo: ");
    if(scanf("%f", &min) != 1){
        printf("Entrada invalida\n");
        while(getchar() != '\n');
        return;
    }

    printf("Precio maximo: ");
    if(scanf("%f", &max) != 1){
        printf("Entrada invalida\n");
        while(getchar() != '\n');
        return;
    }

    if(min > max){
    printf("Rango invalido\n");
    return;
}


    while(aux != NULL){
        if(aux->precio >= min && aux->precio <= max){
            imprimir_libro(aux);
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
    printf("\033[1;33mIngrese el ISSN del libro a vender: \033[0m");
    if(scanf("%d", &ISSN) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");
        while(getchar() != '\n');
        return;
    }

    libro *lib = buscar_libro(ISSN);

    if(lib == NULL){
        printf("\033[1;31mEl libro no existe\033[0m\n");
        return;
    }

    if(lib->cantidad_ejemplares == 0){
        printf("\033[1;31mNo hay stock disponible\033[0m\n");
        return;
    }

    int cantidad;
    printf("\033[1;33mCantidad a comprar (max 5): \033[0m");
    if(scanf("%d", &cantidad) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");

        while(getchar() != '\n');

        return;
    }


    if(cantidad > 5){
        printf("\033[1;31mNo puede comprar más de 5 unidades\033[0m\n");
        return;
    }

    if(cantidad > lib->cantidad_ejemplares){
        printf("\033[1;31mNo hay suficiente stock\033[0m\n");
        return;
    }

    if(cantidad <= 0){
    printf("\033[1;31mCantidad invalida\033[0m\n");
    return;
}


    // crear venta
    venta *nueva = (venta*) malloc(sizeof(venta));
    if(nueva == NULL){
        printf("\033[1;31mError de memoria\033[0m\n");
        return;
    }

    printf("\033[1;33mNombre: \033[0m");
    scanf(" %99[^\n]", nueva->nombre);

    printf("\033[1;33mTelefono: \033[0m");
    scanf("%29s", nueva->telefono);

    printf("\033[1;33mDocumento: \033[0m");
    if(scanf("%d", &nueva->documento) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");

        free(nueva);

        while(getchar() != '\n');

        return;
    }

    if(nueva->documento <= 0){
    printf("\033[1;31mDocumento invalido\033[0m\n");
    free(nueva);
    return;
}

    if(buscar_venta(nueva->documento) != NULL){
    printf("\033[1;31mYa existe una venta con ese documento\033[0m\n");
    free(nueva);
    return;
}

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

    guardar_ventas();
    guardar_libros();

    printf("\033[1;32m\n===== VENTA REALIZADA =====\033[0m\n");
    printf("\033[1;36mCliente: %s\033[0m\n", nueva->nombre);
    printf("\033[1;33mTotal: %.2f\033[0m\n", nueva->total);
    printf("\033[1;35mDescuento: %.2f\033[0m\n", nueva->descuento);
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


void guardar_ventas(){

    FILE *archivo = fopen("ventas.dat", "wb");

    if(archivo == NULL){
        printf("\033[1;31mError al guardar ventas\033[0m\n");
        return;
    }

    venta *aux = lista_ventas;

    while(aux != NULL){

        VentaArchivo temp;

        strcpy(temp.nombre, aux->nombre);
        strcpy(temp.telefono, aux->telefono);

        temp.documento = aux->documento;

        temp.ISSN = aux->ISSN;

        strcpy(temp.titulo, aux->titulo);
        strcpy(temp.autor, aux->autor);

        temp.cantidad = aux->cantidad;

        temp.precio_unitario =
            aux->precio_unitario;

        temp.total = aux->total;

        temp.descuento = aux->descuento;

        fwrite(&temp, sizeof(VentaArchivo), 1, archivo);

        aux = aux->siguiente;
    }

    fclose(archivo);
}
void cargar_ventas(){

    FILE *archivo = fopen("ventas.dat", "rb");

    if(archivo == NULL){
        return;
    }

    VentaArchivo temp;

    while(fread(&temp, sizeof(VentaArchivo), 1, archivo)){

        venta *nueva = (venta*) malloc(sizeof(venta));
        if(nueva == NULL){
            printf("Error de memoria\n");
            return;
        }

        strcpy(nueva->nombre, temp.nombre);
        strcpy(nueva->telefono, temp.telefono);

        nueva->documento = temp.documento;

        nueva->ISSN = temp.ISSN;

        strcpy(nueva->titulo, temp.titulo);
        strcpy(nueva->autor, temp.autor);

        nueva->cantidad = temp.cantidad;

        nueva->precio_unitario =
            temp.precio_unitario;

        nueva->total = temp.total;

        nueva->descuento = temp.descuento;

        nueva->siguiente = lista_ventas;

        lista_ventas = nueva;
    }

    fclose(archivo);
}

// 6. Editar venta


void editar_venta(){
    int documento;
    printf("\033[1;33mIngrese documento de la venta: \033[0m");
    if(scanf("%d", &documento) != 1){
    printf("\033[1;31mEntrada invalida\033[0m\n");

    while(getchar() != '\n');

    return;
}

    venta *v = buscar_venta(documento);

    if(v == NULL){
        printf("\033[1;31mVenta no encontrada\033[0m\n");
        return;
    }

    int opcion;
    printf("\033[1;35m\n1. Editar nombre\n");
    printf("2. Editar telefono\n");
    printf("3. Editar cantidad\n");
    printf("Seleccione: \033[0m");
    if(scanf("%d", &opcion) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");
        while(getchar() != '\n');
        return;
    }

    if(opcion == 1){
        printf("Nuevo nombre: ");
        scanf(" %99[^\n]", v->nombre);
        guardar_ventas();
        guardar_libros();
    }
    else if(opcion == 2){
        printf("Nuevo telefono: ");
        scanf(" %29s", v->telefono);
        guardar_ventas();
        guardar_libros();
    }
    else if(opcion == 3){
        libro *lib = buscar_libro(v->ISSN);

        if(lib == NULL){
            printf("\033[1;31mError: libro no encontrado\033[0m\n");
            return;
        }

        // 🔥 devolver stock anterior
        lib->cantidad_ejemplares += v->cantidad;

        int nueva_cantidad;
        printf("\033[1;33mNueva cantidad: \033[0m");
        if(scanf("%d", &nueva_cantidad) != 1){
            printf("\033[1;31mEntrada invalida\033[0m\n");
            while(getchar() != '\n');
            lib->cantidad_ejemplares -= v->cantidad;
            return;
        }

        if(nueva_cantidad <= 0){
            printf("\033[1;31mCantidad invalida\033[0m\n");
            lib->cantidad_ejemplares -= v->cantidad;
            return;
        }


        if(nueva_cantidad > 5){
            printf("\033[1;31mMaximo 5 unidades\033[0m\n");
            lib->cantidad_ejemplares -= v->cantidad; // revertir
            return;
        }

        if(nueva_cantidad > lib->cantidad_ejemplares){
            printf("\033[1;31mNo hay suficiente stock\033[0m\n");
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

        printf("\033[1;32mCantidad actualizada correctamente\033[0m\n");
        guardar_ventas();
        guardar_libros();
    }
    else{
        printf("\033[1;31mOpcion invalida\033[0m\n");
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 7. Eliminar venta

void eliminar_venta(){
    int documento;
    printf("\033[1;33mIngrese documento de la venta a eliminar: \033[0m");
    if(scanf("%d", &documento) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");
        while(getchar() != '\n');
        return;
    }

    venta *actual = lista_ventas;
    venta *anterior = NULL;

    while(actual != NULL && actual->documento != documento){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual == NULL){
        printf("\033[1;31mVenta no encontrada\033[0m\n");
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
    guardar_ventas();
    guardar_libros();
    printf("\033[1;32mVenta eliminada y stock restaurado correctamente\033[0m\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 8. Imprimir Factura

void imprimir_factura(){
    int documento;
    printf("\033[1;33mIngrese documento de la venta: \033[0m");
    if(scanf("%d", &documento) != 1){
        printf("\033[1;31mEntrada invalida\033[0m\n");
        while(getchar() != '\n');
        return;
    }

    venta *v = buscar_venta(documento);

    if(v == NULL){
        printf("\033[1;31mVenta no encontrada\033[0m\n");
        return;
    }

    printf("\033[1;35m\n=====================================\n");
    printf("              FACTURA DE COMPRA              \n");
    printf("=====================================\033[0m\n");

    printf("\033[1;36mCliente: %s\n", v->nombre);
    printf("Documento: %d\n", v->documento);
    printf("Telefono: %s\033[0m\n", v->telefono);

    printf("\033[1;33m\n           --- Detalle ---\n");
    printf("Libro: %s\n", v->titulo);
    printf("Autor: %s\n", v->autor);
    printf("Cantidad: %d\n", v->cantidad);
    printf("Precio unitario: %.2f\033[0m\n", v->precio_unitario);

    printf("\033[1;37m\n-------------------------------\n");
    printf("Subtotal: %.2f\n", v->precio_unitario * v->cantidad);
    printf("Descuento: %.2f\n", v->descuento);
    printf("\033[1;31mTOTAL A PAGAR: %.2f\033[0m\n", v->total);
    printf("\033[1;35m=====================================\033[0m\n");
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








void imprimir_todos_libros(){
    libro *aux = lista_libros;
    int total = 0;

    if(aux == NULL){
        printf("\033[1;31mNo hay libros registrados\033[0m\n");
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
    scanf(" %99[^\n]", titulo);

    libro *aux = lista_libros;

    while(aux != NULL){
        if(strcmp(aux->titulo, titulo) == 0){
            imprimir_libro(aux);
            encontrado = 1;
        }
        aux = aux->siguiente;
    }

    if(!encontrado){
        printf("\033[1;33mNo se encontro el libro\033[0m\n");
    }
}



void imprimir_todas_ventas(){
    venta *aux = lista_ventas;
    int total = 0;

    if(aux == NULL){
        printf("\033[1;31mNo hay ventas registradas\033[0m\n");
        return;
    }

    printf("\033[1;35m\n======= VENTAS REGISTRADAS =======\033[0m\n");
    while(aux != NULL){
        printf("\033[1;34m\n=============================\n");
        printf("Cliente: %s\n", aux->nombre);
        printf("Documento: %d\n", aux->documento);
        printf("Telefono: %s\n", aux->telefono);

        printf("Libro: %s\n", aux->titulo);
        printf("Autor: %s\n", aux->autor);
        printf("Cantidad: %d\n", aux->cantidad);
        printf("Precio unitario: %.2f\n", aux->precio_unitario);

        printf("Descuento: %.2f\n", aux->descuento);
        printf("Total: %.2f\033[0m\n", aux->total);

        total++;
        aux = aux->siguiente;
    }

    printf("\033[1;32m\nTotal de ventas: %d\033[0m\n", total);
}





void reporte_inventario(){

    libro *aux = lista_libros;

    int total_libros = 0;
    int total_unidades = 0;
    float valor_total = 0;

    if(aux == NULL){
        printf("\033[1;31mNo hay libros registrados\033[0m\n");
        return;
    }

    printf("\033[1;34m\n=========== REPORTE DE INVENTARIO ===========\033[0m\n");

    while(aux != NULL){

        total_libros++;

        total_unidades += aux->cantidad_ejemplares;

        valor_total += aux->precio * aux->cantidad_ejemplares;

        printf("\033[1;33m\nTitulo: %s\n", aux->titulo);
        printf("ISSN: %d\n", aux->ISSN);
        printf("Cantidad: %d\n", aux->cantidad_ejemplares);
        printf("Valor total libro: %.2f\033[0m\n",
               aux->precio * aux->cantidad_ejemplares);

        aux = aux->siguiente;
    }

    printf("\n\033[1;32m====================================\n");
    printf("Total tipos de libros: %d\n", total_libros);
    printf("Total unidades: %d\n", total_unidades);
    printf("Valor total inventario: %.2f\n", valor_total);
    printf("====================================\033[0m\n");
}



void libros_agotados(){

    libro *aux = lista_libros;

    int encontrados = 0;

    printf("\033[1;35m\n======= LIBROS AGOTADOS =======\033[0m\n");

    while(aux != NULL){

        if(aux->cantidad_ejemplares == 0){

            imprimir_libro(aux);

            encontrados = 1;
        }

        aux = aux->siguiente;
    }

    if(!encontrados){
        printf("\033[1;33mNo hay libros agotados\033[0m\n");
    }
}

void total_vendido(){

    venta *aux = lista_ventas;

    float total = 0;
    float descuentos = 0;

    int cantidad_ventas = 0;
    int libros_vendidos = 0;

    while(aux != NULL){

        total += aux->total;

        descuentos += aux->descuento;

        libros_vendidos += aux->cantidad;

        cantidad_ventas++;

        aux = aux->siguiente;
    }

    printf("\033[1;36m\n========== REPORTE DE VENTAS ==========\033[0m\n");

    printf("\033[1;32mCantidad de ventas: %d\033[0m\n", cantidad_ventas);

    printf("\033[1;33mLibros vendidos: %d\033[0m\n", libros_vendidos);

    printf("\033[1;35mDescuentos aplicados: %.2f\033[0m\n", descuentos);

    printf("\033[1;34mDinero total vendido: %.2f\033[0m\n", total);

    printf("\033[1;36m=======================================\033[0m\n");
}




void borrar_todos_libros(){

    if(lista_ventas != NULL){
        printf("\033[1;31mNo se pueden borrar libros mientras existan ventas\033[0m\n");
        return;
    }

    libro *aux = lista_libros;

    while(aux != NULL){

        libro *temp = aux;

        aux = aux->siguiente;

        free(temp);
    }

    lista_libros = NULL;

    remove("libros.dat");

    printf("\033[1;32mTodos los libros fueron eliminados\033[0m\n");
}




void borrar_todas_ventas(){

    venta *aux = lista_ventas;

    while(aux != NULL){

        venta *temp = aux;

        aux = aux->siguiente;


        libro *lib = buscar_libro(aux->ISSN);

    if(lib != NULL){
        lib->cantidad_ejemplares += aux->cantidad;
    }

        free(temp);
    }

    lista_ventas = NULL;

    remove("ventas.dat");

    printf("\033[1;32mTodas las ventas fueron eliminadas\033[0m\n");
}


void liberar_libros(){
    libro *aux = lista_libros;

    while(aux != NULL){
        libro *temp = aux;
        aux = aux->siguiente;
        free(temp);
    }
}

void liberar_ventas(){
    venta *aux = lista_ventas;

    while(aux != NULL){
        venta *temp = aux;
        aux = aux->siguiente;
        free(temp);
    }
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int opcion = 0;
    cargar_libros();
    cargar_ventas();
    while(opcion != 17){
        menu();
        if(scanf("%d", &opcion) != 1){
            printf("Entrada invalida\n");

            while(getchar() != '\n');

            opcion = 0;
            continue;
        }

        switch(opcion){

            case 1:
                agregar_libro();
                break;

            case 2:
                editar_libro();
                break;

            case 3:
                eliminar_libro();
                break;

            case 4:
                buscar_imprimir_libro();
                break;

            case 5:
                vender_libro();
                break;

            case 6:
                editar_venta();
                break;

            case 7:
                eliminar_venta();
                break;

            case 8:
                imprimir_factura();
                break;

            case 9:
                imprimir_todos_libros();
                break;

            case 10:
                buscar_por_titulo();
                break;

            case 11:
                imprimir_todas_ventas();
                break;

            case 12:
                reporte_inventario();
                break;

            case 13:
                libros_agotados();
                break;

            case 14:
                total_vendido();
                break;
            case 15:
                borrar_todos_libros();
                break;

            case 16:
                borrar_todas_ventas();
                break;

            case 17:
                printf("\033[1;36mSaliendo del sistema...\033[0m\n");
                break;

            default:
                printf("\033[1;31mOpcion incorrecta\033[0m\n");
        }
    }
liberar_libros();
liberar_ventas();

    return 0;
}
