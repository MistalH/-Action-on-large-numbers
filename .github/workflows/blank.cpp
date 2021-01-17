#include <iostream>
#include <string>

using namespace std;

// Funkcja na dodawanie
string Dodawanie(string var1, string var2) {
    string integer1, integer2;
    if (var1.length() < var2.length()) {
        integer1 = var2;
        integer2 = var1;
    }
    else {
        integer1 = var1;
        integer2 = var2;
    }

    int integer1Lenght = integer1.length();
    int integer2Lenght = integer2.length();

    reverse(integer1.begin(), integer1.end());
    reverse(integer2.begin(), integer2.end());
    string away = "";
    int flow = 0;

    for (int i = 0; i < integer2Lenght; i++) {
        int a = (integer1[i] - '0') + (integer2[i] - '0') + flow;
        away.push_back('0' + a % 10);
        flow = a / 10;
    }

    for (int i = integer2Lenght; i < integer1Lenght; i++) {
        int a = (integer1[i] - '0') + flow;
        away.push_back('0' + a % 10);
        flow = a / 10;
    }
    if (flow) {
        away.push_back('0' + flow);
    }
    // odwrracam 
    reverse(away.begin(), away.end());

    return away;
}
// Odejmowanie
string Odejmowanie(string var1, string var2) {
    string integer1, integer2;
    char Znak;

    //WAŻNE Usuniecie zera z poczatkow liczb !!!!! 
    if (var1[0] == '0') {
        for (unsigned int i = 0; i < var1.length() + 1; i++) {
            if (var1[i] != '0') {
                var1.erase(0, i);
                break;
            }
        }
    }
    // zamiana zmiennych miejscami tak aby większa liczba była przypisana jako
    // integer1
    if (var1.length() < var2.length()) {
        integer1 = var2;
        integer2 = var1;
        Znak = 45; 
        //Znak ="-"
    }
    else if (var1.length() == var2.length() && var1 < var2) {
        integer1 = var2;
        integer2 = var1;
        Znak = 45;
        //Znak ="-"
    }
    else {
        integer1 = var1;
        integer2 = var2;
        Znak = '\0';
    }
    int integer1Lenght = integer1.length();
    int integer2Lenght = integer2.length();
    // Znów obracam 
    reverse(integer1.begin(), integer1.end());
    reverse(integer2.begin(), integer2.end());

    string away = "";
    
    int flow = 0;
    for (int i = 0; i < integer2Lenght; i++) {
        int a = (integer1[i] - '0') - flow - (integer2[i] - '0');
        if (a < 0) {
            a = a + 10;
            flow = 1;
        }
        else {
            flow = 0;
        }
        away.push_back('0' + a % 10);
    }
    for (int i = integer2Lenght; i < integer1Lenght; i++) {
        int a = (integer1[i] - '0') - flow;
        if (a < 0) {
            a = a + 10;
            flow = 1;
        }
        else {
            flow = 0;
        }
        away.push_back('0' + a % 10);
    }

    int Awaylenght = away.length();

    reverse(away.begin(), away.end());

    //WAŻNE Usuniecie zera z poczatkow liczb !!!!! 
    if (away[0] == '0') {
        for (int i = 0; i < Awaylenght; i++) {
            if (away[i] != '0') {
                away.erase(0, i);
                break;
            }
        }
    }
    
    if (Znak) {
        away = Znak + away;
    }
    return away;
}

string Mnozenie(string var1, string var2) {
    string integer1, integer2;
    // zamiana zmiennych tak, aby większa była jako number1,
    if (var1.length() < var2.length()) {
        integer1 = var1;
        integer2 = var2;
    }
    else {
        integer1 = var2;
        integer2 = var1;
    }
    int integer1Lenght = integer1.length();
    int integer2Lenght = integer2.length();
    reverse(integer1.begin(), integer1.end());
    reverse(integer2.begin(), integer2.end());

    string away = "";
    string local = "";
    int zeros = 0;
    for (int i = 0; i < integer1Lenght; i++) {
        away = "";
        int zero = 0;
        // przebieg petli
        int integre = 0;
        // wykona siue tyle razy  ile wieksza liczba ma cyfr!!!
        for (int k = 0; k < zeros; k++) {
            away.push_back('0' + 0);
        }

        for (int j = 0; j < integer2Lenght; j++) {
            int var = ((integer1[i] - '0') * (integer2[j] - '0'));

            int zmn1 = var % 10 + zero + integre;
            if (var >= 10) {
                integre = 1;
                var = var - 10;
            }
            else {
                integre = 0;
            }

            away.push_back('0' + var);

            zero = var / 10;
        }
        if (zero) {
            away.push_back('0' + zero);
        }
        if (integre) {
            away.push_back('0' + integre);
        }

        zeros++;
        reverse(away.begin(), away.end());
        local = Dodawanie(local, away);
    }

    return local;
}
// DZielenie dla 
string dzielenie(string var1, string var2, string& reszta) {
    string integer1 = var1;
    // wynik
    string zero = "";
    // zastapienie ZNAK
    while (integer1[0] != '-') {
        integer1 = Odejmowanie(integer1, var2);
        if (integer1 == var1) {
            return "NaN";
        }
        if (integer1[0] != '-') {
            reszta = integer1;
        }
        else {
            break;
        }
        zero = Dodawanie(zero, "1");
    }
    //zwrócenie wyniku
    return zero;
}
// Głowne dzielenie
string dzielenie2(string var1, string var2) {
    string wynik = "";
    string temp_wynik = "";
    string reszta = "";
    for (unsigned int i = 0; i < var1.length(); i++) {
        reszta.append(var1.substr(i, 1));
        temp_wynik = dzielenie(reszta, var2, reszta);
        if (temp_wynik == "") {
            temp_wynik = "0";
        }
        if (temp_wynik == "NaN") {
            return "NaN";
        }
        wynik.append(temp_wynik);
    }

    // Usuwanie zer na początku
    if (wynik[0] == '0') {
        for (unsigned int i = 0; i < wynik.length(); i++) {
            if (wynik[i] != '0') {
                wynik.erase(0, i);
                break;
            }
        }
    }
    return wynik;
}
int main() {
    int data = 0; //Zainicjowanie zmiennej ile razy ma się wykonać pętla
    string  var1;
    string var2;
    string add;
    cin >> data;
    for (int i = 0; i < data; i++) {
        cin >> add;
        if (add.find("+") != string::npos) {
            var2 = string(add, add.find("+") + 1);
            var1 = string(add, 0, add.find("+"));
            cout << Dodawanie(var1, var2) << "\n";
        }
        else if (add.find("-") != string::npos) {
            var2 = string(add, add.find("-") + 1);
            var1 = string(add, 0, add.find("-"));
            cout << Odejmowanie(var1, var2) << "\n";
        }
        else if (add.find("*") != string::npos) {
            var2 = string(add, add.find("*") + 1);
            var1 = string(add, 0, add.find("*"));
            cout << Mnozenie(var1, var2) << "\n";
        }
        else if (add.find("/") != string::npos) {
            var2 = string(add, add.find("/") + 1);
            var1 = string(add, 0, add.find("/"));
            cout << dzielenie2(var1, var2) << "\n";
        }
    }
}
