#include <iostream>
#include <string>

using namespace std;

class Contacto {
public:
    string nombre;
    string telefono;

    Contacto() : nombre(""), telefono("") {}

    Contacto(string n, string t) : nombre(n), telefono(t) {}

    bool estaVacio() const {
        return nombre == "";
    }

    bool fueEliminado() const {
        return nombre == "ELIMINADO";
    }
};

class TablaHash {
private:
    Contacto* tabla;
    int tamano;
    int numContactos;

    int hashFunc(const string& nombre) {
        int hash = 0;
        for (char c : nombre) {
            hash += c;}
        return hash % tamano;
    }
public:
    TablaHash(int tam) : tamano(tam), numContactos(0) {
        tabla = new Contacto[tam];
    }
    ~TablaHash() {
        delete[] tabla;
    }
    void insertarContacto(const string& nombre, const string& telefono) {
        if (numContactos >= tamano) {
            cout << "Tabla hash llena, no se puede insertar más contactos." << endl;
            return;}
        int indice = hashFunc(nombre);
        while (!tabla[indice].estaVacio() && !tabla[indice].fueEliminado()) {
            indice = (indice + 1) % tamano;}

        tabla[indice] = Contacto(nombre, telefono);
        numContactos++;
    }

    string buscarContacto(const string& nombre) {
        int indice = hashFunc(nombre);
        while (!tabla[indice].estaVacio()) {
            if (tabla[indice].nombre == nombre) {
                return tabla[indice].telefono;}
            indice = (indice + 1) % tamano;}
        return "Contacto no encontrado.";
    }
    void eliminarContacto(const string& nombre) {
        int indice = hashFunc(nombre);
        while (!tabla[indice].estaVacio()) {
            if (tabla[indice].nombre == nombre) {
                tabla[indice].nombre = "ELIMINADO";
                tabla[indice].telefono = "";
                numContactos--;
                cout << "Contacto eliminado: " << nombre << endl;
                return;}
            indice = (indice + 1) % tamano;}
        cout << "Contacto no encontrado." << endl;
    }
    void mostrarAgenda() {
        for (int i = 0; i < tamano; ++i) {
            if (!tabla[i].estaVacio() && !tabla[i].fueEliminado()) {
                cout << "Posición " << i << ": " << tabla[i].nombre << " (" << tabla[i].telefono << ")" << endl;
            }
        }
    }
};

int main() {
    TablaHash agenda(10);

    agenda.insertarContacto("Alice", "123-456-7890");
    agenda.insertarContacto("Bob", "987-654-3210");
    agenda.insertarContacto("Charlie", "555-555-5555");
    agenda.insertarContacto("David", "444-444-4444");

int opcion;
    string nombre, telefono;

    do {
        cout << "Menú de la Agenda de Contactos:" << endl;
        cout << "1. Insertar contacto" << endl;
        cout << "2. Buscar contacto" << endl;
        cout << "3. Eliminar contacto" << endl;
        cout << "4. Mostrar agenda" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();  // Para ignorar el salto de línea después de la entrada numérica

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre del contacto: ";
                getline(cin, nombre);
                cout << "Ingrese el número de teléfono: ";
                getline(cin, telefono);
                agenda.insertarContacto(nombre, telefono);
                break;
            case 2:
                cout << "Ingrese el nombre del contacto a buscar: ";
                getline(cin, nombre);
                agenda.buscarContacto(nombre);
                break;
            case 3:
                cout << "Ingrese el nombre del contacto a eliminar: ";
                getline(cin, nombre);
                agenda.eliminarContacto(nombre);
                break;
            case 4:
                agenda.mostrarAgenda();
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                break;
        }
        cout << endl;
    } while (opcion != 0);
    return 0;
}
