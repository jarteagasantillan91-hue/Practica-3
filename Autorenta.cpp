#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Inspeccionable {
public:
    virtual void inspeccionar() = 0;
};

class Vehiculo : public Inspeccionable {
protected:
    string placa;
    string marca;
    string modelo;
    int anio;
    double tarifaDia;

public:
    Vehiculo(string _placa, string _marca, string _modelo, int _anio, double _tarifa)
        : placa(_placa), marca(_marca), modelo(_modelo), anio(_anio), tarifaDia(_tarifa) {
        if (_anio < 0 || _anio > 2026) throw invalid_argument("Año inválido");
    }

    string getPlaca() const { return placa; }
    void setMarca(string _marca) { marca = _marca; }
    void setModelo(string _modelo) { modelo = _modelo; }
    void setAnio(int _anio) {
        if (_anio > 0 && _anio <= 2026) anio = _anio;
    }
    void setTarifaDia(double _tarifa) { tarifaDia = _tarifa; }

    virtual void mostrarInfo() const {
        cout << "Placa: " << placa << " | Marca: " << marca << " | Modelo: " << modelo
             << " | Año: " << anio << " | Tarifa/día: " << tarifaDia << endl;
    }

    virtual double calcularCosto(int dias) const = 0;
};

class Automovil : public Vehiculo {
    int pasajeros;
public:
    Automovil(string p, string m, string mo, int a, double t, int pas)
        : Vehiculo(p,m,mo,a,t), pasajeros(pas) {}

    double calcularCosto(int dias) const override {
        return tarifaDia * dias;
    }

    void inspeccionar() override {
        cout << "Inspeccion de automovil: revisar llantas y frenos." << endl;
    }
};

class Motocicleta : public Vehiculo {
    int cilindrada;
public:
    Motocicleta(string p, string m, string mo, int a, double t, int cil)
        : Vehiculo(p,m,mo,a,t), cilindrada(cil) {}

    double calcularCosto(int dias) const override {
        return (tarifaDia * dias) * 0.9; // 10% descuento
    }

    void inspeccionar() override {
        cout << "Inspeccion de motocicleta: revisar cadena y nivel de aceite." << endl;
    }
};

class Camioneta : public Vehiculo {
    double capacidadCarga;
public:
    Camioneta(string p, string m, string mo, int a, double t, double cap)
        : Vehiculo(p,m,mo,a,t), capacidadCarga(cap) {}

    double calcularCosto(int dias) const override {
        return (tarifaDia * dias) + 50; // recargo fijo
    }

    void inspeccionar() override {
        cout << "Inspeccion de camioneta: revisar suspension y carga maxima." << endl;
    }
};

int main() {
    
    Vehiculo* v1 = new Automovil("ABC123","Toyota","Corolla",2020,100,5);
    Vehiculo* v2 = new Motocicleta("XYZ456","Honda","CBR",2021,80,250);
    Vehiculo* v3 = new Camioneta("LMN789","Ford","Ranger",2022,150,1000);

    v1->mostrarInfo(); cout << "Costo: " << v1->calcularCosto(3) << endl; v1->inspeccionar();
    v2->mostrarInfo(); cout << "Costo: " << v2->calcularCosto(3) << endl; v2->inspeccionar();
    v3->mostrarInfo(); cout << "Costo: " << v3->calcularCosto(3) << endl; v3->inspeccionar();

    delete v1; delete v2; delete v3;
    return 0;
}