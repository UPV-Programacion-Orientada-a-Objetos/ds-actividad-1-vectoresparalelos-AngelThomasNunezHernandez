#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    string nombres[100];
    string paises[100];
    string disciplinas[100];
    string generos[100];
    int medallas[100];
    int AtletasTotales = 0;

    string archivocsv;
    cout << "Ruta del archivo CSV o Nombre si esta en la misma carpeta: ";
    cin >> archivocsv;

    ifstream archivo(archivocsv);
    if (!archivo) {
        cout << "No encontrado\n";
        return 1;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea) && AtletasTotales < 10) {
        string campos[5];
        int c = 0;
        for (int i = 0; i < (int)linea.size(); i++) {
            if (linea[i] == ',') c++;
            else campos[c] += linea[i];
        }

        nombres[AtletasTotales] = campos[0];
        paises[AtletasTotales] = campos[1];
        disciplinas[AtletasTotales] = campos[2];
        generos[AtletasTotales] = campos[3];
        medallas[AtletasTotales] = (campos[4].empty()) ? 0 : stoi(campos[4]);

        AtletasTotales++;
    }

    archivo.close();

    int opcion;
    do {
        cout << "1. Buscar un atleta por nombre\n";
        cout << "2. Calcular medallas de un pais\n";
        cout << "3. Mostrar atleta con más medallas\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                cout << "Ingrese el nombre del atleta: ";
                string nombreBuscado;
                getline(cin, nombreBuscado);

                bool encontrado = false;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (nombres[i] == nombreBuscado) {
                        cout << "Atleta: " << nombres[i] 
                             << "Pais: " << paises[i] 
                             << "Disciplina: " << disciplinas[i] 
                             << "Genero: " << generos[i] 
                             << "Medallas de oro: " << medallas[i] << "\n";
                        encontrado = true;
                    }
                }
                if (!encontrado) cout << "No se encontro el atleta.\n";
                break;
            }
            case 2: {
                cout << "Ingrese el nombre del pais: ";
                string BuscarPais;
                getline(cin, BuscarPais);

                int suma = 0;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (paises[i] == BuscarPais) suma += medallas[i];
                }
                cout << "El total de medallas de oro de " << BuscarPais << " es: " << suma << "\n";
                break;
            }
            case 3: {
                int MasMedallas = -1;
                string MejorAtleta;
                for (int i = 0; i < AtletasTotales; i++) {
                    if (medallas[i] > MasMedallas) {
                        MasMedallas= medallas[i];
                        MejorAtleta = nombres[i];
                    }
                }
                if (MasMedallas >= 0)
                    cout << "El atleta con mas medallas de oro es: " << MejorAtleta << " con " << MasMedallas << " medallas.\n";
                else
                    cout << "No hay atletas registrados.\n";
                break;
            }
            case 4:
                break;
            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 4);

    return 0;
}
