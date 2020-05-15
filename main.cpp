#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*Cerințe comune tuturor temelor:
1. utilizarea sabloanelor;
2. utilizarea STL;
3. utilizarea variabilelor, funcțiilor statice,
constantelor și a unei functii const;
4. utilizarea conceptelor de RTTI raportat la template-uri;
5. tratarea excepțiilor;
6. citirea informațiilor complete a n obiecte,
memorarea și afișarea acestora;
7. să se identifice și să se implementeze ierarhia de clase;
8. clasele să conțină constructori, destructori, =,
funcție prietena de citire a datelor;
9. clasa de baza sa conțină funcție virtuala de afisare,
rescrisa în clasele derivate, iar operatorul de citire să
fie implementat ca funcție prietena (în clasele derivate să se
facă referire la implementarea acestuia în clasa de baza).

Tema 3. La facultatea Y studenții intra în sesiune.
În regulament e prevăzut ca ei sa aibă un anumit număr de examene.
Fiecare examen are un număr, incrementat automat, denumirea materiei,
data și nota la scris.
Partialul conține și nota la oral, iar examenul final
conține extra-puncte pe un proiect.
Dacă partialul nu e luat, atunci se reface la examenul final,
altfel, se păstrează nota.
Cei care vor să-si mareasca nota, mai dau un quiz,
conținând un număr de itemi de tip grila.

Structura de date: unordered_set sau
unordered_map <id_examen, vector<student>>
(se rețin studentii care nu au trecut examenul cu id-ul id_examen)

Cerința suplimentară:
- Să se adauge toate campurile relevante pentru modelarea acestei
probleme.
- Să se construiască clasa template CatalogIndividual care
sa conțină informații despre tipurile de examene date de un student.
Clasa conține nr matricol al studentului (incrementat automat la
adaugarea unei noi file), nr_examene și structura de obiecte.
Sa se supraincarce operatorul += pentru inserarea unei fișe de
observație a unui examen în structura.
- Să se construiască o specializare pentru tipul Quizz care sa adapteze
operatorii menționați și care sa afiseze, în plus,
cate persoane au dat cel puțin 2 quizz-uri.*/

template<class c, class N>
class student;

template<class n, class s>
class examen
{
protected:

    static n id_examen;
    s denumire_materie;
    s data;
    n nota_final;

public:

    examen(s mat="", s dat="", n nota=1)
{
    id_examen++;

    try
    {
        for(unsigned int i=0; i<mat.length(); i++)
            if((int)mat[i]!=32 &&
               ((int)mat[i]<65 || (int)mat[i]>90) &&
               ((int)mat[i]<97 || (int)mat[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=mat;

    data=dat;

    try
    {
        if(nota<1 || nota>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota finala nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_final=nota;
}

    examen(const examen&);
    virtual ~examen()=0;
    virtual void citire(istream&)=0;
    virtual void afisare(ostream&)=0;
    friend istream& operator>>(istream& in, examen<float, string>& ex)
    {
        ex.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, examen<float, string>& ex)
    {
        ex.afisare(out);
        return out;
    }
    examen& operator=(const examen&);
    static n Numar_examene(){return id_examen;}
    friend class student<string, int>;
};

template<class n, class s>
n examen<n, s>::id_examen;

template<class n, class s>
examen<n, s>::~examen(){}

template<class n, class s>
examen<n, s>::examen(const examen& ex)
{
    denumire_materie=ex.denumire_materie;
    data=ex.data;
    nota_final=ex.nota_final;
}

template<class n, class s>
examen<n, s>& examen<n, s>::operator=(const examen& ex)
{
    this->denumire_materie=ex.denumire_materie;
    this->data=ex.data;
    this->nota_final=ex.nota_final;
    return *this;
}

template<class n, class s>
void examen<n, s>::citire(istream& in)
{
    string denumire;
    cout<<"Denumire materie: ";
    in>>denumire;
    try
    {
        for(unsigned int i=0; i<denumire.length(); i++)
            if((int)denumire[i]!=32 &&
               ((int)denumire[i]<65 || (int)denumire[i]>90) &&
               ((int)denumire[i]<97 || (int)denumire[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=denumire;

    string dat;
    cout<<"Data examenului: ";
    in>>dat;
    data=dat;

    float nota;
    cout<<"Nota finala a examenului este ";
    in>>nota;
    try
    {
        if(nota<1 || nota>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_final=nota;
}

template<class n, class s>
void examen<n, s>::afisare(ostream& out)
{
    out<<"Denumire materie: "<<denumire_materie<<endl;
    out<<"Data examenului: "<<data<<endl;
    out<<"Nota scris: "<<nota_final<<endl;
}

template<class n, class s>
class partial:public examen<float, string>
{
    s denumire_materie;
    s data;
    n nota_scris;
    n nota_oral;

public:

    partial(s denumire="", s date="", n scris=1, n oral=1):examen<n,s>(denumire, date, max((scris+oral)/n(2), n(1)))
{
    try
    {
        for(unsigned int i=0; i<denumire.length(); i++)
            if((int)denumire[i]!=32 &&
               ((int)denumire[i]<65 || (int)denumire[i]>90) &&
               ((int)denumire[i]<97 || (int)denumire[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=denumire;

    data=date;

    try
    {
        if(scris<1 || scris>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_scris=scris;

    try
    {
        if(oral<1 || oral>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_oral=oral;

}
    partial(const partial&);
    ~partial(){};
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>>(istream& in, partial<n,s>& par)
    {
        par.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, partial<n,s>& par)
    {
        par.afisare(out);
        return out;
    }
    partial& operator=(const partial&);
};

template<class n, class s>
partial<n,s>::partial(const partial& par):examen<n,s>(par.denumire_materie, par.data, (par.nota_oral+par.nota_scris)/2)
{
    this->denumire_materie=par.denumire_materie;
    this->data=par.data;
    this->nota_oral=par.nota_oral;
    this->nota_scris=par.nota_scris;
}

template<class n, class s>
partial<n,s>& partial<n,s>::operator=(const partial& par)
{
    this->denumire_materie=this->denumire_materie=par.denumire_materie;
    this->data=this->data=par.data;
    this->nota_oral=par.nota_oral;
    this->nota_scris=par.nota_scris;
    this->nota_final=(this->nota_oral+this->nota_scris)/2;
    return *this;
}

template<class n, class s>
void partial<n,s>::afisare(ostream& out)
{
    out<<"Denumire materie: "<<denumire_materie<<endl;
    out<<"Data: "<<data<<endl;
    out<<"Nota scris: "<<nota_scris<<endl;
    out<<"Nota oral: "<<nota_oral<<endl;
}

template<class n, class s>
void partial<n,s>::citire(istream& in)
{
    string denumire;
    cout<<"Denumire materie pentru testul partial: ";
    in>>denumire;
    try
    {
        for(unsigned int i=0; i<denumire.length(); i++)
            if((int)denumire[i]!=32 &&
               ((int)denumire[i]<65 || (int)denumire[i]>90) &&
               ((int)denumire[i]<97 || (int)denumire[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=denumire;

    string dat;
    cout<<"Data partial: ";
    in>>dat;
    data=dat;

    float scris;
    cout<<"Nota scris partial: ";
    in>>scris;

    try
    {
        if(scris<1 || scris>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota la scris nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_scris=scris;

    float oral;
    cout<<"Nota oral partial: ";
    in>>oral;

    try
    {
        if(oral<1 || oral>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota la oral nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_oral=oral;

    nota_final=(nota_oral+nota_scris)/n(2);
}

template<class n, class s>
class examen_final:public examen<float,string>
{
    s denumire_materie;
    s data;
    n nota_scris;
    n extra_puncte;

public:

    examen_final(s denumire="", s date="", n scris=1, n extra=0):examen<n,s>(denumire, date, min(scris+extra, n(10)))
{
    try
    {
        for(unsigned int i=0; i<denumire.length(); i++)
            if((int)denumire[i]!=32 &&
               ((int)denumire[i]<65 || (int)denumire[i]>90) &&
               ((int)denumire[i]<97 || (int)denumire[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=denumire;

    data=date;

    try
    {
        if(scris<1 || scris>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_scris=scris;

    try
    {
        if(extra<0 || extra>2) throw 1;
    }
    catch(int c)
    {
        cout<<"Extra-punctele nu se afla in intervalul 0-2!"<<endl;
        exit(0);
    }

    extra_puncte=extra;

    nota_final=min(nota_scris+extra_puncte, n(10));
}
    examen_final(examen_final&);
    ~examen_final(){};
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>>(istream& in, examen_final& ex)
    {
        ex.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, examen_final& ex)
    {
        ex.afisare(out);
        return out;
    }
    examen_final& operator=(const examen_final&);
};

template<class n, class s>
void examen_final<n,s>::citire(istream& in)
{
    string denumire;
    cout<<"Denumire materie pentru examen final: ";
    in>>denumire;
    try
    {
        for(unsigned int i=0; i<denumire.length(); i++)
            if((int)denumire[i]!=32 &&
               ((int)denumire[i]<65 || (int)denumire[i]>90) &&
               ((int)denumire[i]<97 || (int)denumire[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Denumirea materiei este incorecta"<<endl;
        exit(0);
    }
    denumire_materie=denumire;

    string dat;
    cout<<"Data examen final: ";
    in>>dat;
    data=dat;

    float scris;
    cout<<"Nota scris examen final: ";
    in>>scris;

    try
    {
        if(scris<1 || scris>10) throw 1;
    }
    catch(int c)
    {
        cout<<"Nota nu se afla in intervalul 1-10!"<<endl;
        exit(0);
    }

    nota_scris=scris;

    float extra;
    cout<<"Puncte extra (0-2): ";
    in>>extra;

    try
    {
        if(extra<0 || extra>2) throw 1;
    }
    catch(int c)
    {
        cout<<"Punctele extra nu se afla in intervalul 0-2!"<<endl;
        exit(0);
    }

    extra_puncte=extra;

    nota_final=min((nota_scris+extra_puncte),n(10));
}

template<class n, class s>
void examen_final<n,s>::afisare(ostream& out)
{
    out<<"Denumire materie: "<<denumire_materie<<endl;
    out<<"Data: "<<data<<endl;
    out<<"Nota scris: "<<nota_scris<<endl;
    out<<"Puncte extra: "<<extra_puncte<<endl;
}

template<class n, class s>
examen_final<n,s>::examen_final(examen_final& ex):examen<n,s>(ex.denumire_materie, ex.data, min((ex.nota_scris+ex.extra_puncte),n(10)))
{
    this->denumire_materie=ex.denumire_materie;
    this->data=ex.data;
    this->nota_scris=ex.nota_scris;
    this->extra_puncte=ex.extra_puncte;
}

template<class n, class s>
examen_final<n,s>& examen_final<n,s>::operator=(const examen_final& ex)
{
    this->denumire_materie=ex.denumire_materie;
    this->data=ex.data;
    this->nota_scris=ex.nota_scris;
    this->extra_puncte=ex.extra_puncte;

    this->nota_final=min((this->nota_scris+this->extra_puncte),n(10));
    return *this;
}

template<class c, class N>
class student
{
    c nume;
    c prenume;
    c cnp;
    N numar_examene;
    static N nr;

public:

    student(c name=" ", c first_name=" ", c cod="0000000000000", N num=0)
{
    nr++;

    try
    {
        for(unsigned int i=0; i<name.length(); i++)
            if((int)name[i]!=32 &&
               ((int)name[i]<65 || (int)name[i]>90) &&
               ((int)name[i]<97 || (int)name[i]>122))
                throw 1;
    }
    catch(int x)
    {
        cout<<"Numele nu poate sa contina cifre sau alte simboluri diferite de litere!"<<endl;
        exit(0);
    }
    nume=name;

    try
    {
        for(unsigned int i=0; i<first_name.length(); i++)
            if((int)first_name[i]!=32 &&
               ((int)first_name[i]<65 || (int)first_name[i]>90) &&
               ((int)first_name[i]<97 || (int)first_name[i]>122))
                throw 1;
    }
    catch(int x)
    {
        cout<<"Numele nu poate sa contina cifre sau alte simboluri diferite de litere!"<<endl;
        exit(0);
    }
    prenume=first_name;

    try
    {
        for(unsigned int i=0; i<cod.length(); i++)
            if(cod[i]<'0' || cod[i]>'9' || cod.length()!=13) throw 1;
    }
    catch(int x)
    {
        cout<<"CNP-ul studentului trebuie sa contina doar cifre si sa aiba 13 caractere."<<endl;
        exit(0);
    }

    cnp=cod;

    try
    {
        if(num<0) throw 1;
    }
    catch(int x)
    {
        cout<<"Numarul de examene trebuie sa fie numar natural!"<<endl;
        exit(0);
    }

    numar_examene=num;
}

    student(const student&);
    ~student();
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>>(istream& in, student<string,int>& s)
    {
        s.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, student<string,int>& s)
    {
        s.afisare(out);
        return out;
    }
    student& operator=(const student& s);
    static N Numar_Studenti(){return nr;};
    void sesiune(string materii[100]);
    void informatii_examene();
    bool trecut(string, vector<examen<float,string>*>);
    vector<examen<float, string>*>examene;

};

template<class c, class N>
void student<c,N>::sesiune(string materii[100])
{
    for(unsigned int i=0; i<numar_examene; i++)
    {
        cout<<"\nA dat studentul partial la "<<materii[i]<<"(Da/Nu)? ";
        string raspuns;

        try
        {
            if(!(cin>>raspuns)) throw 1;
        }
        catch(int j)
        {
            cout<<"\nRaspuns invalid. Dati un string (Da/Nu).";
            exit(0);
        }

        try
        {
            if((tolower(raspuns[0])!='d' || tolower(raspuns[1])!='a')
            && (tolower(raspuns[0])!='n' || tolower(raspuns[1])!='u'))
                throw 1;
        }

        catch(int i)
        {
              cout<<"\nRaspundeti cu Da/Nu.";
              exit(0);
        }

        if(tolower(raspuns[0])=='d')
            {
                string date;
                cout<<"Data partialului la "<<materii[i]<<" este: ";
                cin>>date;
                float oral;
                cout<<"Nota la oral este: ";
                cin>>oral;
                float scris;
                cout<<"Nota la scris este: ";
                cin>>scris;

                ///Dorim sa adaugam examenele partiale in vectorul de obiecte de tip examen
                examen<float, string> *ex=new partial<float, string>(materii[i], date, scris, oral);
                partial<float, string> *par=dynamic_cast<partial<float, string>*>(ex);
                examene.push_back(par);
            }
        else
            {
                examen<float, string> *ex=new partial<float, string>(materii[i]);
                partial<float, string> *par=dynamic_cast<partial<float, string>*>(ex);
                examene.push_back(par);
            }

        cout<<"\nS-a prezentat studentul la examenul de "<<materii[i]<<"(Da/Nu)? ";

        try
        {
            if(!(cin>>raspuns)) throw 1;
        }
        catch(int j)
        {
            cout<<"\nRaspuns invalid. Dati un string (Da/Nu).";
            exit(0);
        }

        try
        {
            if((tolower(raspuns[0])!='d' || tolower(raspuns[1])!='a')
            && (tolower(raspuns[0])!='n' || tolower(raspuns[1])!='u'))
                throw 1;
        }

        catch(int i)
        {
              cout<<"\nRaspundeti cu Da/Nu.";
              exit(0);
        }

        if(tolower(raspuns[0])=='d')
            {
                string date;
                cout<<"Data examenului la "<<materii[i]<<" a fost: ";
                cin>>date;
                float scris;
                cout<<"Nota la scris este: ";
                cin>>scris;
                float puncte;
                cout<<"Extra-punctele pe proiect(0-2): ";
                cin>>puncte;

                ///Dorim sa adaugam examenele partiale in vectorul de obiecte abstracte examene
                examen<float,string> *ex=new examen_final<float, string>(materii[i], date, scris, puncte);
                examen_final<float, string> *exf=dynamic_cast<examen_final<float, string>*>(ex);
                examene.push_back(ex);
            }

        else
            {
                examen<float,string> *ex=new examen_final<float,string>(materii[i]);
                examen_final<float, string> *exf=dynamic_cast<examen_final<float, string>*>(ex);
                examene.push_back(ex);
            }
    }
}

template<class c, class N>
bool student<c,N>::trecut(string materie, vector<examen<float,string>*> examene)
{
    for(unsigned int i=1; i<examene.size(); i+=2)
    {
        if((*examene[i]).denumire_materie.compare(materie)==0
           && (*examene[i]).nota_final<5) return false;
        else if((*examene[i]).denumire_materie.compare(materie)==0) return true;
    }
}

template<class c, class N>
void student<c, N>::informatii_examene()
{
    vector<string> partiale_de_repetat;
    vector<string> examene_picate;

    for(unsigned int i=0; i<examene.size(); i++)
    {
        ///Verificam daca partialul a fost luat
        if(i%2==0)
        {
            if((*examene[i]).nota_final<5) partiale_de_repetat.push_back((*examene[i]).denumire_materie);
        }
        else
        {
            if((*examene[i]).nota_final<5) examene_picate.push_back((*examene[i]).denumire_materie);
        }
    }
    if(partiale_de_repetat.size()>=1)
        {
            cout<<"Studentul are de repetat urmatoarele partiale: ";
            for(unsigned int i=0; i<partiale_de_repetat.size(); i++)
                cout<<partiale_de_repetat[i]<<" ";
                cout<<endl;
        }
    if(examene_picate.size()>=1)
        {
            cout<<"Studentul a picat la urmatoarele examene: ";
            for(unsigned int i=0; i<examene_picate.size(); i++)
                cout<<examene_picate[i]<<" ";
                cout<<endl;
        }
}

//Declararea variabilei statice (variabila independenta de nr de instante ale clasei student)
template<class c, class N>
N student<c, N>::nr;

//Constructor copiere
template<class c, class N>
student<c,N>::student(const student& s)
{
    nume=s.nume;
    prenume=s.prenume;
    cnp=s.cnp;
    numar_examene=s.numar_examene;
}

//Destructor
template<class c, class N>
student<c,N>::~student()
{

}

//Suprascrierea operatorului =
template<class c, class N>
student<c,N>& student<c,N>::operator=(const student& s)
    {
        this->nume=s.nume;
        this->prenume=s.prenume;
        this->cnp=s.cnp;
        this->numar_examene=s.numar_examene;

        return *this;
    }

template<class c, class N>
void student<c,N>::citire(istream& in)
{
    ///Declarare si citire nume
    string name;
    cout<<"Nume si Prenume: ";
    in>>name;

    ///Verificarea acceptarii numelui
    try
    {
        for(unsigned int i=0; i<name.length(); i++)
            if((int)name[i]!=32 &&
               ((int)name[i]<65 || (int)name[i]>90) &&
               ((int)name[i]<97 || (int)name[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Numele nu poate sa contina cifre sau alte simboluri diferite de litere!"<<endl;
        exit(0);
    }
    nume=name;

    ///Declarare si citire prenume
    string first_name;
    in>>first_name;

    ///Verificarea acceptarii prenumelui
    try
    {
        for(unsigned int i=0; i<first_name.length(); i++)
            if((int)first_name[i]!=32 &&
               ((int)first_name[i]<65 || (int)first_name[i]>90) &&
               ((int)first_name[i]<97 || (int)first_name[i]>122))
                throw 1;
    }
    catch(int i)
    {
        cout<<"Numele nu poate sa contina cifre sau alte simboluri diferite de litere!"<<endl;
        exit(0);
    }

    prenume=first_name;

    ///Declarare si citire CNP
    string cod;
    cout<<"CNP(13 cifre): ";
    in>>cod;

    ///Verificarea acceptarii CNP-ului
    try
    {
        for(unsigned int i=0; i<cod.length(); i++)
            if(cod[i]<'0' || cod[i]>'9' || cod.length()!=13) throw 1;
    }
    catch(int x)
    {
        cout<<"CNP-ul studentului trebuie sa contina doar cifre si sa aiba 13 caractere."<<endl;
        exit(0);
    }
    cnp=cod;
}

template<class c, class N>
void student<c,N>::afisare(ostream& out)
{
    out<<"Nume si Prenume: "<<nume<<" "<<prenume<<endl;
    out<<"CNP: "<<cnp<<endl;
    out<<"Numar examene: "<<numar_examene<<endl;
}

void CitireStudenti(vector<student<string, int>> &Studenti, unordered_map<int, vector<student<string, int>>> &Restantieri)
{

 ///Citire numar examene si verificarea acceptarii numarului
 int n;
 cout<<"Dati numarul de examene: ";

 try
 {
     if(!(cin>>n) || n<=0) throw 1;
 }
 catch(int i)
 {
     cout<<"Eroare, numarul nu a fost citit cu succes.";
     exit(0);
 }

 ///Citire numar studenti si verificarea acceptarii numarului
 int num;
 cout<<"Dati numarul de studenti: ";

 try
 {
     if(!(cin>>num) || num<=0) throw 1;
 }
 catch(int i)
 {
     cout<<"Eroare, numarul nu a fost citit cu succes.";
     exit(0);
 }

 ///Stocarea celor n examene
 string materii[n];

 cout<<"Enumerati materiile la care studentii au dat examen: ";
 for(unsigned int i=0; i<n; i++)
    {
        cin>>materii[i];
    }

vector<vector<examen<float,string>*>>Situatie;
 ///Stocarea celor num studenti
 for(unsigned int i=0; i<num; i++)
    {
        cout<<"\n\n";
        student<string, int> s("", "", "", n);
        cin>>s;
        Studenti.push_back(s);
        Studenti[Studenti.size()-1].sesiune(materii);
        Studenti[Studenti.size()-1].informatii_examene();
        Situatie.push_back(Studenti[Studenti.size()-1].examene);
    }

 for(unsigned int i=0; i<n; i++)
 {
    vector<student<string, int>> picati;
    for(unsigned int j=0; j<Studenti.size(); j++)
        {
           if(Studenti[j].trecut(materii[i], Situatie[j])==0)
            picati.push_back(Studenti[j]);
        }
    if(picati.size()>=1) Restantieri.insert({i+1, picati});
 }

 for(auto i=Restantieri.begin(); i!=Restantieri.end(); i++)
 {
     cout<<"\nLa examenul cu id-ul "<<i->first<<"("<<materii[i->first-1]<<")"<<" restantierii sunt: \n\n";
     for(unsigned int j=0; j<i->second.size(); j++)
        cout<<i->second[j]<<endl;
 }

/*student str(" ",  " ", "9876543021234", n);
Studenti.push_back(str);*/
}

int main()
{
 vector<student<string, int>> Studenti;
 unordered_map<int, vector<student<string, int>>> Restantieri;

 CitireStudenti(Studenti, Restantieri);
}
