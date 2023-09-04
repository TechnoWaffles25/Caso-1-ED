// Control para que no defina mas de una vez al compilar
#ifndef _NODODOBLE_
    #define _NODODOBLE_ 1

    #include <iostream>

    struct noticia {
        int numero;
        std::string titular;
    };

    struct nododoble {
        /* Creamos la estructura del nodo doble que nos permite retrodecer o avanzar 
        junto con la informacion de la noticias de ese nodo */
        struct noticia data;

        // El nullptr indica que inicialmente NO HAY NODO ANTERIOR O POSTERIOR

        struct nododoble* next = nullptr;
        struct nododoble* previous = nullptr;
    };

#endif