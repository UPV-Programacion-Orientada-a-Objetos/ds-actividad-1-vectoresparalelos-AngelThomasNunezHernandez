#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::string nombres[100];
    std::string paises[100];
    std::string disciplinas[100];
    std::string generos[100];
    int medallas[100];
    int AtletasTotales = 0;

    std::string archivocsv;
    std::cout << "Ruta del archivo CSV o nombre si esta en la misma carpeta: ";
    std::cin >> archivocsv;

    std::ifstream archivo(archivocsv);
    if (!archivo) {
        std::cout << "Archivo no encontrado.\n";
        return 1;
    }

    std::string linea;
    std::getline(archivo, linea); // ignorar encabezado

    while (std::getline(archivo, linea) && AtletasTotales < 10) {
        std::string campos[5];
        int c = 0;
        for (size_t i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') c++;
            else campos[c] += linea[i];
        }

        nombres[AtletasTotales] = campos[0];
        paises[AtletasTotales] = campos[1];
        disciplinas[AtletasTotales] = campos[2];
        generos[AtletasTotales] = campos[3];
        medallas[AtletasTotales] = (campos[4].empty()) ? 0 : std::stoi(campos[4]);

        AtletasTotales++;
    }

    archivo.close();

    int opcion;
    do {
        std::cout << "\n1. Buscar un atleta por nombre\n";
        std::cout << "2. Calcular medallas de un pais\n";
        std::cout << "3. Mostrar atleta con más medallas\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1: {
                std::cout << "Ingrese el nombre del atleta: ";
                std::string nombreBuscado;
                std::getline(std::cin, nombreBuscado);

                bool encontrado = false;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (nombres[i] == nombreBuscado) {
                        std::cout << "Atleta: " << nombres[i] 
                                  << " | Pais: " << paises[i] 
                                  << " | Disciplina: " << disciplinas[i] 
                                  << " | Genero: " << generos[i] 
                                  << " | Medallas de oro: " << medallas[i] << "\n";
                        encontrado = true;
                    }
                }
                if (!encontrado) std::cout << "No se encontro el atleta.\n";
                break;
            }
            case 2: {
                std::cout << "Ingrese el nombre del pais: ";
                std::string BuscarPais;
                std::getline(std::cin, BuscarPais);

                int suma = 0;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (paises[i] == BuscarPais) suma += medallas[i];
                }
                std::cout << "El total de medallas de oro de " << BuscarPais << " es: " << suma << "\n";
                break;
            }
            case 3: {
                int MasMedallas = -1;
                std::string MejorAtleta;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (medallas[i] > MasMedallas) {
                        MasMedallas = medallas[i];
                        MejorAtleta = nombres[i];
                    }
                }
                if (MasMedallas >= 0)
                    std::cout << "El atleta con mas medallas de oro es: " << MejorAtleta << " con " << MasMedallas << " medallas.\n";
                else
                    std::cout << "No hay atletas registrados.\n";
                break;
            }
            case 4:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
        }

    } while(opcion != 4);

    return 0;
}