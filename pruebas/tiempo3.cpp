#include <stdio.h>      /* printf, scanf */
#include <time.h>       /* time_t, struct tm, time, mktime */
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main ()
{
    time_t tiempo;
    struct tm *hora = {0};
    struct tm hora2 = {0}, hora3 = {0};
    char buffer [80];
    
    int hora1,minuto;
    time(&tiempo);
    hora=localtime(&tiempo);
    hora2=*localtime(&tiempo);
    hora3=*localtime(&tiempo);
    
    hora2.tm_hour=11;
    hora2.tm_min=00;
    hora3.tm_hour=13;
    hora3.tm_min=00;
    
    cout<<"Ingrese hora"<<'\n';
    cin>>hora1;
    cout<<"Ingrese minuto"<<'\n';
    cin>>minuto;
    cout<<'\n';
    hora->tm_hour=hora1;
    hora->tm_min=minuto;
    strftime (buffer,80,"La hora ingresada es %R.",hora);
    puts (buffer); 
    vector<tm*> sd;
    sd.push_back(hora);
    cout<<sd[0]<<endl;
    cout<<hora<<endl;
    int h=hora->tm_hour,m=hora->tm_min;
    string nombre="archivo.txt";
    ofstream archivo (nombre);
    archivo << "hora:minuto" << endl;
    archivo << sd[0]->tm_hour << ":" << m<<endl;
    archivo.close();
    cout<<"entre las 11 y 13 horas?"<<endl;
    if(hora->tm_hour<hora3.tm_hour && hora->tm_hour>hora2.tm_hour) cout<<"si";
    else cout<<"no";
    cout<<hora2.tm_hour<<" "<<hora3.tm_hour;
    
    return 0;
}