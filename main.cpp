#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
string nazwaPlikuAdresatow = "ksiazkaAdresowa.txt";
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
bool alfabetyczniePoNazwiskuIImieniu(Adresat lewy, Adresat prawy)
{
    if(lewy.nazwisko == prawy.nazwisko )
        return (lewy.imie<prawy.imie);
    else
        return(lewy.nazwisko<prawy.nazwisko);
}
int znajdzDostepneId(vector<Adresat> &adresaci)
{
    int maxi=0;
    for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)

    {
        if(indeksVectora->id > maxi)
            maxi=indeksVectora->id;
    }
    return maxi+1;
}
int wczytajKsiazkeAdresowaZPliku(vector<Adresat> &adresaci)
{
    string linia;
    int dostepneId;
    fstream plik;
    Adresat adresat;
    plik.open( nazwaPlikuAdresatow.c_str(), ios::in);
    if (plik.good() == true)
    {
        while (getline(plik, linia))
        {
            adresat = podzielDaneNaPojedynczeSkladniki(linia);
            adresaci.push_back(adresat);
        }
        sort( adresaci.begin(), adresaci.end(), alfabetyczniePoNazwiskuIImieniu);
        plik.close();
        dostepneId = znajdzDostepneId(adresaci);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku"<<endl;
        dostepneId=1;
        system("pause");
    }
    return dostepneId;
}
void wyswietlWszystkichAdresatow(vector<Adresat> &adresaci)
{
    system("cls");
    cout << " -- Osoby zapisane w Twojej ksiazce adresowej --" << endl << endl;
    for(vector<Adresat>::iterator itr = adresaci.begin(),koniec = adresaci.end(); itr!=koniec; ++itr)
    {
        cout << endl;
        cout << "ID:               " << itr->id << endl;
        cout << "Imie i nazwisko:  " << itr->imie << " " << itr->nazwisko<<endl;
        cout << "Telefon:          " << itr->telefon << endl;
        cout << "Email:            " << itr->email << endl;
        cout << "Adres:            " << itr->adres << endl;
        cout << endl << endl;
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
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}
void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plikText;
    plikText.open(nazwaPlikuAdresatow.c_str(), ios::out | ios::app);

    if (plikText.good() == true)
    {
        plikText << adresat.id << '|';
        plikText << adresat.imie << '|';
        plikText << adresat.nazwisko << '|';
        plikText << adresat.telefon << '|';
        plikText << adresat.email << '|';
        plikText << adresat.adres << '|' << endl;
        plikText.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
int wprowadzDaneAdresata(vector<Adresat> &adresaci, int dostepneId)
{
    Adresat adresat;
    string imieKolejne;
    string nazwiskoKolejne;
    string daneAdresata;
    bool znalezionoAdresata=false;
    cout << "Podaj imie:  " << endl;
    cin >> adresat.imie;
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale( adresat.imie);
    cout << "Podaj nazwisko:  " << endl;
    cin >> adresat.nazwisko;
    adresat.nazwisko=zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);
    vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end();
    while(indeksVectora!=koniecVectora)
    {
        imieKolejne = indeksVectora->imie;
        nazwiskoKolejne = indeksVectora->nazwisko;
        if ((nazwiskoKolejne == adresat.nazwisko) && (imieKolejne == adresat.imie ))
        {
            cout << "Taki adresat jest juz w twojej ksiazce. " << endl;
            cout << endl;
            cout << "ID:              " << indeksVectora->id << endl;
            cout << "Imie i nazwisko: " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon:         " << indeksVectora->telefon<<endl;
            cout << "Email:           " << indeksVectora->email << endl;
            cout << "Adres:           " << indeksVectora->adres << endl;
            cout << endl << endl;
            system("pause");
            znalezionoAdresata = true;
        }
        ++indeksVectora;
    }
    if(!znalezionoAdresata)
    {
        adresat.id = dostepneId;
        cout << "Podaj telefon:  " << endl;
        cin.sync();
        getline(cin, adresat.telefon);
        cout << "Podaj email:  " << endl;
        cin >> adresat.email;
        cout << "Podaj adres:  " << endl;
        cin.sync();
        getline(cin,adresat.adres);
        adresaci.push_back(adresat);
        sort( adresaci.begin(), adresaci.end(), alfabetyczniePoNazwiskuIImieniu);
        dostepneId++;
        dopiszAdresataDoPliku(adresat);
    }
    return dostepneId;
}
void wyszukajPoImieniu(vector<Adresat> &adresaci)
{
    string imieSzukane, imieKolejne;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj imie osob, ktorych dane chcesz odszukac: " << endl;
    cin >> imieSzukane;
    imieSzukane=zamienPierwszaLitereNaDuzaAPozostaleNaMale(imieSzukane);
    system("cls");
    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        imieKolejne = indeksVectora->imie;
        imieKolejne = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imieKolejne);
        if(imieKolejne == imieSzukane)
        {
            cout << endl;
            cout << "ID:              " << indeksVectora->id << endl;
            cout << "Imie i nazwisko: " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon:         " << indeksVectora->telefon << endl;
            cout << "Email:           " << indeksVectora->email << endl;
            cout << "Adres:           " << indeksVectora->adres << endl;
            cout << endl << endl;
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
    nazwiskoSzukane=zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoSzukane);
    system("cls");
    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        nazwiskoKolejne = indeksVectora->nazwisko;
        nazwiskoKolejne = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoKolejne);
        if(nazwiskoKolejne == nazwiskoSzukane)
        {
            cout << endl;
            cout << "ID:               " << indeksVectora->id << endl;
            cout << "Imie i nazwisko:  " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon:          "<<indeksVectora->telefon << endl;
            cout << "Email:            " << indeksVectora->email << endl;
            cout << "Adres:            " << indeksVectora->adres << endl;
            cout << endl << endl;
            iloscOsobZnalezionych++;
        }
    }
    if (iloscOsobZnalezionych == 0)
        cout << "W twojej ksiazce nie ma osob o nazwisku " << nazwiskoSzukane << " ." << endl;
    else
        cout<<"W twojej ksiazce jest " << iloscOsobZnalezionych << " osob o nazwisku " << nazwiskoSzukane << "." << endl;
    system("pause");
}
void zapiszWszystkichAdresatowDoPliku(vector<Adresat> &adresaci)
{
    string daneAdresata;
    fstream plikText;
    plikText.open(nazwaPlikuAdresatow.c_str(),ios::out);
    if (plikText.good() == true)
    {
        for ( vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
        {
            daneAdresata=konwersjaIntToString(indeksVectora->id)+"|"+indeksVectora->imie+"|"+indeksVectora->nazwisko+"|"+indeksVectora->telefon+"|"+indeksVectora->email+"|"+indeksVectora->adres+"|";
            plikText << daneAdresata << endl;
        }
        plikText.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}
int usunAdresataOPodanymId(vector<Adresat> &adresaci, int dostepneId)
{
    int idSzukane;
    char potwierdzenie;
    int indeksSzukanego = 0;
    int dostepneIdPoUsunieciu;
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
            indeksSzukanego++;
    }
    if (znaleziono)
    {
        system("cls");
        cout << " USUWANIE ADRESATA" << endl<<endl;
        cout <<" Dane adresata, ktorego chesz usunac: "<<endl;
        cout << "ID: " << adresaci[indeksSzukanego].id << endl;
        cout << "Imie i nazwisko: " <<adresaci[indeksSzukanego].imie << " " << adresaci[indeksSzukanego].nazwisko << endl;
        cout << "Telefon: "<<adresaci[indeksSzukanego].telefon << endl;
        cout << "Email: " << adresaci[indeksSzukanego].email << endl;
        cout << "Adres: " << adresaci[indeksSzukanego].adres <<endl<< endl;

        cout <<"Czy napewno chesz usunac adresata t/n" << endl;
        cin >> potwierdzenie;
        if (potwierdzenie == 't')
        {
           adresaci.erase(adresaci.begin()+indeksSzukanego);

            zapiszWszystkichAdresatowDoPliku(adresaci);
            dostepneIdPoUsunieciu = znajdzDostepneId(adresaci);
            cout<<"Usunieto adresata o id:  " << idSzukane << "." << endl;
        }
        else
           {    dostepneIdPoUsunieciu = dostepneId;
              cout<<"Nie usunieto adresata o id:  " << idSzukane << "." << endl;
           }
    }
    else
        cout<<"W twojej ksiazce nie ma adresata o id:  " << idSzukane << "." << endl;
    system("pause");
    return dostepneIdPoUsunieciu;
}

void edytujDaneAdresataOPodanymId(vector<Adresat> &adresaci)
{ bool zmienionoImieLubNazwisko = false;
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
            cout <<"Dane znalezionego adresata: "<< endl <<endl;
            cout << "ID:              " << adresaci[indeksSzukanego].id << endl;
            cout << "Imie i nazwisko: " <<adresaci[indeksSzukanego].imie << " " << adresaci[indeksSzukanego].nazwisko << endl;
            cout << "Telefon:         " <<adresaci[indeksSzukanego].telefon << endl;
            cout << "Email:           " << adresaci[indeksSzukanego].email << endl;
            cout << "Adres:           " << adresaci[indeksSzukanego].adres << endl;
            cout << endl << endl;
            cout << "EDYCJA DANYCH" << endl;
            cout <<  endl << endl;
            cout << "1 - imie " << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu glownego" << endl;
            cout <<  endl << endl;
            cout << "Twoj wybor: " << endl;

            cin>>wyborEdycji;
            switch(wyborEdycji)
            {
            case '1' :
                cout << "Podaj nowe imie: "<<endl;
                cin>>adresaci[indeksSzukanego].imie;
                adresaci[indeksSzukanego].imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresaci[indeksSzukanego].imie);
                zapiszWszystkichAdresatowDoPliku(adresaci);
                zmienionoImieLubNazwisko = true;
                cout << "Zmieniono imie adresata o id:  " << idSzukane << "." << endl;
                break;
            case '2' :
                cout << "Podaj nowe nazwisko: "<<endl;
                cin>>adresaci[indeksSzukanego].nazwisko;
                adresaci[indeksSzukanego].nazwisko=zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresaci[indeksSzukanego].nazwisko);
                zapiszWszystkichAdresatowDoPliku(adresaci);
                zmienionoImieLubNazwisko = true;
                cout << "Zmieniono nazwisko adresata o id:  " << idSzukane << "." << endl;
                break;
            case '3' :
                cout << "Podaj nowy numer telefonu: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].telefon);
                zapiszWszystkichAdresatowDoPliku(adresaci);
                cout << "Zmieniono numer telefonu adresata o id:  " << idSzukane << "." << endl;
                break;
            case '4' :
                cout << "Podaj nowy email: "<<endl;
                cin>>adresaci[indeksSzukanego].email;
                zapiszWszystkichAdresatowDoPliku(adresaci);
                cout << "Zmieniono email adresata o id:  " << idSzukane << "." << endl;
                break;
            case '5' :
                cout << "Podaj nowy adres: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].adres);
                zapiszWszystkichAdresatowDoPliku(adresaci);
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
        if( zmienionoImieLubNazwisko)
            sort( adresaci.begin(), adresaci.end(), alfabetyczniePoNazwiskuIImieniu);
    system("pause");
}
int main()
{
    vector<Adresat> adresaci;
    int dostepneId;
    char wybor;
    dostepneId = wczytajKsiazkeAdresowaZPliku(adresaci);
    while(1)
    {
        system("cls");
        cout << ">>KSIAZKA ADRESOWA<<" << endl<<endl;
        cout << "1.Dodaj nowego adresata " << endl;
        cout << "2.Wyszukaj  po imieniu" << endl;
        cout << "3.Wyszukaj po nazwisku" << endl;
        cout << "4.Wyswietl wszystkich adresatow" << endl;
        cout << "5.Usun adresata" << endl;
        cout << "6.Edytuj adresata" << endl;
        cout << "9.Zakoncz program " << endl;
        cout << endl<< "Twoj wybor: " << endl;
        cin >> wybor;
        switch(wybor)
        {
        case '1' :
            dostepneId = wprowadzDaneAdresata(adresaci, dostepneId);
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
            dostepneId = usunAdresataOPodanymId(adresaci, dostepneId);
            break;
        case '6' :
            edytujDaneAdresataOPodanymId(adresaci);
            break;
        case '9' :
            cout<<endl<<"KONIEC PROGRAMU"<<endl;
            exit(0);
        default:
            cout << "Nie ma takiej opcji w menu, podaj poprawna opcje po ukazaniu sie menu" << endl;
            system("pause");
        }
    }
    return 0;
}
