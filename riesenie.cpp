#include <iostream>
#include <map>
#include <vector>
#include <string>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;
#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class ZAKAZNIK { 
	string meno; 
	string priezvisko;
				
public:
	ZAKAZNIK();
	//nastavi clenske premenne meno a priezvisko na ""
	ZAKAZNIK(string priezvisko0, string meno0);
	ZAKAZNIK(ZAKAZNIK *zakaznik);
	string daj_meno();//vrati cele meno zakaznika
};

class VYSTROJ { 
	ZAKAZNIK *zakaznik;
	//2.uloha
	int typ; // 1 - lyze, 2 - lyziarky
	int opotrebovanost;
	int velkost;
	bool pozicane;
public:
	//1.uloha
	VYSTROJ(int typ, int velkost);
	~VYSTROJ();
	int daj_velkost() { return velkost; };
	int daj_typ() { return typ; };
	bool obsadenost() const { return pozicane; };
	bool pozicajZakaznikovi(string meno0, string priezvisko0);
	bool pozicajZakaznikovi(ZAKAZNIK *zakaznik);
	bool vratVystroj(int damage);
	string celeMenoZakaznika() const;
	//2.uloha
	void nastavOpotrebovanost(unsigned int pocet_percent);	
	bool su_pozicane() const { return pozicane; };
	int get_opotrebovanost();
};

//3.uloha
class POZICOVNA {
	unsigned int pocetLyzi;
	unsigned int pocetLyziarok;
	map<int, int> lyze0; //<velkost, mnozstvo>
	map<int, int> lyziarky0;
	vector<VYSTROJ> lyze;
	vector<VYSTROJ> lyziarky;
public:
	POZICOVNA(unsigned int pocetLyzi, unsigned int pocetLyziarok);
	int pocetLyziDanejVelkosti(int velkost);
	int pocetLyziarokDanejVelkosti(int velkost);
	void dokup_vystroj(VYSTROJ l); //prida lyze do map, zvacsi triednu premennu, prida lyzu do vektora
	void dokup_vystroj(int type, int size);
	//4.uloha
	bool pozicajZakaznikovi(string priezvisko0, string meno0, const int velkostLyzi, const int velkostLyziarok);
	int pocetVolnychLyzi() const;
	int pocetVolnychLyziarok() const;
	//5.uloha
	bool vratLyze(string priezvisko0, string meno0, int damage);
	bool vratLyziarky(string priezvisko0, string meno0, int damage);
	int kontrolaVystroje();
};
#endif

//1.uloha
ZAKAZNIK::ZAKAZNIK() {
	//Nastavte clenske premenne meno a priezvisko na ""
	meno = "";
	priezvisko = "";
}
ZAKAZNIK::ZAKAZNIK(string meno0, string priezvisko0) {
	//Ak je niektory zo vstupnych parametrov prazdny retazec
	//nastavte clenske premenne meno a priezvisko na "" a skoncite.
	//Inak do clenskych prememnnych ulozte vstupne parametre

	if (priezvisko0 == "" || meno0 == ""){
		meno = "";
		priezvisko = "";
		return;
	}
	meno = meno0;
	priezvisko = priezvisko0;
}
ZAKAZNIK::ZAKAZNIK(ZAKAZNIK *zakaznik) {
	//Ak je meno alebo priezvisko vstupneho parametra host rovne nule, alebo nie je definovane, 
	//nastavte clenske premenne meno a priezvisko na "" a skoncite.
	//Inak do clenskych prememnnych ulozte clenske prememnne zakaznika
	
	if (zakaznik == nullptr || zakaznik == NULL)
	{
		meno = "";
		priezvisko = "";
		return;
	}
	if (zakaznik->daj_meno() == "not defined")
	{
		meno = "";
		priezvisko = "";
		return;
	}
	meno = zakaznik->meno;
	priezvisko = zakaznik->priezvisko;
}
string ZAKAZNIK::daj_meno()  {
	//V pripade, ze meno a priezvisko su prazdne retazce, vratte "not defined".
	//Inak vratte cele meno v tvare "meno<medzera>priezvisko"
	
	if (meno != "" && priezvisko != "")
	{
		string celeMeno = meno + ' ' + priezvisko;
		return celeMeno;
	}
	return "not defined";
}
VYSTROJ::VYSTROJ(int type, int size) {
	//Nastavte clenske premenne velkost, typ
	//Ako defaultnu opotrebovanost vystroje nastavte 0, zakaznik na nullptr a premennu pozicane na false
	velkost = size;
	typ = type;

	pozicane = false;
	zakaznik = nullptr;
	opotrebovanost = 0;
}

VYSTROJ::~VYSTROJ() {
	//Ak zakaznik nie je nulovy, uvolnite jeho pamat
	if (zakaznik  != nullptr) {
		zakaznik = nullptr;
	}
}
bool VYSTROJ::pozicajZakaznikovi(string meno0, string priezvisko0) {
	//Ak vystroj nie je pozicana a zakaznik nema definovane prazdne priezvisko aj meno, 
	//vytvorte si dynamicky instanciu triedy ZAKAZNIK - ZAKAZNIK *osoba = new HOST(...);
	//a priradte ju clenskej premennej zakaznik.
	//Pozicane nastavte na true a vratte true.
	//Inak vratte false.
	if (pozicane == false && priezvisko0 != "" && meno0 != "" && opotrebovanost <= 90)
	{
		ZAKAZNIK *osoba = new ZAKAZNIK(meno0, priezvisko0);
		zakaznik = osoba;
		pozicane = true;
		return true;
	}
	return false;
}

bool VYSTROJ::pozicajZakaznikovi(ZAKAZNIK *osoba) {
	//Ak vystroj nie je pozicana a zakaznik nema definovane prazdne priezvisko aj meno,
	//vytvorte si dynamicky instanciu triedy ZAKAZNIK - ZAKAZNIK *osoba = new HOST(...);
	//a priradte ju clenskej premennej zakaznik.
	//Pozicane nastavte na true a vratte true.
	//Inak vratte false.

	if (pozicane == false && osoba->daj_meno() != "not defined" && opotrebovanost <= 90)
	{
		ZAKAZNIK *osoba2 = new ZAKAZNIK(osoba);
		zakaznik = osoba2;
		pozicane = true;
		return true;
	}
	return false;
}

string VYSTROJ::celeMenoZakaznika() const {
	//Vrati cele meno zakaznika v tvare meno<medzera>priezvisko. V pripade, ze to je nulovy smernik, 
	//vratte miesto toho "".
	if (zakaznik == nullptr) {
		return "";
	}
	return zakaznik->daj_meno();
}

bool VYSTROJ::vratVystroj(int damage) { 
	//Ak je vystroj pozicana, zruste zakaznika
	//nastavte pozicane na false, zvyste opotrebovanost podla damage a vratte true. Ak nie je 
	//pozicana, vratte false.
	if (pozicane == true) {
		delete zakaznik;
		zakaznik = nullptr;
		pozicane = false;
		nastavOpotrebovanost(opotrebovanost + damage);
		return true;
	}

	return false;
}
//2.uloha
int VYSTROJ::get_opotrebovanost() {
	//Vratte triednu premennu opotrebovanost
	return opotrebovanost;
}
void VYSTROJ::nastavOpotrebovanost(unsigned int pocet_percent) {
	//Nastavte triednu premennu opotrebovanost podla vstupneho parametra pocet_percent
	opotrebovanost = pocet_percent;
}

//3.uloha
POZICOVNA::POZICOVNA(unsigned int pocetlyzi, unsigned int pocetlyziarok) {
	//Nastavte si pocet lyzi a pocet lyziarok.
	//Do vektorov ulozte lyze a lyziarky, velkosti si nechajte vygenerovat nahodne
	//const int pom[7] = {120, 130, 140, 150, 160, 170, 180}; 
	//int RandIndex = rand() % 7; toto nahodne vygeneruje velkost lyzi z vyssie uvedeneho zoznamu
	//lyze[...] = new VYSTROJ(...);
	//do mapy lyze0 a lyziarky0 ulozte pocet kusov jednotlivych velkosti vystroje
	// velkost lyziarok generujte nahodne od velkosti 36 do 45

	pocetLyzi = pocetlyzi;
	pocetLyziarok = pocetlyziarok;
	const int pom[7] = {120, 130, 140, 150, 160, 170, 180};

	for (unsigned int i = 0; i < pocetLyzi; i++){
		int RandIndex = rand() % 7;
		//1 - lyza, 2 - lyziarka
		lyze.push_back(VYSTROJ(1, pom[RandIndex]));
		lyze0.insert(pair<int, int>(pom[RandIndex], 0));
	}

	for (unsigned int i = 0; i < pocetLyzi; i++) {
		lyze0[lyze[i].daj_velkost()]++;
	}

	for (unsigned int i = 0; i < pocetLyziarok; i++){
		int RandSize = rand() % 10 + 36; //random cislo z intervalu 36 az 45
		lyziarky.push_back(VYSTROJ(2, RandSize));
		lyziarky0.insert(pair<int, int>(RandSize, 0));
	}
	for (unsigned int i = 0; i < pocetLyziarok; i++) {
		lyziarky0[lyziarky[i].daj_velkost()]++;
	}

}


bool spravnaVelkostLyzi(int velkost) {
	switch (velkost)
	{
	case 120: return true;
	case 130: return true;
	case 140: return true;
	case 150: return true;
	case 160: return true;
	case 170: return true;
	case 180: return true;
	case 190: return true;
	default:
		return false;
	}
}
int POZICOVNA::pocetLyziDanejVelkosti(int size) {
	//vratte pocet kusov lyzi zadanej velkosti
	//v pripade zle zadanej velkosti vratte -1
	if (spravnaVelkostLyzi(size) == true) {
		return lyze0[size];
	}
	return -1;
	
}
int POZICOVNA::pocetLyziarokDanejVelkosti(int size) {
	//vratte pocet kusov lyziarok zadanej velkosti
	//v pripade zle zadanej velkosti vratte -1
	if (size >= 36 && size <= 45) {
		return lyziarky0[size];
	}
	return - 1;
}

void POZICOVNA::dokup_vystroj(VYSTROJ m) {
	//zvacsite pocetLyzi alebo pocetLyziarok o 1 (podla vstupneho parametra) 
	//do prislusneho vektora ulozte novu vystroj zo vstupu
	//nezabudnite zvacsit pocet kusov podla velkosti novej vystroje v prislusnej mape 

	if (m.daj_typ() == 1) {
		pocetLyzi++;
		lyze.push_back(m);
		lyze0[m.daj_velkost()]++;
	}
	else if (m.daj_typ() == 2) {
		pocetLyziarok++;
		lyziarky.push_back(m);
		lyziarky0[m.daj_velkost()]++;
	}
}

void POZICOVNA::dokup_vystroj(int type, int size) {
	//Vytvote si novu instanciu triedy VYSTROJ
	//zvacsite pocetLyzi alebo pocetLyziarok o 1 (podla vstupneho parametra) 
	//do prislusneho vektora ulozte novu vystroj zo vstupu
	//nezabudnite zvacsit pocet kusov podla velkosti novej vystroje v prislusnej mape 

	VYSTROJ v(type, size);
	dokup_vystroj(v);
}
//4.uloha
bool POZICOVNA::pozicajZakaznikovi(string meno0, string priezvisko0, const int size_lyze, const int size_lyziarky) {
	//ak su vstupne udaje zadane spravne, prejdite cyklom vsetky lyze a lyziarky a ak sedi velkost
	//a opotrebovanost vystroje je <= 90, pozicajte vystroj zakaznikovi
	//vratte true, ak sa podarila pozicat aspon jedna z vystroje
	//false vratte len v pripade, ak sa nepodarilo pozicat lyze ani lyziarky zaroven
	if (meno0 == ""  || priezvisko0 == "") {
		return false;
	}
	bool pozicanie_lyzi = false;
	bool pozicanie_lyziarok = false;
	if (spravnaVelkostLyzi(size_lyze)) {
		for (int i = 0; i < pocetLyzi; i++) {
			if (lyze[i].su_pozicane() == false && lyze[i].daj_velkost() == size_lyze && lyze[i].get_opotrebovanost() <= 90) {
				pozicanie_lyzi = lyze[i].pozicajZakaznikovi(meno0, priezvisko0);
				break;
			}
		}
	}
	if (size_lyziarky >= 36 && size_lyziarky <= 45) {
		for (int i = 0; i < pocetLyziarok; i++) {
			if (lyziarky[i].su_pozicane() == false && lyziarky[i].daj_velkost() == size_lyziarky && lyziarky[i].get_opotrebovanost() <= 90) {
				pozicanie_lyziarok = lyziarky[i].pozicajZakaznikovi(meno0, priezvisko0);
				if (pozicanie_lyzi == true) {
					return true;
				}
				return pozicanie_lyziarok;
			}
		}
	}
	return false;
}
int POZICOVNA::pocetVolnychLyzi() const {
	//vratte pocet nepozicanych lyzi
	int pocet = 0;
	for (int i = 0; i < pocetLyzi; i++) {
		if (lyze[i].su_pozicane() == false) {
			pocet++;
		}
	}
	return pocet;
}
int POZICOVNA::pocetVolnychLyziarok() const {
	//vratte pocet nepozicanych lyziarok
	int pocet = 0;
	for (int i = 0; i < pocetLyziarok; i++) {
		if (lyziarky[i].su_pozicane() == false) {
			pocet++;
		}
	}
	return pocet;
}
//5.uloha
bool POZICOVNA::vratLyze(string meno0, string priezvisko0, int damage) {
	//V cykle prejdite cez vsetky lyze. Ak najdete zhodu 
	//so vstupnym menom a priezviskom, "vratte" jeho vystroj a vratte, ci sa to podarilo.
	//Ak nie je, vratte false.
	string celeMeno = meno0 + ' ' + priezvisko0;
	
	for (unsigned int i = 0; i < pocetLyzi; i++){
		
		if (lyze[i].celeMenoZakaznika() == celeMeno) {
			
			return lyze[i].vratVystroj(damage);
		}
	}
	return false;
}

bool POZICOVNA::vratLyziarky(string meno0, string priezvisko0, int damage) {
	//V cykle prejdite cez vsetky lyziarky. Ak najdete zhodu 
	//s vstupnym menom a priezviskom, "vratte" jeho vystroj a vratte, ci sa to podarilo.
	//Ak nie je, vratte false.
	string celeMeno = meno0 + ' ' + priezvisko0;
	for (unsigned int i = 0; i < pocetLyziarok; i++) {
		
		if (lyziarky[i].celeMenoZakaznika() == celeMeno) {
			
			return lyziarky[i].vratVystroj(damage);
		}
	}
	return false;
}
int POZICOVNA::kontrolaVystroje() {
	//V cykloch prejdite cez vsetky lyze a lyziarky. Ak najdete vystroj, ktorej opotrebovanost je vacsia ako 90
	//nahradite ju novou, ale velkost ponechate
	//Zaroven spocitate pocet vymenenych kusov vystroje a vratite ho
	//Ak ziadnu vystroj nevymenite za novu, vratite 0
	int pocet = 0;
	for (unsigned int i = 0; i < pocetLyzi; i++)
	{
		if (lyze[i].get_opotrebovanost() > 90) {
			int velkost = lyze[i].daj_velkost();
			lyze[i] = VYSTROJ(1, velkost);
			pocet++;
		}
	}

	for (unsigned int i = 0; i < pocetLyziarok; i++) {
		if (lyziarky[i].get_opotrebovanost() > 90) {
			int velkost = lyziarky[i].daj_velkost();
			lyziarky[i] = VYSTROJ(2, velkost);
			pocet++;
		}
	}
	return pocet;
	
}

