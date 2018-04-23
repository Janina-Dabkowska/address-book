#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
string nazwaPlikuUzytkownikow = "Uzytkownicy.txt";
string nazwaPlikuAdresatow = "Adresaci.txt";
string nazwaTymczasowaPlikuAdresatow = "Adresaci_tymczasowy.txt";
struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};
struct Adresat
{
    int id,idUzytkownika;
    string imie, nazwisko, telefon, email, adres;
};
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}
string konwersjaIntToString(int liczbaInt)
{
    ostringstream ss;
    ss << liczbaInt;
    string liczbaString = ss.str();

    return liczbaString;
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuUzytkownikow.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.id << '|';
        plikTekstowy << uzytkownik.nazwa << '|';
        plikTekstowy << uzytkownik.haslo << '|'<< endl;
        plikTekstowy.close();

        cout << endl << "Uzytkownik zostal zapisany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy i zapisac w nim danych." << endl;
        system("pause");
    }
}
void zapiszWszystkichUzytkownikowDoPlikuTekstowego(vector<Uzytkownik> &uzytkownicy)
{
    fstream plikTekstowy;
    string liniaZDanymiUzytkownika= "";

    plikTekstowy.open(nazwaPlikuUzytkownikow.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwersjaIntToString(itr->id) + '|';
            liniaZDanymiUzytkownika += itr->nazwa + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plikTekstowy << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
    }
}

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownika)
{
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;
    int dlugosc=daneUzytkownika.length();
    for (int pozycjaZnaku = 0; pozycjaZnaku < dlugosc; pozycjaZnaku++)
    {
        if (daneUzytkownika[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownika[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.nazwa = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownika = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuUzytkownikow.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoUzytkownika))
        {
            uzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownika);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}
void rejestracja(vector<Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string nazwa, haslo;
    Uzytkownik uzytkownik;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;
    int i=0;
    while( i<iloscUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            cout<<"Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>nazwa;
            i=0;
        }
        else
            i++;
    }
    uzytkownik.nazwa=nazwa;

    cout<<"Podaj haslo: ";
    cin>>haslo;
    uzytkownik.haslo=haslo;
    uzytkownik.id = iloscUzytkownikow+1;
    uzytkownicy.push_back(uzytkownik);
    dopiszUzytkownikaDoPliku(uzytkownik);

}
int logowanie(vector<Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;
    int i = 0;
    while( i<iloscUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby = 0; proby<3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob: "<< 3-proby <<" : ";
                cin>>haslo;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout<< "Zalogowales sie. ";
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 minuty: ";
            system("pause");
            return 0;
        }
        else
            i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem.";
    system("pause");
    return 0;
}
void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if ( uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout<< "Haslo zostalo zmienione. ";
            zapiszWszystkichUzytkownikowDoPlikuTekstowego(uzytkownicy);
            system("pause");
        }
    }
}
bool alfabetyczniePoNazwiskuIImieniu(Adresat lewy, Adresat prawy)
{
    if(lewy.nazwisko == prawy.nazwisko )
        return (lewy.imie<prawy.imie);
    else
        return(lewy.nazwisko<prawy.nazwisko);
}
Adresat pobierzDaneAdresata(string daneAdresata)
{
    Adresat adresat;
    string pojedynczaDanaAdresata;
    int dlugosc = daneAdresata.length();
    int numerPojedynczejDanejAdresata = 1;
    for (int pozycjaZnaku = 0; pozycjaZnaku < dlugosc; pozycjaZnaku++)
    {
        if (daneAdresata[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresata[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.telefon = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;

            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}
int wczytajKsiazkeAdresowaZPliku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string linia;
    int dostepneId=1;
    fstream plik;
    Adresat adresat;
    plik.open( nazwaPlikuAdresatow.c_str(), ios::in);
    if (plik.good() == true)
    {
        while (getline(plik, linia))
        {
            adresat = pobierzDaneAdresata(linia);
            if(dostepneId<adresat.id+1)
                dostepneId = adresat.id+1;

            if(adresat.idUzytkownika == idZalogowanegoUzytkownika)
                adresaci.push_back(adresat);
        }
        sort( adresaci.begin(), adresaci.end(), alfabetyczniePoNazwiskuIImieniu);
        plik.close();

    }
    else
    {
        cout << "Nie mozna otworzyc pliku"<<endl;

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
void wyszukajPoImieniu(vector<Adresat> &adresaci)
{
    string imieSzukane;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj imie osob, ktorych dane chcesz odszukac: " << endl;
    cin >> imieSzukane;
    imieSzukane = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imieSzukane);
    system("cls");
    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        if(indeksVectora->imie == imieSzukane)
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
    string nazwiskoSzukane;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj nazwisko osob, ktorych dane chcesz odszukac: " << endl;
    cin >> nazwiskoSzukane;
    nazwiskoSzukane = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoSzukane);
    system("cls");
    for(vector<Adresat>::iterator indeksVectora = adresaci.begin(),koniecVectora = adresaci.end(); indeksVectora!=koniecVectora; ++indeksVectora)
    {
        if(indeksVectora->nazwisko == nazwiskoSzukane)
        {
            cout << endl;
            cout << "ID:               " << indeksVectora->id << endl;
            cout << "Imie i nazwisko:  " << indeksVectora->imie << " " << indeksVectora->nazwisko << endl;
            cout << "Telefon:          " << indeksVectora->telefon << endl;
            cout << "Email:            " << indeksVectora->email << endl;
            cout << "Adres:            " << indeksVectora->adres << endl;
            cout << endl << endl;
            iloscOsobZnalezionych++;
        }
    }
    if (iloscOsobZnalezionych == 0)
        cout << "W twojej ksiazce nie ma osob o nazwisku " << nazwiskoSzukane << " ." << endl;
    else
        cout <<"W twojej ksiazce jest " << iloscOsobZnalezionych << " osob o nazwisku " << nazwiskoSzukane << "." << endl;
    system("pause");
}
void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plikText;
    plikText.open(nazwaPlikuAdresatow.c_str(), ios::out | ios::app);

    if (plikText.good() == true)
    {
        plikText << adresat.id << '|';
        plikText << adresat.idUzytkownika << '|';
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
        cout << "Nie udalo sie otworzyc pliku Adresatow i zapisac w nim danych." << endl;
        system("pause");
    }
}
int wprowadzDaneAdresata(vector<Adresat> &adresaci, int dostepneId,int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string imieKolejne;
    string nazwiskoKolejne;
    string daneAdresata;
    bool znalezionoAdresata = false;
    cout << "Podaj imie:  " << endl;
    cin >> adresat.imie;
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale( adresat.imie);
    cout << "Podaj nazwisko:  " << endl;
    cin >> adresat.nazwisko;
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);
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
            cout << "Telefon:         " << indeksVectora->telefon <<endl;
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
        adresat.idUzytkownika = idZalogowanegoUzytkownika;
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
int pobierzIdAdresata(string daneJednegoAdresata)
{
    string idAdresata="";
    int pozycja=0;
    while(daneJednegoAdresata[pozycja]!='|')
    {
        idAdresata+=daneJednegoAdresata[pozycja];
        pozycja++;

    }
    return atoi(idAdresata.c_str());
}
string utworzLinieZDanymiAdresata(Adresat adresat)
{
    string liniaZDanymiAdresata= konwersjaIntToString(adresat.id) + '|';
    liniaZDanymiAdresata += konwersjaIntToString(adresat.idUzytkownika) + '|';
    liniaZDanymiAdresata += adresat.imie + '|';
    liniaZDanymiAdresata += adresat.nazwisko + '|';
    liniaZDanymiAdresata += adresat.telefon + '|';
    liniaZDanymiAdresata += adresat.email + '|';
    liniaZDanymiAdresata += adresat.adres + '|';
    return liniaZDanymiAdresata;
}


void usunDaneAdresataZPliku( int idAdresataDoUsuniecia)
{
    fstream plikTekstowyAktualny, plikTekstowyTymczasowy;
    string daneJednegoAdresata;
    int idAdresata;
    plikTekstowyAktualny.open(nazwaPlikuAdresatow.c_str(), ios::in);

    if (plikTekstowyAktualny.good() == true)
    {
        plikTekstowyTymczasowy.open(nazwaTymczasowaPlikuAdresatow.c_str(), ios::out);
        if (plikTekstowyTymczasowy.good() == true)
        {
            while (getline(plikTekstowyAktualny, daneJednegoAdresata))
            {
                idAdresata=pobierzIdAdresata(daneJednegoAdresata);
                if(idAdresata != idAdresataDoUsuniecia)
                    plikTekstowyTymczasowy << daneJednegoAdresata << endl;
            }
            plikTekstowyTymczasowy.close();
        }
        else cout<< "Nie mozna otworzyc pliku tymczasowego adresatow.";
        plikTekstowyAktualny.close();
        remove (nazwaPlikuAdresatow.c_str() );
        rename (nazwaTymczasowaPlikuAdresatow.c_str(),nazwaPlikuAdresatow.c_str());
    }
    else cout<< "Nie mozna otworzyc pliku adresatow.";

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
            if(adresaci[indeksSzukanego].id+1 == dostepneId)
                dostepneIdPoUsunieciu=adresaci[indeksSzukanego].id;
            else dostepneIdPoUsunieciu = dostepneId;
            usunDaneAdresataZPliku( adresaci[indeksSzukanego].id);
            adresaci.erase(adresaci.begin()+indeksSzukanego);
            cout<<"Usunieto adresata o id:  " << idSzukane << "." << endl;
        }
        else
        {
            dostepneIdPoUsunieciu = dostepneId;
            cout<<"Nie usunieto adresata o id:  " << idSzukane << "." << endl;
        }
    }
    else
        cout<<"W twojej ksiazce nie ma adresata o id:  " << idSzukane << "." << endl;
    system("pause");
    return dostepneIdPoUsunieciu;
}
void zapiszZmienioneDaneAdresataDoPliku( string noweDaneAdresata,int idAdresataDoZamiany)
{
    fstream plikTekstowyAktualny, plikTekstowyTymczasowy;
    string daneJednegoAdresata;
    int idAdresata;
    plikTekstowyAktualny.open(nazwaPlikuAdresatow.c_str(), ios::in);

    if (plikTekstowyAktualny.good() == true)
    {
        plikTekstowyTymczasowy.open(nazwaTymczasowaPlikuAdresatow.c_str(), ios::out);
        if (plikTekstowyTymczasowy.good() == true)
        {
            while (getline(plikTekstowyAktualny, daneJednegoAdresata))
            {
                idAdresata = pobierzIdAdresata(daneJednegoAdresata);
                if(idAdresata == idAdresataDoZamiany)
                    plikTekstowyTymczasowy << noweDaneAdresata << endl;
                else
                    plikTekstowyTymczasowy << daneJednegoAdresata << endl;
            }
            plikTekstowyTymczasowy.close();
        }
        else cout<< "Nie mozna otworzyc pliku tymczasowego.";
        plikTekstowyAktualny.close();
        remove (nazwaPlikuAdresatow.c_str() );
        rename (nazwaTymczasowaPlikuAdresatow.c_str(),nazwaPlikuAdresatow.c_str());
    }
    else cout<< "Nie mozna otworzyc pliku adresatow.";
}
void edytujDaneAdresataOPodanymId(vector<Adresat> &adresaci)
{
    string daneAdresataOdzieloneKreskami;
    bool zmienionoImieLubNazwisko = false;
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
            cout << "Imie i nazwisko: " << adresaci[indeksSzukanego].imie << " " << adresaci[indeksSzukanego].nazwisko << endl;
            cout << "Telefon:         " << adresaci[indeksSzukanego].telefon << endl;
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
                zapiszZmienioneDaneAdresataDoPliku( utworzLinieZDanymiAdresata(adresaci[indeksSzukanego]),adresaci[indeksSzukanego].id);
                zmienionoImieLubNazwisko = true;
                cout << "Zmieniono imie adresata o id:  " << idSzukane << "." << endl;
                break;
            case '2' :
                cout << "Podaj nowe nazwisko: "<<endl;
                cin>>adresaci[indeksSzukanego].nazwisko;
                adresaci[indeksSzukanego].nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresaci[indeksSzukanego].nazwisko);
                zapiszZmienioneDaneAdresataDoPliku( utworzLinieZDanymiAdresata(adresaci[indeksSzukanego]),adresaci[indeksSzukanego].id);
                zmienionoImieLubNazwisko = true;
                cout << "Zmieniono nazwisko adresata o id:  " << idSzukane << "." << endl;
                break;
            case '3' :
                cout << "Podaj nowy numer telefonu: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].telefon);
                zapiszZmienioneDaneAdresataDoPliku( utworzLinieZDanymiAdresata(adresaci[indeksSzukanego]),adresaci[indeksSzukanego].id);
                cout << "Zmieniono numer telefonu adresata o id:  " << idSzukane << "." << endl;
                break;
            case '4' :
                cout << "Podaj nowy email: "<<endl;
                cin>>adresaci[indeksSzukanego].email;
                zapiszZmienioneDaneAdresataDoPliku( utworzLinieZDanymiAdresata(adresaci[indeksSzukanego]),adresaci[indeksSzukanego].id);
                cout << "Zmieniono email adresata o id:  " << idSzukane << "." << endl;
                break;
            case '5' :
                cout << "Podaj nowy adres: "<<endl;
                cin.sync();
                getline(cin, adresaci[indeksSzukanego].adres);
                zapiszZmienioneDaneAdresataDoPliku( utworzLinieZDanymiAdresata(adresaci[indeksSzukanego]),adresaci[indeksSzukanego].id);
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
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    vector<Adresat> adresaci;
    int dostepneId;
    wczytajUzytkownikowZPliku(uzytkownicy);
    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << ">>KSIAZKA ADRESOWA<<" << endl<<endl;
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "9.Zakoncz program " << endl;
            cin >> wybor;
            if(wybor == '1')
                rejestracja(uzytkownicy);
            else if(wybor == '2')
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            else if(wybor == '9')
                exit(0);
        }
        else
        {
            if(!adresaci.empty())
            {
                adresaci.clear();
            }
            dostepneId = wczytajKsiazkeAdresowaZPliku(adresaci,idZalogowanegoUzytkownika);

            system("cls");
            cout << ">>KSIAZKA ADRESOWA<<" << endl<<endl;
            cout << "1.Dodaj nowego adresata " << endl;
            cout << "2.Wyszukaj  po imieniu" << endl;
            cout << "3.Wyszukaj po nazwisku" << endl;
            cout << "4.Wyswietl wszystkich adresatow" << endl;
            cout << "5.Usun adresata" << endl;
            cout << "6.Edytuj adresata" << endl;
            cout << "7.Zmien haslo" << endl;
            cout << "8.Wyloguj" << endl;
            cout << endl<< "Twoj wybor: " << endl;
            cin >> wybor;
            switch(wybor)
            {
            case '1' :
                dostepneId = wprowadzDaneAdresata(adresaci, dostepneId, idZalogowanegoUzytkownika);
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
            case '7' :
                zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
                break;
            case '8' :
                idZalogowanegoUzytkownika = 0;
                break;
            default:
                cout << "Nie ma takiej opcji w menu, podaj poprawna opcje po ukazaniu sie menu" << endl;
                system("pause");
            }
        }
    }
    return 0;
}

