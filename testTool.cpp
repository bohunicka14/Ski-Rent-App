#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Globalne premenne

const unsigned int MAX_POCET_SKUPIN_TESTOV = 6;
unsigned int pocetSkupin = 0;
unsigned int aktualnaSkupina = 0;
string nazvySkupin[MAX_POCET_SKUPIN_TESTOV];
unsigned int pocetTestovSkupiny[MAX_POCET_SKUPIN_TESTOV];
unsigned int pocetZlyhanychTestovSkupiny[MAX_POCET_SKUPIN_TESTOV];

void pridajZbehnutyTest(bool vysledok) {
  pocetTestovSkupiny[aktualnaSkupina] += 1;
  if (vysledok == false) {
    pocetZlyhanychTestovSkupiny[aktualnaSkupina] += 1;
  }
}
int getPocetTestov() {
  return pocetTestovSkupiny[aktualnaSkupina];
}
string vysledokTestu(bool vysledok) {
  return vysledok ? " - OK" : " - FALSE";
}
string getNazovSkupiny() {
  return nazvySkupin[aktualnaSkupina];
}
int getPocetZlyhanychTestov() {
  return pocetZlyhanychTestovSkupiny[aktualnaSkupina];
}
void nastavSledovanieSkupiny(const string nazov) {
  if (pocetSkupin < MAX_POCET_SKUPIN_TESTOV) {
    pocetSkupin += 1;
  }
  aktualnaSkupina = pocetSkupin - 1;
  nazvySkupin[aktualnaSkupina] = nazov;
  pocetTestovSkupiny[aktualnaSkupina] = 0;
  pocetZlyhanychTestovSkupiny[aktualnaSkupina] = 0;
  cout << endl << "<----------" << getNazovSkupiny() << "---------->" << endl;
}
void zhodnotenieVysledkov() {
  cout << "<--- " << getNazovSkupiny();
  cout << " (" << getPocetTestov() << ":" << getPocetZlyhanychTestov() << ")";
  bool vysledok = (getPocetZlyhanychTestov() == 0) ? true : false;
  cout << vysledokTestu(vysledok) << endl << endl;
}
bool testTrue(bool vysledok, const string nazovTestu) {
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testFalse(bool vysledok, string nazovTestu) {
  return testTrue(!vysledok, nazovTestu);
}
bool testEqual(int i1, int i2, const string nazovTestu) {
  bool vysledok = (i1 == i2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << i1 << "'=='" << i2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(int i1, int i2, const string nazovTestu) {
  bool vysledok = (i1 != i2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << i1 << "'!='" << i2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testEqual(double d1, double d2, const string nazovTestu) {
  bool vysledok = (d1 == d2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << d1 << "'=='" << d2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(double d1, double d2, const string nazovTestu) {
  bool vysledok = (d1 != d2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << d1 << "'!='" << d2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testEqual(const string s1, const string s2, const string nazovTestu) {
  bool vysledok = (s1 == s2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << s1 << "'=='" << s2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
bool testNonEqual(const string s1, const string s2, const string nazovTestu) {
  bool vysledok = (s1 != s2);
  pridajZbehnutyTest(vysledok);
  cout << getPocetTestov() << ". " << nazovTestu << ":'" << s1 << "'!='" << s2 << "'";
  cout << vysledokTestu(vysledok) << endl;
  return vysledok;
}
int pocetSkupinTestov() {
  return pocetSkupin;
}
string getNazovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return nazvySkupin[cislo];
  }
  return "";
}
int pocetTestovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return pocetTestovSkupiny[cislo];
  }
  return 0;
}
int pocetNesplnenychTestovDanejSkupiny(unsigned int cislo) {
  if (cislo < pocetSkupin) {
    return pocetZlyhanychTestovSkupiny[cislo];
  }
  return 0;
}
void zhodnotenieTestov() {
  unsigned int pocetVsetkychTestov = 0;
  unsigned int pocetVsetkychNesplnenychTestov = 0;
  cout << "<----------- Zaverecne zhodnotenie ---------->" << endl;
  for (unsigned int i = 0; i < pocetSkupin; i++) {
    cout << "       " << i + 1 << ": " << nazvySkupin[i];
    cout << " (" << pocetTestovDanejSkupiny(i) << ":" << pocetNesplnenychTestovDanejSkupiny(i) << ")";
    cout << endl;
    pocetVsetkychTestov += pocetTestovDanejSkupiny(i);
    pocetVsetkychNesplnenychTestov += pocetNesplnenychTestovDanejSkupiny(i);
  }
  cout << endl << "       Celkovy vysledok";
  cout << " (" << pocetVsetkychTestov << ":" << pocetVsetkychNesplnenychTestov << ")";
  bool vysledok = (pocetVsetkychNesplnenychTestov == 0) ? true : false;
  cout << vysledokTestu(vysledok) << endl << endl;
}


