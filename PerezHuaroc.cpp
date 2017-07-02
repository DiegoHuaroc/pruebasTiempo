#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <map>
#include <ctime>

#define LIM (+19)

using namespace std;

struct PuntoEst
{
    string nombre;
    double posicionX;
    double posicionY;
    string estadoP;
    string horario;
};

class PuntoF
{
    vector<PuntoEst> ListPoints;
    map<string,PuntoEst> mapaPuntos;


    public:
        PuntoF()
            {
            }
            
    void leerArchivo(string nombre)
        {
     
        ifstream archivo(nombre);
        
        vector<string> datos;
        string texto;
        
        while (getline(archivo,texto))
            {
                datos.push_back(texto);
            }
        
        ListPoints.clear();
        for (int i = 1; i < datos.size(); i++)
            {
            auto columnas = split(datos[i], ',');
            PuntoEst punto = {columnas[0], atof(columnas[1].c_str()), atof(columnas[2].c_str()),columnas[3],columnas[4]};
            ListPoints.push_back(punto);
            mapaPuntos.insert(pair<string, PuntoEst>(columnas[0],punto));
            }
        
        archivo.close();
        }
    
        
    vector <string> split(string texto, char separador)
    {
        vector<string> datos;
        string valor;
        for (auto i : texto)
            {
            if (i != separador)
                {
                valor = valor + i;
                }
            else
                {
                datos.push_back(valor);
                valor.clear();
                }
            }
        datos.push_back(valor);
        return datos;
    }
    double distancia(PuntoEst pri, PuntoEst seg){
        double distancia =sqrt(pow(pri.posicionX-seg.posicionX,2)+pow(pri.posicionY-seg.posicionY,2));
        return distancia;
    }
    void actEstadoMostrar( int hr){
        int segH;
    for (map<string,PuntoEst>::iterator it=mapaPuntos.begin(); it!=mapaPuntos.end(); ++it)
    {
        int segH;
        string temporal4=it->second.horario;
        char control[4];
        string control3=control;
        temporal4.copy(control,4,0);
        control[4]='\0';
        string n="null";
        if(temporal4==n){it->second.estadoP="mantenimiento";}
        else{
            string control5="vacio temporalmente";
            for(int i=0;i<temporal4.size()/10;i++){
                char primera[4],segunda[4];
                int s=i*10;
                
                primera[4]='\0';
                segunda[4]='\0';
        
                temporal4.copy(primera,4,s);
                string pri=primera;
                temporal4.copy(segunda,4,s+4);
                string seg=segunda;
                int priH =atof(pri.c_str());
                segH =atof(seg.c_str());
                if( hr>priH && hr<segH)control5="ocupado temporalmente";
            }
            
            if(hr>segH){
                control5="vacio por el resto del dia"; 
            }
            it->second.estadoP=control5;
        }
    }
    }
    void reserva(string sujeto){
        string(50, '\n');
        int control6=-10;
        map<int,int> horariosP;
        cout<<"Horarios disponibles del punto "<<sujeto<<" :"<<endl;
        string horarios=mapaPuntos[sujeto].horario;
        for(int i=0;i<horarios.size()/10;i++){
            char hora1[2],hora2[2],min1[2],min2[2],primera[4],segunda[4],cliente[2];
            int s=i*10;
            hora1[2]='\0';
            min1[2] ='\0';
            hora2[2]='\0';
            min2[2]='\0';
            primera[4]='\0';
            segunda[4]='\0';
            cliente[2]='\0';
            horarios.copy(hora1,2,s);
            horarios.copy(min1,2,s+2);
            horarios.copy(hora2,2,s+4);
            horarios.copy(min2,2,s+6);
            horarios.copy(cliente,2,s+8);
        
            horarios.copy(primera,4,s);
            string pri=primera;
            horarios.copy(segunda,4,s+4);
            string seg=segunda;
            int priH =atof(pri.c_str());
            int segH =atof(seg.c_str());
            horariosP.insert(pair<int, int>(priH,segH));
            cout<<hora1<<":"<<min1<<" a "<< hora2<<":"<<min2<<" reservado por "<<cliente<<endl;
        }
        int h1,m1,h2,m2,horr1,horr2;
        cout<<endl;
        cout<<"Ingrese la hora inicial de su reserva en formato de 24 horas:"<<endl;
        cout<<"Hora:";
        cin>>h1;
        cout<<"Minutos:";
        cin>>m1;
        cout<<"Ingrese la hora final de su reserva en formato de 24 horas:"<<endl;
        cout<<"Hora:";
        cin>>h2;
        cout<<"Minutos:";
        cin>>m2;
        horr1=h1*100+m1;
        horr2=h2*100+m2;
        for (map<int,int>::iterator it=horariosP.begin(); it!=horariosP.end(); ++it)
        {
            if( it->first>horr1 && it->first<horr2)  control6=1;
            if( it->second>horr1 && it->second<horr2) control6=1;
        }
        if (control6<0){
            string nuevoH;
            int numero=0;
            char nom,ape;
            cout<<"Ingrese la inicial de su nombre :";
            cin>>nom;
            if(nom==0) nom='_';
            else nom=toupper(nom);
            cout<<"Ingrese la inicial de su apellido :";
            cin>>ape;
            if(ape==0) ape='_';
            else ape=toupper(ape);
            map<int,int>::reverse_iterator rit=horariosP.rbegin();
            map<int,int>::iterator it=horariosP.begin();
            if(rit->second<horr1){
                if(horr1<1000)nuevoH+='0'+to_string(horr1);
                else nuevoH+=to_string(horr1);
                if(horr2<1000)nuevoH+='0'+to_string(horr2);
                else nuevoH+=to_string(horr2);
                horarios+=nuevoH+nom+ape;
                mapaPuntos[sujeto].horario=horarios;
                cout<<"Reserva exitosa.";
            }
            else{
                while (it->second<horr1)
                {
                    ++it;
                    numero+=1;
                }
                numero=numero*10;
                if(horr1<1000)nuevoH+='0'+to_string(horr1);
                else nuevoH+=to_string(horr1);
                if(horr2<1000)nuevoH+='0'+to_string(horr2);
                else nuevoH+=to_string(horr2);
                char parte1[numero],parte2[horarios.size()-numero];
                parte1[numero]='\0';
                parte2[horarios.size()-numero]='\0';
                horarios.copy(parte1,numero,0);
                horarios.copy(parte2,horarios.size()-numero,numero);
                horarios=parte1+nuevoH+nom+ape+parte2;
                mapaPuntos[sujeto].horario=horarios;
                cout<<"Reserva exitosa.";
            }
        }
        else cout<<"Reserva no viable por cruce "<<endl;
    }
    

    void busquedaPorEstado(double dist, double x, double y){
        map<string,string> temporal;
        PuntoEst tempo={"Posicicon actual",x,y," "," "};
        
        for (map<string,PuntoEst>::iterator it=mapaPuntos.begin(); it!=mapaPuntos.end(); ++it)
        {
            
            temporal.insert(pair<string, string>(it->second.estadoP,it->first));
        }
        
        for (auto it: temporal)
        {
            cout << "Puntos con el estado "<<it.first <<" son :"<< endl;
            for (map<string,PuntoEst>::iterator qit=mapaPuntos.begin(); qit!=mapaPuntos.end(); ++qit)
            {
                double distance=distancia(qit->second,tempo);
                if(qit->second.estadoP==it.first &&distance<dist)
                cout << "    ." <<qit->first << endl;   
            
            }
        }
    }
    void busquedaPorEstado(string estado,double dist, double x, double y,int hr){
        int tempora1=0;
        cout<<endl;
        cout<<"Puntos con el estado "<<estado<<" son :"<<endl;
        for (map<string,PuntoEst>::iterator it=mapaPuntos.begin(); it!=mapaPuntos.end(); ++it)
        {
            if(it->second.estadoP==estado){
                cout << "    ." <<it->first << endl;  
                tempora1+=1;
            }
            
        }
        if(tempora1=0)cout<<"No hay puntos cercanos"<<endl;
        
    }

    void grabarArchivo(string nombre)
    {
        
        ofstream archivo(nombre);
        archivo << "nombre,posicion X,posicion Y,estado" << endl;
        for (map<string,PuntoEst>::iterator it=mapaPuntos.begin(); it!=mapaPuntos.end(); ++it)
        {
            archivo << it->second.nombre << "," << it->second.posicionX <<
            "," << it->second.posicionY << "," << it->second.estadoP <<"," << it->second.horario << endl;   
        }
        archivo.close();
    }


};
int menu()
{
    int opcion = 0;
    do
    {
        system ("clear");
        cout << "MENU" << endl;
        cout << string(4, '~') << endl << endl;
        cout << "1. Realizar reserva" << endl;
        cout << "0. Para salir" << endl << endl;
        cout << "Opcion : ";
        cin >> opcion;
    }
    while (opcion < 0 || opcion > 1);
    
    return opcion;
}
int main()
{
    PuntoF puntos;
    puntos.leerArchivo("datos.txt");
    int opcion = 0;
    
    do
    {
        opcion = menu(); 
        double x, y,distancia1;
        int opcion2;
        string nomb;
        string est;
        time_t rawtime;
        struct tm * ptm;
        time ( &rawtime );
        ptm = gmtime ( &rawtime );
        int hora1,minuto,hr;
        hora1=(ptm->tm_hour+LIM)%24;
        minuto=ptm->tm_min;
        hr=hora1*100+minuto;
        switch(opcion)
        {
            case 1:     // Enlistado de estados
                cout << string(50, '\n');
                cin.ignore();
                        cout<<"Ingrese coordenada x de su posicion "<<endl;
                        cin>>x;
                        cout<<"Ingrese coordenada y de su posicion "<<endl;
                        cin>>y;
                        cout<<"Ingrese distancia "<<endl;
                        cin>>distancia1;
                        puntos.actEstadoMostrar(hr);
                        puntos.busquedaPorEstado(distancia1,x,y);
                        cin.ignore();
                        cout<<endl;
                        cout<<"Ingrese nombre del punto donde desea hacer su reserva : ";
                        getline(cin,nomb);
                        puntos.reserva(nomb);
                        puntos.grabarArchivo("datos.txt");
                        cin.ignore();
                        cin.get();
        }
        
    }
    while (opcion != 0);

    return 0;
}
