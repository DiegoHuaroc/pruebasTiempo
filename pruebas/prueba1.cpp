#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <map>
#include <ctime>

#define LIMA (+19)
using namespace std;
int main(){
    time_t rawtime;
    struct tm * ptm;

    time ( &rawtime );

    ptm = gmtime ( &rawtime );

    int hora1,minuto,hr,hora12;

    hora1=(ptm->tm_hour+LIMA)%24;
    minuto=ptm->tm_min;
    hr=hora1*100+minuto;
    cout<<hora1<<":"<<minuto<<endl;
    cout<<hr<<endl;
    
    string x,y="05300623DH07110822ZI09491009XC10171151VQ";
    int qwer,wer,control;
    string tre="";
    cout<<y;
    string estado="";
    cin>>qwer;
    cin>>wer;
    int a;
    map<int,int> mapaPuntos;
    cout<<y.size()/10<<endl;
    for(int i=0;i<y.size()/10;i++){
        char hora1[2],hora2[2],min1[2],min2[2],primera[4],segunda[4],cliente[2];
        int s=i*10;
        hora1[2]='\0';
        min1[2] ='\0';
        hora2[2]='\0';
        min2[2]='\0';
        primera[4]='\0';
        segunda[4]='\0';
        cliente[2]='\0';
        y.copy(hora1,2,s);
        y.copy(min1,2,s+2);
        y.copy(hora2,2,s+4);
        y.copy(min2,2,s+6);
        y.copy(cliente,2,s+8);
        
        y.copy(primera,4,s);
        string pri=primera;
        y.copy(segunda,4,s+4);
        string seg=segunda;
        int priH =atof(pri.c_str());
        int segH =atof(seg.c_str());
        mapaPuntos.insert(pair<int, int>(priH,segH));
        //if( qwer<segH && qwer>priH) estado+="NO Viable ";
        //if( wer<segH && wer>priH) estado+="NO Viable ";
        if( priH>qwer && priH<wer) estado+="NO Viable ";
        if( segH>qwer && segH<wer) estado+="NO Viable ";
        cout<<hora1<<":"<<min1<<" a "<< hora2<<":"<<min2<<" "<<cliente<<endl;
    }
    for (map<int,int>::iterator qit=mapaPuntos.begin(); qit!=mapaPuntos.end(); ++qit)
    {
        
    }
    mapaPuntos.insert(pair<int, int>(qwer,wer));
    map<int,int>::iterator it=mapaPuntos.begin();
    map<int,int>::reverse_iterator rit=mapaPuntos.rbegin();
    int hora;

    //it=mapaPuntos.begin();
    if(hr>rit->second){
        cout<<"Libre resto del dia fin";
        hora=12;
    }
    else{
        while (it->second<hr)
        {
            ++it;
            hora12=it->second;
        }
        
    }
    for (map<int,int>::iterator qit=mapaPuntos.begin(); qit!=mapaPuntos.end(); ++qit)
    {
        cout<<qit->first<<"  "<<qit->second<<endl;
        if(qit->first<1000)tre+='0'+to_string(qit->first);
        else tre+=to_string(qit->first);
        if(qit->second<1000)tre+='0'+to_string(qit->second);
        else tre+=to_string(qit->second);
    }
    cout<<estado<<endl;

    cout<<tre<<"  "<<tre.size()<<" "<<hora<<" "<<hora12;
    
    
    

    
    return 0;
}