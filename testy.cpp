#include <iostream>

#include "testTool.h"
#include "riesenie.h"

using namespace std;

void testyVystroje() {
  nastavSledovanieSkupiny("Testy vystroje");

  ZAKAZNIK host("Jozef","Mak");
  testEqual("Jozef Mak", host.daj_meno(), "Meno zakaznika");
	ZAKAZNIK host1("","Vinco");
  testEqual("not defined", host1.daj_meno(), "Meno zakaznika");
	ZAKAZNIK host2("Vinco", "");
	testEqual("not defined", host2.daj_meno(), "Meno zakaznika");
	ZAKAZNIK host3("Nic", "");
	testEqual("not defined", host3.daj_meno(), "Meno zakaznika");
	ZAKAZNIK *host4;
	{
		ZAKAZNIK host5("Holden", "Caulfield ");
		testEqual("Holden Caulfield ", host5.daj_meno(), "Meno zakaznika");
		host4 = new ZAKAZNIK(&host5);
	}
	testEqual("Holden Caulfield ", host4->daj_meno(), "Meno zakaznika");
	ZAKAZNIK host6(&host);
	testEqual("Jozef Mak", host6.daj_meno(), "Meno zakaznika");
	ZAKAZNIK host7(&host3);
	testEqual("not defined", host7.daj_meno(), "Meno zakaznika");
	VYSTROJ alpine(1, 180);
	testFalse(alpine.obsadenost(), "Obsadenost");
  testFalse(alpine.vratVystroj(35), "Obsadenost");
  testEqual("", alpine.celeMenoZakaznika(), "Meno zakaznika");
  testTrue(alpine.pozicajZakaznikovi("Paul", "Baumer"), "Pozicanie");
	testFalse(alpine.pozicajZakaznikovi(&host3), "Pozicanie");
  testTrue(alpine.obsadenost(), "Test obsadenosti");
  testEqual("Paul Baumer", alpine.celeMenoZakaznika(), "Meno zakaznika");
	testTrue(alpine.vratVystroj(15), "Vratenie vystroje");
  testFalse(alpine.vratVystroj(12), "Vratenie vystroje");
  testEqual("", alpine.celeMenoZakaznika(), "Meno zakaznika");
  testFalse(alpine.obsadenost(), "Obsadenost");
	VYSTROJ alpine1(2, 39);
	testTrue(alpine1.pozicajZakaznikovi(&host), "Pozicanie");
	testEqual("Jozef Mak", alpine1.celeMenoZakaznika(), "Meno zakaznika");

	zhodnotenieVysledkov();
}
void testyOpotrebenia() {
  nastavSledovanieSkupiny("Testy opotrebenia");

  VYSTROJ lyze1(1, 150);
  testEqual(1, lyze1.daj_typ(), "Typ vystroje");
  testEqual(lyze1.get_opotrebovanost(), 0,"Opotrebovanost lyzi");
  testTrue(lyze1.pozicajZakaznikovi("Jozef", "Mak"), "Pozicanie");
  testTrue(lyze1.vratVystroj(95), "Vratenie");
  testEqual(lyze1.get_opotrebovanost() , 95, "Opotrebovanost");
  testEqual("", lyze1.celeMenoZakaznika(), "Meno zakaznika");
  testFalse(lyze1.pozicajZakaznikovi("Paul", "Baumer"), "Pozicanie");
  lyze1.nastavOpotrebovanost(50);
	testEqual(lyze1.get_opotrebovanost(), 50, "Oprava lyzi");
	testTrue(lyze1.pozicajZakaznikovi("Paul", "Baumer"), "Pozicanie");
  testEqual("Paul Baumer", lyze1.celeMenoZakaznika(), "Meno zakaznika");
  testTrue(lyze1.vratVystroj(19), "Vratenie");
  testEqual(lyze1.get_opotrebovanost(), 69 ,"Opotrebovanost");
  VYSTROJ lyziarky1(2, 40);
  lyziarky1.nastavOpotrebovanost(30);
	testTrue(lyziarky1.pozicajZakaznikovi("Holden", "Caulfield"), "Pozicanie");
  testEqual("Holden Caulfield", lyziarky1.celeMenoZakaznika(), "Meno zakaznika");
  testEqual(lyziarky1.get_opotrebovanost(), 30, "Opotrebovanost");
  testTrue(lyziarky1.vratVystroj(30), "Vratenie lyziarok");
  testEqual(lyziarky1.get_opotrebovanost(), 60, "Opotrebovanost");
  testEqual(2, lyziarky1.daj_typ(), "Typ vystroje");
  testEqual(1, lyze1.daj_typ(), "Typ vystroje");
	{
		ZAKAZNIK novyHost("Anna", "Karenina");
		testTrue(lyziarky1.pozicajZakaznikovi(&novyHost), "Pozicanie");
	}
	testEqual("Anna Karenina", lyziarky1.celeMenoZakaznika(), "Meno zakaznika");

  zhodnotenieVysledkov();
}
void testyPozicovne() {
  nastavSledovanieSkupiny("Testy otvorenia pozicovne ");

  POZICOVNA p(3, 3);
  testEqual(p.pocetVolnychLyzi(), 3, "Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 3, "Volne lyziarky");
  testEqual(p.pocetLyziDanejVelkosti(50), -1,"Zla velkost");
  testEqual(p.pocetLyziarokDanejVelkosti(3), -1,"ZLa velkost");
  p.dokup_vystroj(1, 160);
  testEqual(p.pocetVolnychLyzi(), 4,"Volne lyze");
  p.dokup_vystroj(2, 38);
  testEqual(p.pocetVolnychLyziarok(), 4,"Volne lyziarky");

  POZICOVNA p1(2, 0);
  testEqual(p1.pocetVolnychLyzi(), 2,"Volne lyze");
  testEqual(p1.pocetVolnychLyziarok(), 0,"Volne lyziarky");
  testEqual(p.pocetVolnychLyzi(), 4,"Volne lyze");
  POZICOVNA p3(0, 0);
  p3.dokup_vystroj(1, 170);
  p3.dokup_vystroj(2, 38);
  testEqual(p3.pocetLyziarokDanejVelkosti(38), 1,"Pocet lyziarok velkosti 38");
  testEqual(p3.pocetLyziDanejVelkosti(170), 1, "Pocet lyzi velkosti 170");
  p3.dokup_vystroj(1, 170);
  p3.dokup_vystroj(2, 38);
  testEqual(p3.pocetLyziarokDanejVelkosti(38), 2, "Pocet lyziarok velkosti 38");
  testEqual(p3.pocetVolnychLyziarok(), 2, "Pocet lyziarok volnych");

	zhodnotenieVysledkov();
}
void testyPoziciavania() {
  nastavSledovanieSkupiny("Testy poziciavania z pozicovne");

 POZICOVNA p(4, 4);
	//testEqual(hotel.zoznamHosti(nullptr), "", "Mena hosti");
	testEqual(p.pocetVolnychLyzi(), 4, "Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 4,"Volne lyziarky");
	testFalse(p.pozicajZakaznikovi("Seymour", "Glass", 0, 0), "Pozicanie");
	p.dokup_vystroj(1, 180);
	p.dokup_vystroj(2, 42);
	testTrue(p.pozicajZakaznikovi("Seymour", "Glass", 180, 42), "Pozicanie");
	testEqual(p.pocetVolnychLyzi(), 4, "Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 4,"Volne lyziarky");
  p.dokup_vystroj(1, 160);
  p.dokup_vystroj(2, 37);
  testEqual(p.pocetVolnychLyzi(), 5, "Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 5, "Volne lyziarky");
	testTrue(p.pozicajZakaznikovi("Anna", "Steel", 160, 37), "Pozicanie");
	testFalse(p.pozicajZakaznikovi("", "", 170, 39), "Pozicanie");
	p.dokup_vystroj(1, 160);
	p.dokup_vystroj(2, 37);
  testEqual(p.pocetVolnychLyzi(), 5,"Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 5,"Volne lyziarky");
	testFalse(p.pozicajZakaznikovi("Anastasia", "Steel", 159, 34), "Pozicanie");
	
  zhodnotenieVysledkov();
}
void testyVratenia() {
  nastavSledovanieSkupiny("Testy vratenia vystroje");

  POZICOVNA p(3, 3);
  p.dokup_vystroj(1, 190);
  p.dokup_vystroj(2, 45);
	testTrue(p.pozicajZakaznikovi("Matt", "Bomer", 190, 45), "Pozicanie");
	p.dokup_vystroj(1, 180);
	p.dokup_vystroj(2, 44);
	testTrue(p.pozicajZakaznikovi("Mark", "Cavendish", 180, 44),"Pozicanie");
	p.dokup_vystroj(1, 170);
	p.dokup_vystroj(2, 43);
	testTrue(p.pozicajZakaznikovi("Simon", "Richardson", 170, 43), "Pozicanie");
	p.dokup_vystroj(1, 160);
	p.dokup_vystroj(2, 42);
	testTrue(p.pozicajZakaznikovi("Matt", "Stepphens", 160, 42), "Pozicanie");
	testFalse(p.pozicajZakaznikovi("Pravda", "Pravdova", 100, 45), "Pozicanie");
  testEqual(p.pocetVolnychLyzi(), 3,"Volne lyze");
  testEqual(p.pocetVolnychLyziarok(), 3, "Volne lyziarky");
	testTrue(p.vratLyze("Matt", "Stepphens", 2), "Vratenie lyzi");
  testEqual(p.pocetVolnychLyzi(), 4, "Volne lyze");
  testTrue(p.vratLyziarky("Simon", "Richardson", 2), "Vratenie lyziarok");
  testEqual(p.pocetVolnychLyziarok(), 4, "Volne lyziarky");
  testTrue(p.vratLyziarky("Matt", "Stepphens", 2), "Vratenie lyziarok");
  testEqual(p.pocetVolnychLyziarok(), 5, "Volne lyziarky");
	testTrue(p.vratLyziarky("Mark", "Cavendish", 95), "Vratenie lyziarok");
  testEqual(p.pocetVolnychLyziarok(), 6, "Volne lyziarky");

	testEqual(p.kontrolaVystroje(), 1, "Kontrola vystroje");
	

  zhodnotenieVysledkov();
}
