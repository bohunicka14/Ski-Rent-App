#if !defined( _TESTER_H_ )
#define _TESTER_H_

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

bool testTrue(bool vysledok, const string nazovTestu);
bool testFalse(bool vysledok, string nazovTestu);
bool testEqual(int i1, int i2, const string nazovTestu);
bool testNonEqual(int i1, int i2, const string nazovTestu);
bool testEqual(double d1, double d2, const string nazovTestu);
bool testNonEqual(double d1, double d2, const string nazovTestu);
bool testEqual(const string s1, const string s2, const string nazovTestu);
bool testNonEqual(const string s1, const string s2, const string nazovTestu);

void nastavSledovanieSkupiny(const string nazov);
void zhodnotenieVysledkov();
void zhodnotenieTestov();

#endif
