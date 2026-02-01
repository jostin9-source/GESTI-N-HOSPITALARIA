 #include <windows.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct MedicoEnfermera {
    string cedula, nombre, apellido, edad, celular, especialidad, turno;
};
struct Paciente{
	string cedula, nombre, apellido, edad, celular, nombreenfermedad, codigoenfermedad, gravedad, seguropaciente;
};
struct Consulta{
	string cedula, morprev, sintomas, presion, peso, altura, gravedadconsulta;
};
int opcionelegida() {
    int O;
    cout << "                GESTIÓN DE DATOS" << endl; 
    do {
        cout << "Seleccione:" << endl;
        cout << "[1] Menú Principal\n[2] Búsqueda" << endl; cin >> O;
        if (O != 1 && O != 2) {
            cout << "Opción inválida, ingrese de nuevo" << endl;
        }
    } while (O != 1 && O != 2);
    return O;
}

int asignacion(int opcion) {
    int oo;
    if (opcion == 1) {
        do {
            cout << "Seleccione:" << endl;
            cout << "[1] Gestión de Médicos\n[2] Gestión de Enfermeras\n[3] Gestión de Pacientes\n[4] Gestión de Consultas\n[5] Ordenamiento" << endl;
            cin >> oo;
        } while (oo < 1 || oo > 5);
    } else {
        do {
            cout << "Búsqueda por: " << endl;
            cout <<"[1] Cédula (médicos)\n" "[2] Cédula (enfermeras)\n" "[3] Apellido (medicos)\n" "[4] Apellido (enfermeras)\n" "[5] Edad (medico)\n" "[6] Edad (enfermeras)\n" "[7] Cédula (pacientes)\n" "[8] Enfermedad (pacientes)" <<endl;
            cin >> oo;
        } while (oo<1 || oo>8);
    }
    return oo;
}
//procesos medicos y enfermeras
//procedimiento registro medicos y enfermeras
void registrarmedicos(const string& nombreArchivo) {
    ofstream archivoEscritura(nombreArchivo, ios::app);
    if (archivoEscritura.is_open()) {
        MedicoEnfermera m;
        cin.ignore(); //limpiar
        cout << "    REGISTRO" << endl;
        cout << "Ingrese C.I (10 números): ";
        getline(cin, m.cedula);
        while(m.cedula.length() != 10) {
            cout << "ID inválido. Ingrese 10 números: ";
            getline(cin, m.cedula);
        }
        cout << "Ingrese nombres: "; getline(cin, m.nombre); cout << "Ingrese apellidos: "; getline(cin, m.apellido);
        cout << "Ingrese edad: "; getline(cin, m.edad);
         cout << "Ingrese Número Celular (10 números): ";
        getline(cin, m.celular);
        while(m.celular.length() != 10) {
            cout << "Celular inválido. Ingrese 10 números: ";
            getline(cin, m.celular);
        }
        cout << "Ingrese especialidad: "; getline(cin, m.especialidad); cout << "Ingrese horario de turno (HH)(ejm: 15,12,09): "; getline(cin, m.turno);
        archivoEscritura << m.cedula << ";" << m.nombre << ";" << m.apellido << ";" << m.edad << ";" << m.celular << ";" << m.especialidad << ";" << m.turno << "\n";
        archivoEscritura.close();
        cout << "Datos guardados correctamente\n" << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}
//procedimiento modificar medicos o enfermeras
void modificador(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    ofstream temporal("temp.csv"); // Archivo de paso
    string linea, cedulaBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la Cédula del Médico o Enfermera a modificar: ";
    cin.ignore();
    getline(cin, cedulaBuscar);
    while (getline(lectura, linea)) {
        stringstream ss(linea);
        string cedulaActual;
        getline(ss, cedulaActual, ';'); // Extraemos solo la cédula para comparar

        if (cedulaActual == cedulaBuscar) {
            encontrado = true;
            MedicoEnfermera m;
            m.cedula = cedulaActual; // Mantenemos la misma cédula
            cout << "--- Médico/Enfermera encontrado. Ingrese nuevos datos ---" << endl;
            cout << "Nuevo Nombre: "; getline(cin, m.nombre); cout << "Nuevo Apellido: "; getline(cin, m.apellido); cout << "Nueva Edad: "; getline(cin, m.edad);
            cout << "Nuevo Celular: "; getline(cin, m.celular); cout << "Nueva Especialidad: "; getline(cin, m.especialidad); cout << "Nuevo Turno: "; getline(cin, m.turno);
            // Escribimos los datos nuevos en el temporal
            temporal << m.cedula << ";" << m.nombre << ";" << m.apellido << ";" << m.edad << ";" << m.celular << ";" << m.especialidad << ";" << m.turno << "\n";
        } else {
            // Si no es el que buscamos, copiamos la línea tal cual
            temporal << linea <<endl;
        }
    }
    lectura.close();
    temporal.close();
    // Reemplazamos el archivo viejo por el nuevo
    remove(nombreArchivo.c_str());         // Borramos .csv
    rename("temp.csv", nombreArchivo.c_str()); // temp.csv=.csv
    if (encontrado) cout << "Modificado con éxito." << endl;
    else cout << "No se encontró el registro." << endl;
}
//caso eliminar medicos o enfermeras
void eliminador(const string& nombreArchivo){
	ifstream lectura(nombreArchivo);
	ofstream temporal("temp.csv");
	string linea, cedulabuscar;
	bool encontrado=false;
	if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
	cout<<"Ingrese número de Cédula a Eliminar"<<endl;
	cin.ignore();
	getline (cin, cedulabuscar);
	while (getline(lectura, linea)) {
        stringstream ss(linea);
        string cedulaactual;
        getline(ss, cedulaactual, ';');
        if(cedulabuscar==cedulaactual){
        	encontrado=true;
		}else{
			temporal<<linea<<endl;
		}
	}
	lectura.close();
	temporal.close();
	    if(encontrado){
         remove(nombreArchivo.c_str());
	     rename("temp.csv", nombreArchivo.c_str());
         cout<<"Encontrado y Eliminado"<<endl;
		}else{
			remove("temp.csv");
			cout<<"No Encontrado"<<endl;
		}
}
//caso mostrar datos medicos o enfermeras
void listado(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    if (!lectura.is_open()) {
        cout << "Error al Abrir el Archivo" << endl;
        return;
    }
    string linea;
    vector<MedicoEnfermera> lista;
    // 1. Leer el archivo y llenar el vector
    while (getline(lectura, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        MedicoEnfermera m;
        getline(ss, m.cedula, ';');
        getline(ss, m.nombre, ';');
        getline(ss, m.apellido, ';');
        getline(ss, m.edad, ';');
        getline(ss, m.celular, ';');
        getline(ss, m.especialidad, ';');
        getline(ss, m.turno, ';');
        lista.push_back(m);
    }
    lectura.close();
    //Método burbuja para ordenar por apellido A-Z
    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos el apellido actual con el siguiente
            if (lista[j].apellido > lista[j + 1].apellido) {
                // Intercambiamos los objetos completos
                MedicoEnfermera aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
    // 3. Imprimir el resultado
    printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ESPECIALIDAD", "TURNO");
    for (const auto& m : lista) {
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n", 
               m.cedula.c_str(), m.nombre.c_str(), m.apellido.c_str(), m.edad.c_str(), m.celular.c_str(), m.especialidad.c_str(), m.turno.c_str());
    }
}
//procesos pacientes
//procedimiento registro pacientes
void registrarpacientes(const string& nombreArchivo) {
    ofstream archivoEscritura(nombreArchivo, ios::app);
    if (archivoEscritura.is_open()) {
    	int seguro;
		Paciente p;
        cin.ignore(); //limpiar
        cout << "        REGISTRO DE PACIENTE" << endl;
        cout << "Ingrese C.I (10 números): ";
        getline(cin, p.cedula);
        while(p.cedula.length() != 10) {
            cout << "ID inválido. Ingrese 10 números: ";
            getline(cin, p.cedula);
        }
        cout << "Ingrese nombres: "; getline(cin, p.nombre); cout << "Ingrese apellidos: "; getline(cin, p.apellido);
        cout << "Ingrese edad: "; getline(cin, p.edad); cout << "Ingrese Número Celular (10 números): "; getline(cin, p.celular);
        while(p.celular.length() != 10) {
            cout << "Celular inválido. Ingrese 10 números: ";
            getline(cin, p.celular);
        }
        cout << "Ingrese nombre de enfermedad: "; getline(cin, p.nombreenfermedad); cout <<"Gravedad (1-10): "; getline(cin, p.gravedad);
        cout<<"¿El paciente posee seguro medico?"<<endl;
        cout<<"[1] SI\n[2] NO"<<endl;
        do{
        	cin>>seguro;
        	if(seguro<=0 || seguro>=3){
        		cout<<"Operación Inválida"<<endl;
			}
		}while(seguro<=0 || seguro>=3);
		cin.ignore();
		if(seguro==1){
			cout<<"Ingrese el seguro del paciente: "<<endl; getline(cin, p.seguropaciente);
		}else{
			cout<<""<<endl;
		}
        archivoEscritura << p.cedula << ";" << p.nombre << ";" << p.apellido << ";" << p.edad << ";"<< p.celular << ";" << p.nombreenfermedad << ";" << p.gravedad << ";" << p.seguropaciente << "\n";
        archivoEscritura.close();
        cout << "Datos guardados correctamente\n" << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
	}  
//procedimiento modificar pacientes
void modificador2(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    ofstream temporal("temp.csv"); // Archivo de paso
    string linea, cedulaBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la Cédula del Paciente a modificar: ";
    cin.ignore();
    getline(cin, cedulaBuscar);
    while (getline(lectura, linea)) {
        stringstream ss(linea);
        string cedulaActual;
        getline(ss, cedulaActual, ';'); // Extraccion de cédula para comparar

        if (cedulaActual == cedulaBuscar) {
            encontrado = true;
            Paciente p;
            p.cedula = cedulaActual; // Mantenemos la misma cédula
            cout << "   Paciente encontrado. Ingrese nuevos datos" << endl;
            cout << "Nuevo Nombre: "; getline(cin, p.nombre); cout << "Nuevo Apellido: "; getline(cin, p.apellido); cout << "Nueva Edad: "; getline(cin, p.edad); cout << "Nuevo Celular: "; getline(cin, p.celular);
            cout << "Nueva Enfermedad: "; getline (cin, p.nombreenfermedad); cout << "Nueva gravedad (1-10): "; getline(cin, p.gravedad); cout << "Nuevo Turno: "; getline(cin, p.seguropaciente);
            // Escribimos los datos nuevos en el temporal
            temporal << p.cedula << ";" << p.nombre << ";" << p.apellido << ";" << p.edad << ";"<< p.celular << ";" << p.nombreenfermedad << ";" << p.gravedad << ";" << p.seguropaciente << "\n";     
			} else {
            // Si no es el que buscamos, copiamos la línea tal cual
            temporal << linea <<endl; 
        }
    }
    lectura.close();
    temporal.close();
    // Reemplazamos el archivo viejo por el nuevo
    remove(nombreArchivo.c_str());         // Borramos pacientes.csv
    rename("temp.csv", nombreArchivo.c_str()); // temp.csv=pacientes.csv

    if (encontrado) cout << "Modificado con éxito." << endl;
    else cout << "No se encontró el registro." << endl;
}
//caso mostrar datos paciente
void listado2(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    if (!lectura.is_open()) {
        cout << "Error al Abrir el Archivo" << endl;
        return;
    }
    string linea;
    vector<Paciente> lista;
    // 1. Leer el archivo y llenar el vector
    while (getline(lectura, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        Paciente p;
        getline(ss, p.cedula, ';');
        getline(ss, p.nombre, ';');
        getline(ss, p.apellido, ';');
        getline(ss, p.edad, ';');
        getline(ss, p.celular, ';');
        getline(ss, p.nombreenfermedad, ';');
        getline(ss, p.gravedad, ';');
        getline(ss, p.seguropaciente, ';');
        lista.push_back(p);
    }
    lectura.close();
    //Método burbuja para ordenar por apellido A-Z
    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos el apellido actual con el siguiente
            if (lista[j].apellido > lista[j + 1].apellido) {
                // Intercambiamos los objetos completos
                Paciente aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
    // 3. Imprimir el resultado
    printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ENFERMEDAD", "GRAVEDAD", "SEGURO");
    for (const auto& p : lista) {
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n", 
               p.cedula.c_str(), p.nombre.c_str(), p.apellido.c_str(), p.edad.c_str(), p.celular.c_str(), p.nombreenfermedad.c_str(), p.gravedad.c_str(), p.seguropaciente.c_str());
    }
}
//bandera encontrar pacientes para consultas
	bool existePaciente(const string& ArchivoPacientes, const string& cedulaBuscar) {
    ifstream lectura(ArchivoPacientes);
    string linea;
    if (!lectura.is_open()) return false;
    while (getline(lectura, linea)) {
        stringstream ss(linea);
        string cedulaActual;
        getline(ss, cedulaActual, ';');
        if (cedulaActual == cedulaBuscar) {
            lectura.close();
            return true;
        }
    }
    lectura.close();
    return false;
}
	//proceso registrar consultas
void registrarconsultas(const string& nombreArchivoConsultas, const string& nombreArchivoPacientes) {
    ofstream archivoEscritura(nombreArchivoConsultas, ios::app);
    if (archivoEscritura.is_open()) {
		Consulta c;
		string cedula;
        cin.ignore(); //limpiar
        cout << "        REGISTRO DE CONSULTAS" << endl;
        cout << "Ingrese C.I (10 números): ";
        getline(cin, cedula);
        while(cedula.length() != 10) {
            cout << "ID inválido. Ingrese 10 números: ";
            getline(cin, cedula);
        }
        if (existePaciente(nombreArchivoPacientes, cedula)) {
        c.cedula=cedula;         
        cout << "Paciente encontrado" << endl;
        cout << "Consulta por (morbilidad/prevención): "; getline(cin, c.morprev); cout << "Ingrese síntomas: "; getline(cin, c.sintomas);
        cout << "Ingrese presion: "; getline(cin, c.presion); cout << "Ingrese peso: "; getline(cin, c.peso);
        cout << "Ingrese altura: "; getline(cin, c.altura); cout <<"Gravedad  de Consulta (1-10): "; getline(cin, c.gravedadconsulta);
        archivoEscritura << c.cedula << ";" << c.morprev << ";" << c.sintomas << ";" << c.presion << ";"<< c.peso << ";" << c.altura << ";" << c.gravedadconsulta << "\n";
        archivoEscritura.close();
        cout << "Datos guardados correctamente\n" << endl;
    } else {
        cout << "ERROR: El paciente no existe en el sistema." << endl;
    }
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}
    //proceso modificar consultas
    void modificador3(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    ofstream temporal("temp.csv"); // Archivo de paso
    string linea, cedulaBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la Cédula del paciente para modificar consulta: ";
    cin.ignore();
    getline(cin, cedulaBuscar);
    while (getline(lectura, linea)) {
        stringstream ss(linea);
        string cedulaActual;
        getline(ss, cedulaActual, ';'); // Extraccion de cédula para comparar
        if (cedulaActual == cedulaBuscar) {
            encontrado = true;
            Consulta c;
            c.cedula = cedulaActual; // Mantenemos la misma cédula
            cout << "   Paciente encontrado. Ingrese nuevos datos" << endl;
            cout << "Consulta por: "; getline(cin, c.morprev); cout << "Sintomas: "; getline(cin, c.sintomas); cout << "Presion: "; getline(cin, c.presion); cout<<"Peso: "; getline(cin, c.peso);
			cout << "Altura: "; getline(cin, c.altura);
            cout << "Gravedad: "; getline (cin, c.gravedadconsulta);
            // Escribimos los datos nuevos en el temporal
            temporal<< c.cedula << ";" << c.morprev << ";" << c.sintomas << ";" << c.presion << ";" << c.peso << ";" << c.altura << ";"<< c.gravedadconsulta << "\n";     
			} else {
            // Si no es el que buscamos, copiamos la línea tal cual
            temporal << linea <<endl; 
        }
    }
    lectura.close();
    temporal.close();
    // Reemplazamos el archivo viejo por el nuevo
    remove(nombreArchivo.c_str());         // Borramos cosultas.csv
    rename("temp.csv", nombreArchivo.c_str()); // temp.csv=consultas.csv

    if (encontrado) cout << "Modificado con éxito." << endl;
    else cout << "No se encontró el registro." << endl;
}
//procedimiento ver listado de consultas
void listado3(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    if (!lectura.is_open()) {
        cout << "Error al Abrir el Archivo" << endl;
        return;
    }
    string linea;
    vector<Consulta> lista;
    // 1. Leer el archivo y llenar el vector
    while (getline(lectura, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        Consulta c;
        getline(ss, c.cedula, ';');
        getline(ss, c.morprev, ';');
        getline(ss, c.sintomas, ';');
        getline(ss, c.presion, ';');
        getline(ss, c.peso, ';');
        getline(ss, c.altura, ';');
        getline(ss, c.gravedadconsulta, ';');
        lista.push_back(c);
    }
    lectura.close();
    //Método burbuja para ordenar por apellido A-Z
    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos el apellido actual con el siguiente
            if (lista[j].gravedadconsulta < lista[j + 1].gravedadconsulta) {
                // Intercambiamos los objetos completos
                Consulta aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
    // 3. Imprimir el resultado
    printf("%-23s %-23s %-23s %-15s %-15s %-23s %-8s\n","CÉDULA", "TIPO CONSULTA", "SÍNTOMAS", "PRESIÓN", "PESO", "ALTURA", "GRAVEDAD CONSULTA");
    for (const auto& c : lista) {
        printf("%-23s %-23s %-23s %-15s %-15s %-23s %-8s\n", 
               c.cedula.c_str(), c.morprev.c_str(), c.sintomas.c_str(), c.presion.c_str(), c.peso.c_str(), c.altura.c_str(), c.gravedadconsulta.c_str());
    }
}
//ordenamiento pacientes edad
void ordenamientoP(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    if (!lectura.is_open()) {
        cout << "Error al Abrir el Archivo" << endl;
        return;
    }
    string linea;
    vector<Paciente> lista;
    // 1. Leer el archivo y llenar el vector
    while (getline(lectura, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        Paciente p;
        getline(ss, p.cedula, ';');
        getline(ss, p.nombre, ';');
        getline(ss, p.apellido, ';');
        getline(ss, p.edad, ';');
        getline(ss, p.celular, ';');
        getline(ss, p.nombreenfermedad, ';');
        getline(ss, p.gravedad, ';');
        getline(ss, p.seguropaciente, ';');
        lista.push_back(p);
    }
    lectura.close();
    //Método burbuja para ordenar por apellido A-Z
    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos el apellido actual con el siguiente
            if (lista[j].edad > lista[j + 1].edad) {
                // Intercambiamos los objetos completos
                Paciente aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
    // 3. Imprimir el resultado
    printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ENFERMEDAD", "GRAVEDAD", "SEGURO");
    for (const auto& p : lista) {
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n", 
               p.cedula.c_str(), p.nombre.c_str(), p.apellido.c_str(), p.edad.c_str(), p.celular.c_str(), p.nombreenfermedad.c_str(), p.gravedad.c_str(), p.seguropaciente.c_str());
    }
}
//ordenamiento doctore/enfermeras
void ordenamientoME(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    if (!lectura.is_open()) {
        cout << "Error al Abrir el Archivo" << endl;
        return;
    }
    string linea;
    vector<MedicoEnfermera> lista;
    // 1. Leer el archivo y llenar el vector
    while (getline(lectura, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        MedicoEnfermera m;
        getline(ss, m.cedula, ';');
        getline(ss, m.nombre, ';');
        getline(ss, m.apellido, ';');
        getline(ss, m.edad, ';');
        getline(ss, m.celular, ';');
        getline(ss, m.especialidad, ';');
        getline(ss, m.turno, ';');
        lista.push_back(m);
    }
    lectura.close();
    //Método burbuja para ordenar por apellido A-Z
    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos el apellido actual con el siguiente
            if (lista[j].edad > lista[j + 1].edad) {
                // Intercambiamos los objetos completos
                MedicoEnfermera aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
    // 3. Imprimir el resultado
    printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ESPECIALIDAD", "TURNO");
    for (const auto& m : lista) {
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n", 
               m.cedula.c_str(), m.nombre.c_str(), m.apellido.c_str(), m.edad.c_str(), m.celular.c_str(), m.especialidad.c_str(), m.turno.c_str());
    }
}
//procedimeinto busqueda cedula medico/enfermera
void busquedacedula(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    string linea, cedulaBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la Cédula del Médico o Enfermera a buscar: ";
    cin.ignore();
    cin>>cedulaBuscar;
    while (getline(lectura, linea)) {
    	stringstream ss(linea);
        MedicoEnfermera m;
        getline(ss, m.cedula, ';'); 
        getline(ss, m.nombre, ';');
        getline(ss, m.apellido, ';');
        getline(ss, m.edad, ';');
        getline(ss, m.celular, ';');
        getline(ss, m.especialidad, ';');
        getline(ss, m.turno, ';');

        if (m.cedula == cedulaBuscar) {
        cout << "INFORMACIÓN ENCONTRADA"<<endl;
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ESPECIALIDAD", "TURNO");
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n", 
        m.cedula.c_str(), m.nombre.c_str(), m.apellido.c_str(), m.edad.c_str(), m.celular.c_str(), m.especialidad.c_str(), m.turno.c_str());
			encontrado = true;
			} 
    }
    lectura.close();
    if (encontrado) cout << "Búsqueda exitosa" << endl;
    else cout << "No se encontró el registro." << endl;
}
//procedimiento busqueda apellido medico/enfermera
void busquedaapellido(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    string linea, apellidoBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese el Apellido del Médico o Enfermera a buscar: ";
    cin.ignore();
    cin>>apellidoBuscar;
    while (getline(lectura, linea)) {
    	stringstream ss(linea);
        MedicoEnfermera m;
        getline(ss, m.cedula, ';'); 
        getline(ss, m.nombre, ';');
        getline(ss, m.apellido, ';');
        getline(ss, m.edad, ';');
        getline(ss, m.celular, ';');
        getline(ss, m.especialidad, ';');
        getline(ss, m.turno, ';');

        if (m.apellido == apellidoBuscar) {
        cout << "INFORMACIÓN ENCONTRADA"<<endl;
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ESPECIALIDAD", "TURNO");
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n", 
        m.cedula.c_str(), m.nombre.c_str(), m.apellido.c_str(), m.edad.c_str(), m.celular.c_str(), m.especialidad.c_str(), m.turno.c_str());
			encontrado = true;
			} 
    }
    lectura.close();
    if (encontrado) cout << "Búsqueda exitosa" << endl;
    else cout << "No se encontró el registro." << endl;
}
//procedimiento busqueda edad medicos/enfermeras
void busquedaedad(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    string linea, edadBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese edad del Médico o Enfermera a buscar: ";
    cin.ignore();
    cin>>edadBuscar;
    while (getline(lectura, linea)) {
    	stringstream ss(linea);
        MedicoEnfermera m;
        getline(ss, m.cedula, ';'); 
        getline(ss, m.nombre, ';');
        getline(ss, m.apellido, ';');
        getline(ss, m.edad, ';');
        getline(ss, m.celular, ';');
        getline(ss, m.especialidad, ';');
        getline(ss, m.turno, ';');

        if (m.edad == edadBuscar) {
        cout << "INFORMACIÓN ENCONTRADA"<<endl;
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ESPECIALIDAD", "TURNO");
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-8s\n", 
        m.cedula.c_str(), m.nombre.c_str(), m.apellido.c_str(), m.edad.c_str(), m.celular.c_str(), m.especialidad.c_str(), m.turno.c_str());
			encontrado = true;
			} 
    }
    lectura.close();
    if (encontrado) cout << "Búsqueda exitosa" << endl;
    else cout << "No se encontró el registro." << endl;
}
//procedimiento busqueda pacientes cedula
void busquedapacientes(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    string linea, cedulaBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la Cédula del paciente a buscar: ";
    cin.ignore();
    cin>>cedulaBuscar;
    while (getline(lectura, linea)) {
    	stringstream ss(linea);
        Paciente p;
        getline(ss, p.cedula, ';');
        getline(ss, p.nombre, ';');
        getline(ss, p.apellido, ';');
        getline(ss, p.edad, ';');
        getline(ss, p.celular, ';');
        getline(ss, p.nombreenfermedad, ';');
        getline(ss, p.gravedad, ';');
        getline(ss, p.seguropaciente, ';');

        if (p.cedula == cedulaBuscar) {
        cout << "INFORMACIÓN ENCONTRADA"<<endl;
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ENFERMEDAD", "GRAVEDAD", "SEGURO");
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n", 
        p.cedula.c_str(), p.nombre.c_str(), p.apellido.c_str(), p.edad.c_str(), p.celular.c_str(), p.nombreenfermedad.c_str(), p.gravedad.c_str(), p.seguropaciente.c_str());
			encontrado = true;
			} 
    }
    lectura.close();
    if (encontrado) cout << "Búsqueda exitosa" << endl;
    else cout << "No se encontró el registro." << endl;
}
//procedimiento busqueda enfermedad paciente
void busquedaenfermedad(const string& nombreArchivo) {
    ifstream lectura(nombreArchivo);
    string linea, enferBuscar;
    bool encontrado = false;
    if (!lectura.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }
    cout << "Ingrese la enfermedad del paciente a buscar: ";
    cin.ignore();
    cin>>enferBuscar;
    while (getline(lectura, linea)) {
    	stringstream ss(linea);
        Paciente p;
        getline(ss, p.cedula, ';');
        getline(ss, p.nombre, ';');
        getline(ss, p.apellido, ';');
        getline(ss, p.edad, ';');
        getline(ss, p.celular, ';');
        getline(ss, p.nombreenfermedad, ';');
        getline(ss, p.gravedad, ';');
        getline(ss, p.seguropaciente, ';');

        if (p.nombreenfermedad == enferBuscar) {
        cout << "INFORMACIÓN ENCONTRADA"<<endl;
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n","CÉDULA", "NOMBRE", "APELLIDO", "EDAD", "NÚMERO CELULAR", "ENFERMEDAD", "GRAVEDAD", "SEGURO");
        printf("%-23s %-23s %-23s %-8s %-23s %-23s %-23s %-8s\n", 
        p.cedula.c_str(), p.nombre.c_str(), p.apellido.c_str(), p.edad.c_str(), p.celular.c_str(), p.nombreenfermedad.c_str(), p.gravedad.c_str(), p.seguropaciente.c_str());
			encontrado = true;
			} 
    }
    lectura.close();
    if (encontrado) cout << "Búsqueda exitosa" << endl;
    else cout << "No se encontró el registro." << endl;
}
//funcion de cada caso
int casosopcion(int opcionprincipal, int opcion){
    string archivo = "medicos.csv";
    string archivo1= "enfermeras.csv";
    string archivo2= "pacientes.csv";
    string archivo3= "consultas.csv";
	int opcion1, opcion2, opcion3, opcion4, opcion5;
    if(opcionprincipal==1){
	switch (opcion){
	case 1: 
        do {
            cout << "Seleccione una:" << endl;
            cout << "[1] Registrar Nuevo\n[2] Modificar Datos\n[3] Eliminar\n[4] Ver Listado Completo\n[5] Volver al Menú Principal" << endl;
            cin >> opcion1;
        } while (opcion1 < 1 || opcion1 > 5);
        switch (opcion1) {
            case 1:
                registrarmedicos(archivo);
                break;
            case 2:
                modificador(archivo);
				break;	
			case 3:
			    eliminador(archivo);
			    break;
			case 4:
				listado(archivo);
				break;		
            // mas casos
        }
        break;
    case 2:
	    do {
            cout << "Seleccione una:" << endl;
            cout << "[1] Registrar Nuevo\n[2] Modificar Datos\n[3] Eliminar\n[4] Ver Listado Completo\n[5] Volver al Menú Principal" << endl;
            cin >> opcion2;
        } while (opcion2< 1 || opcion2> 5);
        switch (opcion2) {
            case 1:
                registrarmedicos(archivo1);
                break;
            case 2:
                modificador(archivo1);
				break;	
			case 3:
			    eliminador(archivo1);
			    break;
			case 4:
				listado(archivo1);
				break;		
            // mas casos
        }
        break;
    case 3:
    	do{
    		cout<<"Seleccione una: "<<endl;
    		cout << "[1] Registrar Nuevo\n[2] Modificar Datos\n[3] Eliminar\n[4] Ver Listado Completo\n[5] Volver al Menú Principal" << endl;
            cin>>opcion3;  
		}while(opcion3<1 || opcion3>5);
		switch (opcion3) {
            case 1:
                registrarpacientes(archivo2);
                break;
            case 2:
                modificador2(archivo2);
				break;	
			case 3:
			    eliminador(archivo2);
			    break;
			case 4:
				listado2(archivo2);
				break;		
            // mas casos
        }
        break;
    case 4:
	    do{
    		cout<<"Seleccione una: "<<endl;
    		cout << "[1] Registrar Nuevo\n[2] Modificar Datos\n[3] Eliminar\n[4] Ver Listado Completo\n[5] Volver al Menú Principal" << endl;
            cin>>opcion4;  
		}while(opcion4<1 || opcion4>5);
		switch (opcion4) {
            case 1:
                registrarconsultas(archivo3, archivo2);
                break;
            case 2:
                modificador3(archivo3);
				break;	
			case 3:
			    eliminador(archivo3);
			    break;
			case 4:
				listado3(archivo3);
				break;		
            // mas casos
        }
        break;
    case 5:
    	 do{
    		cout<<"Seleccione una: "<<endl;
    		cout << "[1] Ascendente por edad (pacientes)\n[2] Ascendete por edad (medicos)\n[3] Ascendente por edad (enfermeras)\n[4] Volver al Menú Principal" << endl;
            cin>>opcion5;  
		}while(opcion5<1 || opcion5>4);
		switch (opcion5) {
            case 1:
                ordenamientoP(archivo2);
                break;
            case 2:
                ordenamientoME(archivo);
				break;	
			case 3:
			    ordenamientoME(archivo1);
			    break;
            // mas casos
        }
        break;
    }
}else{
	switch (opcion){
		case 1:
			busquedacedula(archivo);
			break;
		case 2:
			busquedacedula(archivo1);
			break;
		case 3:
		    busquedaapellido(archivo);
		    break;
		case 4:
			busquedaapellido(archivo1);
			break;
		case 5:
			busquedaedad(archivo);
			break;
		case 6:
			busquedaedad(archivo1);
			break;
		case 7:
			busquedapacientes(archivo2);
			break;
		case 8:
			busquedaenfermedad(archivo2);
			break;
	}
}
    return 0;
}
int main() {
    SetConsoleOutputCP(65001);
    bool ejecutar = true;
    while (ejecutar) { 
        int opcionprincipal = opcionelegida();
        int segundaopcion = asignacion(opcionprincipal);
		int todosLOScasos=casosopcion(opcionprincipal, segundaopcion);
        cout << "¿Desea realizar otra operación? (1: Sí / 0: Salir): ";
        int respuesta;
        cin >> respuesta;
        if (respuesta == 0) {
            ejecutar = false; 
        }
        system("cls"); //limpia pantalla 
    }
    return 0;
}