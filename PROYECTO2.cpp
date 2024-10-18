#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> cargar(const string& archivo) {
    vector<string> prod;
    ifstream file(archivo);
    string p;
    while (getline(file, p)) {
        prod.push_back(p);
    }
    file.close();
    return prod;
}

void guardar(const string& archivo, const vector<string>& prod) {
    ofstream file(archivo);
    for (const auto& p : prod) {
        file << p << endl;
    }
    file.close();
}

void mostrar(const vector<string>& prod) {
    cout << "Tus productos en el carrito:\n";
    for (size_t i = 0; i < prod.size(); ++i) {
        cout << i + 1 << ". " << prod[i] << endl;
    }
}

void agregar(vector<string>& prod) {
    string p;
    cout << "ingresa el nombre del producto que quieres agregar: ";
    getline(cin >> ws, p);
    prod.push_back(p);
    cout << "Producto agregado\n";
}

void eliminar(vector<string>& prod) {
    int idx;
    mostrar(prod);
    cout << "Dime el número del producto que quieres eliminar: ";
    cin >> idx;

    if (idx > 0 && idx <= prod.size()) {
        prod.erase(prod.begin() + (idx - 1));
        cout << "Producto eliminado.\n";
    }
    else {
        cout << "No existe un producto con ese numero.\n";
    }
}

bool admin() {
    string clave;
    cout << "Eres administrador? (s/n): ";
    char r;
    cin >> r;
    if (r == 's' || r == 'S') {
        cout << "Introduce la clave de admin: ";
        cin >> clave;
        if (clave == "admin123") {
            return true;
        }
        else {
            cout << "Clave incorrecta. Intenta otra vez.\n";
        }
    }
    return false;
}

int main() {
    const string archivo = "productos.txt";
    vector<string> prod = cargar(archivo);
    bool esAdmin = admin();
    int op;

    do {
        cout << "\n--- Carrito de Compras ---\n";
        mostrar(prod);
        cout << "\n1. Agregar producto\n";
        if (esAdmin) {
            cout << "2. Eliminar producto\n";
        }
        cout << "3. Salir\n";
        cout << "Elige una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            agregar(prod);
            break;
        case 2:
            if (esAdmin) {
                eliminar(prod);
            }
            else {
                cout << "Esa opción no esta disponible si no eres admin.\n";
            }
            break;
        case 3:
            guardar(archivo, prod);
            cout << "Carrito guardado.\n";
            break;
        default:
            cout << "Opción no valida.\n";
        }
    } while (op != 3);

    return 0;
}