#include <map>
#include <vector>
#include <iostream>
#include <string>
#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
class ZAKAZNIK { //host
	string meno; //smernik na retazec, obsahujuci 
	string priezvisko;
public:
	ZAKAZNIK();
	//nastavi clenske premenne meno a priezvisko na nullptr
	ZAKAZNIK(string priezvisko0, string meno0);
	ZAKAZNIK(ZAKAZNIK *zakaznik);
	string daj_meno();//vrati cele meno zakaznika
};

class VYSTROJ {
	ZAKAZNIK *zakaznik;
	//2.uloha
	int typ;
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
						 //map<int, int>::iterator iter_lyze = lyze0.begin();
	map<int, int> lyziarky0;
	vector<VYSTROJ> lyze;
	vector<VYSTROJ> lyziarky;
public:
	POZICOVNA(unsigned int pocetLyzi, unsigned int pocetLyziarok);
	int pocetLyziDanejVelkosti(int velkost);
	int pocetLyziarokDanejVelkosti(int velkost);
	void dokup_vystroj(VYSTROJ l); //prida lyze do map, zvacsi triednu premennu, prida lyzu do pola
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
