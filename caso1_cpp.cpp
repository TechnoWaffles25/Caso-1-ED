#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "news.h" // Include the header file for Newsapi, assuming it's "news.h"
#include "nodo_doble.h" // Include the header file for nodo_doble
#include "lista_doble.h" // Include the header file for lista_doble

using namespace std;

int main() {
    // Creamos una instancia del NewsAPI
    Newsapi newsApi;

    // Llamamos la funcion para popular el vector
    vector<struct noticia *> allrecords = newsApi.getRecords("election","2023-08-29"); //AAAA-MM-DD

    // Obtenemos el tamaño del vecctor
    int vector_size = allrecords.size();
    cout << "Vector size: " << vector_size << std::endl;

    // Crear una instancia de la lista doblemente enlazada
    listadoble lista;

    // Insertar noticias en la lista
    int contador = 0;
    //cout << "-------------------" << std::endl;

    while (contador < vector_size){
        lista.insertar(allrecords.at(contador), contador); // Insertar
        contador++;   
    }

    // Mostrar el tamaño de la lista
    std::cout << "Tamaño de la lista: " << lista.getSize() << std::endl;
    cout << "-------------------" << std::endl;
    lista.buscar("lawyer, trump"); 

    cout << "-------------------" << std::endl;
    lista.getTop5Key("lawyer, trump"); 
    
    cout << "-------------------" << std::endl;
    lista.buscar_eliminar("lawyer, trump");

    cout << "-------------------" << std::endl;
    std::cout << "Tamaño de la lista: " << lista.getSize() << std::endl;

    cout << "-------------------" << std::endl;
    lista.getTop5();

    cout << "-------------------" << std::endl;
    lista.reacomodar(3,1);
    lista.reacomodar(10,15);

    cout << "-------------------" << std::endl;
    lista.mostrar();
}