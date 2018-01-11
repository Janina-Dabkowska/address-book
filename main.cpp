#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, telefon, email, adres;
};

int wczytanieKsiazkiAdresowjZPliku(Adresat adresaci[]) {
    int nrLinii = 1;
    string linia;
    int iloscAdresatow = 0;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);
    if (plik.good() == true) {
        while (getline(plik, linia)) {
            switch(nrLinii) {
            case 1:
                adresaci[iloscAdresatow].id = atoi(linia.c_str());
                break;
            case 2:
                adresaci[iloscAdresatow].imie = linia;
                break;
            case 3:
                adresaci[iloscAdresatow].nazwisko = linia;
                break;
            case 4:
                adresaci[iloscAdresatow].telefon = linia;
                break;
            case 5:
                adresaci[iloscAdresatow].email = linia;
                break;
            case 6:
                adresaci[iloscAdresatow].adres = linia;
                break;
            }
            if (nrLinii == 6) {
                nrLinii = 0;
                iloscAdresatow++;
            }
            nrLinii++;
        }
        plik.close();

    } else {
        cout << "Nie mozna otworzyc pliku"<<endl;
        system("pause");
    }
    return iloscAdresatow;
}
// quicksort wed³ug nazwisk
void sortujPoNazwisku(Adresat adresaci[], int lewy, int prawy) {
    Adresat pivot = adresaci[(lewy+prawy)/2];
    int i,j;
    Adresat roboczy;
    i=lewy;
    j=prawy;
    do {
        while(adresaci[i].nazwisko < pivot.nazwisko) i++;
        while(adresaci[j].nazwisko > pivot.nazwisko) j--;
        if(i<=j) {
            roboczy=adresaci[i];
            adresaci[i] = adresaci[j];
            adresaci[j] = roboczy;
            i++;
            j--;
        }
    } while(i<=j);
    if(j>lewy) sortujPoNazwisku(adresaci, lewy, j);
    if(i<prawy) sortujPoNazwisku(adresaci, i, prawy);
}
// quicksort wed³ug imion
void sortujPoImieniu(Adresat adresaci[], int lewy, int prawy) {
    Adresat pivot = adresaci[(lewy+prawy)/2];
    int i,j;
    Adresat roboczy;
    i = lewy;
    j = prawy;
    do {
        while(adresaci[i].imie < pivot.imie)
            i++;
        while(adresaci[j].imie > pivot.imie)
            j--;
        if(i <= j) {
            roboczy=adresaci[i];
            adresaci[i] = adresaci[j];
            adresaci[j] = roboczy;
            i++;
            j--;
        }
    } while(i <= j);
    if(j > lewy)
        sortujPoImieniu(adresaci, lewy, j);
    if(i < prawy)
        sortujPoImieniu(adresaci, i, prawy);
}
void sortujAlfabetycznie( Adresat adresaci[],int iloscAdresatow) {
    int iloscOsobONazwisku = 0;
    sortujPoNazwisku(adresaci,0,iloscAdresatow-1);
    for(int i = 0; i < iloscAdresatow-1; i++) {
        if(adresaci[i].nazwisko == adresaci[i+1].nazwisko)
            iloscOsobONazwisku++;
        else if (iloscOsobONazwisku > 0) {
            sortujPoImieniu(adresaci, i-iloscOsobONazwisku, i );//sortuje po imieniu czesc tablicy z takimi samymi nazwiskami
            iloscOsobONazwisku = 0;
        }
    }
}
void wyswietlWszystkichAdresatow(Adresat adresaci[], int iloscAdresatow) {
    system("cls");
    cout << " -- Osoby zapisane w Twojej ksiazce adresowej --" << endl << endl;
    for(int indeksTablicy=0; indeksTablicy < iloscAdresatow; indeksTablicy++) {
        cout <<  "Imie i nazwisko: " << adresaci[indeksTablicy].imie << " " << adresaci[indeksTablicy].nazwisko<<endl;
        cout << "Telefon: " << adresaci[indeksTablicy].telefon << endl;
        cout << "Email: " << adresaci[indeksTablicy].email << endl;
        cout << "Adres: " << adresaci[indeksTablicy].adres << endl;
        cout <<  " --- --- ---" << endl;
    }
    cout << "Masz zapisanych  " << iloscAdresatow << " adresatow." << endl;
    system("pause");
}
void ustawAlfabetycznieOstatniego(Adresat adresaci[], int iloscAdresatow) {
    Adresat ostatni = adresaci[iloscAdresatow-1];
    int     licznik = iloscAdresatow-2;
    while ((licznik>=0)&&(adresaci[licznik].nazwisko > ostatni.nazwisko)){
        adresaci[licznik+1] = adresaci[licznik];
        licznik--;
    }
    while((licznik>=0)&&(adresaci[licznik].nazwisko == ostatni.nazwisko && adresaci[licznik].imie > ostatni.imie)) {
        adresaci[licznik+1] = adresaci[licznik];
        licznik--;
    }
	if (licznik < iloscAdresatow-2)//jesli sa adresaci pózniejsi w alfabecie od ostatniego
    adresaci[licznik+1] = ostatni;
}
int wprowadzDaneAdresata(Adresat adresaci[], int iloscAdresatow) {
    int indeksTablicy = 0;
    string imie, nazwisko;

    cout << "Podaj imie:  " << endl;
    cin >> imie;
    cout << "Podaj nazwisko:  " << endl;
    cin >> nazwisko;
    while(indeksTablicy < iloscAdresatow) {
        if ((adresaci[indeksTablicy].nazwisko == nazwisko) && (adresaci[indeksTablicy].imie == imie )) {
            cout << "Taki adresat jest juz w twojej ksiazce. " << endl;
            cout << "Imie i nazwisko: " << adresaci[indeksTablicy].imie << " " << adresaci[indeksTablicy].nazwisko << endl;
            cout << "Telefon: "<<adresaci[indeksTablicy].telefon<<endl;
            cout << "Email: " << adresaci[indeksTablicy].email << endl;
            cout << "Adres: " << adresaci[indeksTablicy].adres << endl;
            cout << " --- --- ---" << endl;
            system("pause");
            return iloscAdresatow;
        }
        indeksTablicy++;
    }
    adresaci[iloscAdresatow].id = iloscAdresatow+1;
    adresaci[iloscAdresatow].imie=imie;
    adresaci[iloscAdresatow].nazwisko=nazwisko;
    cout << "Podaj telefon:  " << endl;
    cin.sync();
    getline(cin, adresaci[iloscAdresatow].telefon);
    cout << "Podaj email:  " << endl;
    cin >> adresaci[iloscAdresatow].email;
    cout << "Podaj adres:  " << endl;
    cin.sync();
    getline(cin,adresaci[iloscAdresatow].adres);
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::app);
    if (plik.good() == true) {
        plik << adresaci[iloscAdresatow].id << endl;
        plik << adresaci[iloscAdresatow].imie << endl;
        plik << adresaci[iloscAdresatow].nazwisko << endl;
        plik << adresaci[iloscAdresatow].telefon << endl;
        plik << adresaci[iloscAdresatow].email << endl;
        plik << adresaci[iloscAdresatow].adres << endl;
        plik.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    iloscAdresatow++;
    if(iloscAdresatow>1)
    ustawAlfabetycznieOstatniego(adresaci,iloscAdresatow);
    cout << "Osoba zostala dodana." << endl;
    system("pause");
    return iloscAdresatow;
}

void wyszukajPoImieniu(Adresat adresaci[],int iloscAdresatow) {
    string imieSzukane, imieKolejne;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj imie osob, ktorych dane chcesz odszukac: " << endl;
    cin >> imieSzukane;
    imieSzukane[0]=toupper(imieSzukane[0]);
    system("cls");
    for( int indeksTablicy = 0; indeksTablicy < iloscAdresatow; indeksTablicy++) {
        imieKolejne = adresaci[indeksTablicy].imie;
        imieKolejne[0] = toupper(imieKolejne[0]);
        if(imieKolejne == imieSzukane) {
            cout << "Imie i nazwisko: " << adresaci[indeksTablicy].imie << " " << adresaci[indeksTablicy].nazwisko << endl;
            cout << "Telefon: "<<adresaci[indeksTablicy].telefon << endl;
            cout << "Email: " << adresaci[indeksTablicy].email << endl;
            cout << "Adres: " << adresaci[indeksTablicy].adres << endl;
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

void wyszukajPoNazwisku(Adresat adresaci[], int iloscAdresatow) {
    string nazwiskoSzukane,nazwiskoKolejne;
    int iloscOsobZnalezionych = 0;
    cout << "Podaj nazwisko osob, ktorych dane chcesz odszukac: " << endl;
    cin >> nazwiskoSzukane;
    nazwiskoSzukane[0] = toupper(nazwiskoSzukane[0]);
    system("cls");
    for (int indeksTablicy = 0; indeksTablicy < iloscAdresatow; indeksTablicy++) {
        nazwiskoKolejne = adresaci[indeksTablicy].nazwisko;
        nazwiskoKolejne[0] = toupper(nazwiskoKolejne[0]);
        if (nazwiskoKolejne == nazwiskoSzukane) {
            cout << "Imie i nazwisko: " << adresaci[indeksTablicy].imie << " " << adresaci[indeksTablicy].nazwisko << endl;
            cout << "Telefon: " << adresaci[indeksTablicy].telefon << endl;
            cout << "Email: " << adresaci[indeksTablicy].email << endl;
            cout << "Adres: " << adresaci[indeksTablicy].adres << endl;
            cout << " --- --- ---" << endl;
            iloscOsobZnalezionych++;
        }
    }
    if (iloscOsobZnalezionych == 0)
        cout << "W twojej ksiazce nie ma osob o nazwisku " << nazwiskoSzukane << " ." << endl;
    else
        cout << "W twojej ksiazce jest " << iloscOsobZnalezionych << " osob o nazwisku " << nazwiskoSzukane << "."<<endl;
    system("pause");
}


int main() {
    Adresat adresaci[1000];
    int iloscAdresatow;
    char wybor;
    iloscAdresatow = wczytanieKsiazkiAdresowjZPliku(adresaci);

    if (iloscAdresatow>1)
        sortujAlfabetycznie(adresaci,iloscAdresatow);

    while(1) {
        system("cls");
        cout << "1.Dodaj nowego adresata " << endl;
        cout << "2.Wyswietl wszystkich adresatow" << endl;
        cout << "3.Wyszukaj  adresatow o podanym imieniu" << endl;
        cout << "4.Wyszukaj adresatow o podanym nazwisku" << endl;
        cout << "9.Zakoncz program " << endl;
        cout << endl;
        cin >> wybor;
        switch(wybor) {
        case '1' :
            iloscAdresatow = wprowadzDaneAdresata(adresaci, iloscAdresatow);
            break;
        case '2' :
            wyswietlWszystkichAdresatow(adresaci, iloscAdresatow);
            break;
        case '3' :
            wyszukajPoImieniu(adresaci, iloscAdresatow);
            break;
        case '4' :
            wyszukajPoNazwisku(adresaci, iloscAdresatow);
            break;
        case '9' :
            exit(0);
        default:
            cout << "Nie ma takiej opcji w menu, podaj poprawna opcje po ukazaniu sie menu" << endl;
            system("pause");
        }
    }
    return 0;
}
