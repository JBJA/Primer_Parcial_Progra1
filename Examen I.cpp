// Josué Benjamín Juárez Arevalo
// Carnet: 1290-20-1186
// Primer Parcial Programacion 1

#include<iostream>
#include<stdio.h>
#include<string.h>
#define VALOR_CENTINELA -1

using namespace std;

const char *nombre_archivo = "archivo.dat";
struct Empleado{
	int codigo;
	char nombres[50];
	char apellidos[50];
	char puesto[50];
	int sueldo;
	int bonificacion=250;
	int sueldo_total=sueldo+bonificacion;
};

// Menu principal
void menu(){
	cout<<" ________________________________________"<<endl;
	cout<<"|                                        |"<<endl;
	cout<<"|   CONTROL DEL PERSONAL DE LA EMPRESA   |"<<endl;
	cout<<"|________________________________________|"<<endl;	
	cout<<"|                                        |"<<endl;
	cout<<"|    1. Ver datos                        |"<<endl;
	cout<<"|________________________________________|"<<endl;	
	cout<<"|                                        |"<<endl;	
	cout<<"|    2. Ingresar nuevo                   |"<<endl;
	cout<<"|________________________________________|"<<endl;	
	cout<<"|                                        |"<<endl;	
	cout<<"|    3. Buscar                           |"<<endl;
	cout<<"|________________________________________|"<<endl;
	cout<<"|                                        |"<<endl;	
	cout<<"|    4. Modificar                        |"<<endl;
	cout<<"|________________________________________|"<<endl;
	cout<<"|                                        |"<<endl;	
	cout<<"|    5. Eliminar                         |"<<endl;
	cout<<"|________________________________________|"<<endl;
	cout<<"|                                        |"<<endl;	
	cout<<"|    6. Salir                            |"<<endl;
	cout<<"|________________________________________|"<<endl;
}

void abrir();
void ingresar();
void modificar();
void buscar_codigo();
void calcular();
void eliminar();

main()
{
int opcion = 0;

while(opcion != 6){
	system("cls");
	menu();
	cout<<"\nOpcion: ";
	cin>>opcion;
	
	if(opcion==1){
		abrir();
		system("pause");
	}
	
	if(opcion==2){
		ingresar();
		system("pause");
	}
	
	if(opcion==3){
		buscar_codigo();
		system("pause");
	}
	
	if(opcion==4){
		abrir();
		modificar();
		system("pause");
	}
		
	if(opcion==5){
		abrir();
		eliminar();
		system("pause");
	}
}
		
	return 0;
}


void abrir(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	// condiciona si existe el archivo
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");;
	}
	
	Empleado empleado;
	int registro = 0;
	int pago;
	fread(&empleado,sizeof(Empleado),1,archivo);
cout<<"_____________________________________________________________________________________"<<endl;
cout<<"id | "<<"Codigo | "<<"Nombres     |     "<<"Apellidos     |     "<<"Sueldo   |   "<<"Bonificacion  |  "<<"Sueldo Total  |  "<<endl;

	// Recorrer el archivo
	do{
		cout<<"___________________________________________________________________________________"<<endl;
		cout<<registro<<" | "<<empleado.codigo<<" | "<<empleado.nombres<<" | "<<empleado.apellidos<<" | "<<empleado.sueldo<<" | "<<empleado.bonificacion<<" | "<<empleado.sueldo_total<<endl;
		fread(&empleado,sizeof(Empleado),1,archivo);
		registro+=1;
		}
	while(feof(archivo)==0);//feof=file end of file
	cout<<endl;
	fclose(archivo);
}

void ingresar(){
	system("cls");
	char continuar;
	// crear y abrir archivo
	FILE* archivo = fopen(nombre_archivo,"ab");
	// datos del estudiante
	Empleado empleado;
	string nombre,apellido;
	// pregunta si desea ingresar otra informacion
	do{
		// bufer limpia 
		fflush(stdin);
		//system("cls");
		cout<<"\nIngrese el Codigo (5 digitos): ";
		cin>>empleado.codigo;
		cin.ignore();
		
		cout<<"Ingrese los Nombres: ";
		getline(cin,nombre);
		strcpy(empleado.nombres,nombre.c_str());
		
		cout<<"Ingrese los Apellidos: ";
		getline(cin,apellido);
		strcpy(empleado.apellidos,apellido.c_str());
		
		cout<<"Ingrese el Sueldo: ";
		cin>>empleado.sueldo;
		cin.ignore();
		
		empleado.sueldo_total=empleado.sueldo+empleado.bonificacion;
		
		// escribe en el archivo
		fwrite(&empleado,sizeof(Empleado),1,archivo);
		
		cout<<"Desea agragar otro Nombre (s/n): ";
		cin>>continuar;
	}
	while(continuar=='s'||continuar=='S');
	fclose(archivo);
	abrir();
}

//Metodo Modificar
void modificar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	string nombre,apellido;
	Empleado empleado;
	int id = 0;
	cout<<"\nQue registros dese modificar (id): ";
	cin>>id;
	fseek(archivo,id * sizeof(Empleado),SEEK_SET);
	cout<<"Ingres Nuevo Codigo: ";
	cin>>empleado.codigo;
	cin.ignore();
	cout<<"Ingres Nuevo Nombres: ";
	getline(cin,nombre);
	strcpy(empleado.nombres,nombre.c_str());
	cout<<"Ingres Nuevo Apellidos: ";
	getline(cin,apellido);
	strcpy(empleado.apellidos,apellido.c_str());
	cout<<"Ingres Nuevo Sueldo: ";
	cin>>empleado.sueldo;
	empleado.sueldo_total=empleado.sueldo+empleado.bonificacion;


	fwrite(&empleado,sizeof(Empleado),1,archivo);
	fclose(archivo);
	abrir();
	cout<<"LA MODIFICACION HA SIDO REALIZADA . . ."<<endl;
	cout<<endl;
}

//Metodo Buscar con Codigo
void buscar_codigo(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");	
	int	 indice=0,pos=0,cod= 0;
	cout<<"Buscar Codigo:";
	cin>>cod;
	Empleado empleado;
	fread(&empleado,sizeof(Empleado),1,archivo);
	do{
		if (empleado.codigo ==cod){
			pos = indice;
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
		indice+=1;
	} while (feof(archivo)==0);

	cout<<"_____________"<<pos<<"__________________"<<endl;
	fseek(archivo,pos * sizeof(Empleado),SEEK_SET);
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombres: "<<empleado.nombres<<endl;
	cout<<"Apellidos: "<<empleado.apellidos<<endl;
	cout<<"Sueldo: "<<empleado.sueldo<<endl;
	cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
	empleado.sueldo_total=empleado.sueldo+empleado.bonificacion;
	cout<<"Sueldo total: "<<empleado.sueldo_total<<endl;

	fclose(archivo);	
}

void eliminar(){
	FILE*archivo=fopen(nombre_archivo, "r+b");
	FILE*temporal;
	Empleado empleado;
	char elimina = 0;
	int codaux;
	
	temporal = fopen("temporal.dat", "wb");
	
	cout<<"Ingrese el codigo del empleado desea eliminar: ";
	cin>>codaux;
	
	if (nombre_archivo == NULL || temporal == NULL) {
		elimina = 0;
	} else {
		/* Se copia en el archivo temporal los registros válidos */
		fread(&empleado, sizeof(Empleado),1,archivo);
		while (!feof(archivo)) {
			if (empleado.codigo != codaux) {
				fwrite(&empleado, sizeof(Empleado), 1, temporal);
			}
			fread(&empleado,sizeof(Empleado),1,archivo);	
		}
		
		/* Se cierran los archivos antes de borrar y renombrar */
		fclose(archivo);
		fclose(temporal);
 
		remove("archivo.dat");
		rename("temporal.dat", "archivo.dat");
 
		elimina = 1;
	}
	cout<<endl;
		cout<<"SE HA ELIMINADO EXITOSAMENTE . . ."<<endl;
		cout<<endl;
		system("pause");
 return abrir();
}

