#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Adresat
{
    int id;
    string imie, nazwisko, telefon, email, adres;
};
Adresat podzielDaneNaPojedynczeSkladniki(string daneAdresata)
{
    Adresat adresat;
    vector<string> danePodzielone;
    string pojedynczaDana;
    int dlugosc = daneAdresata.length();
    int poczatek = 0;

    for(int i = 0; i<dlugosc; i++)
    {
        if(daneAdresata[i] == '|')
        {
            pojedynczaDana = daneAdresata.substr(poczatek,i-poczatek);
            poczatek = i+1;
            danePodzielone.push_back(pojedynczaDana);
        }
    }
    adresat.id = atoi(danePodzielone[0].c_str());
    adresat.imie = danePodzielone[1];
    adresat.nazwisko = danePodzielone[2];
    adresat.telefon = danePodzielone[3];
    adresat.email = danePodzielone[4];
    adresat.adres = danePodzielone[5];

    return adresat;
}
vector<Adresat>  wczytanieKsiazkiAdresowjZPliku()
{

    string linia;
    vector<Adresat> adresaci;
    fstream plik;
    Adresat adresat;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    if (plik.good() == true)
    {
        while (getline(plik, linia))
        {
            adresat = podzielDaneNaPojedynczeSkladniki(linia);
            adresaci.push_back(adresat);
        }
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku"<<endl;
        system("pause");
    }
    return adresaci;
}
void wyswietlWszystkichAdresatow(vector<Adresat> adresaci)
{
    system("cls");
    cout << " -- Osoby zapisane w Twojej ksiazce adresowej --" << endl << endl;
    for(vector<Adresat>::iterator itr = adresaci.begin(),koniec = adresaci.end(); itr!=koniec; ++itr)
    {
        cout << endl;
        cout << "ID: " << itr->id << endl;
        cout <<  "Imie i nazwisko: " << itr->imie << " " << itr->nazwisko<<endl;
        cout << "Telefon: " << itr->telefon << endl;
        cout << "Email: " << itr->email << endl;
        cout << "Adres: " << itr->adres << endl;
        cout <<  " --- --- ---" << endl;
    }
    cout << "Masz zapisanych  " << adresaci.size() << " adresatow." << endl;
    system("pause");
}
string konwersjaIntToString(int liczbaInt)
{
    ostringstream ss;
    ss << liczbaInt;
    string liczbaString = ss.str();

    return liczbaString;
}
int znajdzDostepneId(vector<Adresat> adresaci)
{
    int maxi=0;
    for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)

    {
        if(indeksVectora->id > maxi)
            maxi=indeksVectora->id;

    }
    return maxi+1;
}
vector<Adresat> wprowadzDaneAdresata(vector<Adresat> adresaci, int dostepneId)

{
    Adresat adresat;
    string imieSzukane, imieKolejne;
    string nazwiskoSzukane, nazwiskoKolejne;
    string daneAdresata,stringId;
    cout << "Podaj imie:  " << endl;
    cin >> imieSzukane;
    imieSzukane[0]=toupper(imieSzukane[0]);

    cout << "Podaj nazwisko:  " << endl;
    cin >> nazwiskoSzukane;
    nazwiskoSzukane[0]=toupper(nazwiskoSzukane[0]);
    vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end();
    while(indeksVectora!=koniecVectora)
    {
        imieKolejne = indeksVectora->imie;
        imieKolejne[0] = toupper(imieKolejne[0]);
        nazwiskoKolejne = indeksVectora->nazwisko;
        nazwiskoKolejne[0] = toupper(nazwiskoKolejne[0]);
        if ((nazwiskoKolejne == nazwiskoSzukane) && (imieKolejne == imieSzukane ))
        {
            cout << "Taki adresat jest juz w twojej ksiazce. " << endl;
            cout << endl;
            cout << "ID: " << indeksVectora->id << endl;
            cout << "Imie i nazwisko: " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon: "<<indeksVectora->telefon<<endl;
            cout << "Email: " << indeksVectora->email << endl;
            cout << "Adres: " << indeksVectora->adres << endl;
            cout << " --- --- ---" << endl;
            system("pause");
            return adresaci;
        }
        ++indeksVectora;
    }
    adresat.id = dostepneId;
    stringId = konwersjaIntToString(adresat.id);
    adresat.imie = imieSzukane;
    adresat.nazwisko = nazwiskoSzukane;

    cout << "Podaj telefon:  " << endl;
    cin.sync();
    getline(cin, adresat.telefon);
    cout << "Podaj email:  " << endl;
    cin >> adresat.email;
    cout << "Podaj adres:  " << endl;
    cin.sync();
    getline(cin,adresat.adres);
    adresaci.push_back(adresat);
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::app);
    if (plik.good() == true)
    {
        daneAdresata = stringId+"|"+adresat.imie+"|"+adresat.nazwisko+"|"+adresat.telefon+"|"+adresat.email+"|"+adresat.adres+"|";

        plik << daneAdresata << endl;
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    cout << "Osoba zostala dodana." << endl;
    system("pause");

    return adresaci;
}

void wyszukajPoImieniu(vector<Adresat> adresaci)
{
    string imieSzukane, imieKolejne;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj imie osob, ktorych dane chcesz odszukac: " << endl;
    cin >> imieSzukane;
    imieSzukane[0]=toupper(imieSzukane[0]);
    system("cls");

    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        imieKolejne = indeksVectora->imie;
        imieKolejne[0] = toupper(imieKolejne[0]);
        if(imieKolejne == imieSzukane)
        {
            cout << endl;
            cout << "ID: " << indeksVectora->id << endl;
            cout << "Imie i nazwisko: " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon: "<<indeksVectora->telefon << endl;
            cout << "Email: " << indeksVectora->email << endl;
            cout << "Adres: " << indeksVectora->adres << endl;
            cout << " --- --- ---" << endl;
            iloscOsobZnalezionych++;
        }
    }

    if (iloscOsobZnalezionych == 0)
        cout << "W twojej ksiazce nie ma osob o imieniu " << imieSzukane << " ." << endl;
    else
        cout<<"W twojej ksiazce jest " << iloscOsobZnalezionych << " osob o imieniu " << imieSzukane << "." << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector<Adresat> adresaci)
{
    string nazwiskoSzukane,nazwiskoKolejne;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj nazwisko osob, ktorych dane chcesz odszukac: " << endl;

    cin >> nazwiskoSzukane;
    nazwiskoSzukane[0]=toupper(nazwiskoSzukane[0]);
    system("cls");

    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        nazwiskoKolejne = indeksVectora->nazwisko;
        nazwiskoKolejne[0] = toupper(nazwiskoKolejne[0]);
        if(nazwiskoKolejne == nazwiskoSzukane)
        {
            cout << endl;
            cout << "ID: " << indeksVectora->id << endl;
            cout << "Imie i nazwisko: " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon: "<<indeksVectora->telefon << endl;
            cout << "Email: " << indeksVectora->email << endl;
            cout << "Adres: " << indeksVectora->adres << endl;
            cout << " --- --- ---" << endl;
            iloscOsobZnalezionych++;
        }
    }

    if (iloscOsobZnalezionych == 0)
        cout << "W twojej ksiazce nie ma osob o nazwisku " << nazwiskoSzukane << " ." << endl;
    else
        cout<<"W twojej ksiazce jest " << iloscOsobZnalezionych << " osob o nazwisku " << nazwiskoSzukane << "." << endl;
    system("pause");
}

vector<Adresat> usunAdresataOPodanymId(vector<Adresat> adresaci, bool* usunieto)
{
    int idSzukane;
    char potwierdzenie;
    int indeksSzukanego = 0;
    cout<<endl;
    cout << "Podaj id adresata, ktorego  chcesz usunac: " << endl;
    cin >> idSzukane;
    bool znaleziono = false;
    system("cls");

    for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        if(idSzukane == indeksVectora->id)
        {
            znaleziono=true;
            break;
        }
        else
        {
            indeksSzukanego++;
        }
    }
    if (znaleziono)
    {
        system("cls");
        cout <<" Dane znalezionego adresata: "<<endl;
        cout << "ID: " << adresaci[indeksSzukanego].id << endl;
        cout << "Imie i nazwisko: " <<adresaci[indeksSzukanego].imie << " " << adresaci[indeksSzukanego].nazwisko << endl;
        cout << "Telefon: "<<adresaci[indeksSzukanego].telefon << endl;
        cout << "Email: " << adresaci[indeksSzukanego].email << endl;
        cout << "Adres: " << adresaci[indeksSzukanego].adres << endl;
        cout << " --- --- ---" << endl;
        cout <<"Czy na pewno chcesz usunac powyzszego adresata? t/n" << endl;
        cin>>potwierdzenie;
        if (potwierdzenie == 't')
        {
            adresaci.erase(adresaci.begin()+indeksSzukanego);
            *usunieto=true;
            cout<<"Usunieto adresata o id:  " << idSzukane << "." << endl;
        }
    }
    else
        cout<<"W twojej ksiazce nie ma adresata o id:  " << idSzukane << "." << endl;
    system("pause");
    return adresaci;
}

void nadpiszZmienioneDaneDoPliku(vector<Adresat> adresaci)
{
    string daneAdresata,stringId;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::out);
    if (plik.good() == true)
    {
        for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
        {
            stringId=konwersjaIntToString(indeksVectora->id);
            daneAdresata=stringId+"|"+indeksVectora->imie+"|"+indeksVectora->nazwisko+"|"+indeksVectora->telefon+"|"+indeksVectora->email+"|"+indeksVectora->adres+"|";
            plik << daneAdresata << endl;
        }
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}
vector<Adresat> edytujDaneAdresataOPodanymId(vector<Adresat> adresaci, bool* zmieniono)
{
    int idSzukane;
    char wyborEdycji='0';
    int   indeksSzukanego = 0;
    cout << endl;
    cout << "Podaj id adresata, ktorego  chcesz edytowac: " << endl;
    cin >> idSzukane;
    bool znaleziono = false;
    system("cls");
    for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        if(idSzukane == indeksVectora->id)
        {
            znaleziono=true;
            break;
        }
        else indeksSzukanego++;
    }
    if (znaleziono)
    {
        while(wyborEdycji!='6')
        {
            system("cls");
            cout <<"Dane znalezionego adresata: "<<endl;
            cout << "ID: " << adresaci[indeksSzukanego].id << endl;
            cout << "Imie i nazwisko: " <<adresaci[indeksSzukanego].imie << " " << adresaci[indeksSzukanego].nazwisko << endl;
            cout << "Telefon: "<<adresaci[indeksSzukanego].telefon << endl;
            cout << "Email: " << adresaci[indeksSzukanego].email << endl;
            cout << "Adres: " << adresaci[indeksSzukanego].adres << endl;
            cout << " --- --- ---" << endl;
            cout << "EDYCJA DANYCH" << endl;
            cout <<  " --- --- ---" << endl;
            cout << "1 - imie " << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu glownego" << endl;
            cout <<  " --- --- ---" << endl;
            cout << "Twoj wybor: " << endl;

            cin>>wyborEdycji;
            switch(wyborEdycji)
            {
            case '1' :
                cout << "Podaj nowe imie: "<<endl;
                cin>>adresaci[indeksSzukanego].imie;
                *zmieniono = true;
                cout << "Zmieniono imie adresata o id:  " << idSzukane << "." << endl;
                break;
            case '2' :
                cout << "Podaj nowe nazwisko: "<<endl;
                cin>>adresaci[indeksSzukanego].nazwisko;
                *zmieniono=true;
                cout << "Zmieniono nazwisko adresata o id:  " << idSzukane << "." << endl;
                break;
            case '3' :
                cout << "Podaj nowy numer telefonu: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].telefon);
                *zmieniono=true;
                cout << "Zmieniono numer telefonu adresata o id:  " << idSzukane << "." << endl;
                break;
            case '4' :
                cout << "Podaj nowy email: "<<endl;
                cin>>adresaci[indeksSzukanego].email;
                *zmieniono=true;
                cout << "Zmieniono email adresata o id:  " << idSzukane << "." << endl;
                break;
            case '5' :
                cout << "Podaj nowy adres: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].adres);
                *zmieniono=true;
                cout << "Zmieniono adres adresata o id:  " << idSzukane << "." << endl;
                break;
            case '6' :
                break;
            default:
                cout << "Nie ma takiej opcji w menu, podaj poprawna opcje po ukazaniu sie menu" << endl;
                system("pause");
            }
        }
    }
    else
        cout<<"W twojej ksiazce nie ma adresata o id:  " << idSzukane << "." << endl;
    system("pause");
    return adresaci;
}

int main()
{
    vector<Adresat> adresaci;
    bool* usunieto = new bool;
    *usunieto = false;
    bool* zmieniono = new bool;
    *zmieniono = false;
    int dostepneId = 1;
    char wybor;
    adresaci = wczytanieKsiazkiAdresowjZPliku();
    dostepneId = znajdzDostepneId(adresaci);
    while(1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout <<  " --- --- ---" << endl;
        cout << "1.Dodaj nowego adresata " << endl;
        cout << "2.Wyszukaj  po imieniu" << endl;
        cout << "3.Wyszukaj po nazwisku" << endl;
        cout << "4.Wyswietl wszystkich adresatow" << endl;
        cout << "5.Usun adresata" << endl;
        cout << "6.Edytuj adresata" << endl;
        cout << "9.Zakoncz program " << endl;
        cout <<  " --- --- ---" << endl;
        cout << "Twoj wybor: " << endl;
        cin >> wybor;
        switch(wybor)
        {
        case '1' :
            adresaci = wprowadzDaneAdresata(adresaci, dostepneId);
            dostepneId = znajdzDostepneId(adresaci);
            break;
        case '2' :
            wyszukajPoImieniu(adresaci);
            break;
        case '3' :
            wyszukajPoNazwisku(adresaci);
            break;
        case '4' :
            wyswietlWszystkichAdresatow(adresaci);
            break;
        case '5' :
            adresaci = usunAdresataOPodanymId(adresaci, usunieto);
            if(*usunieto)
            {
                nadpiszZmienioneDaneDoPliku(adresaci);
                *usunieto = false;
                dostepneId = znajdzDostepneId(adresaci);
            }
            break;
        case '6' :
            adresaci = edytujDaneAdresataOPodanymId(adresaci,zmieniono);
            if(*zmieniono)
            {
                nadpiszZmienioneDaneDoPliku(adresaci);
                *zmieniono=false;
            }
            break;
        case '9' :
            delete usunieto;
            delete zmieniono;
            exit(0);
        default:
            cout << "Nie ma takiej opcji w menu, podaj poprawna opcje po ukazaniu sie menu" << endl;
            system("pause");
        }
    }
    return 0;
}

