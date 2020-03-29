/*
    K.Szytko 29.03.2020

    Generowanie klucza polega na stworzeniu wektora kolejnych 95 znaków
    drukowanych (w tym spacji) z pomocą funkcji iota, przemieszanie go
    funkcją shuffle i zwrócenie w postacji stringa.

    Wektor iota:    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMN
                    OPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

    Przykładowy     "QE*5mh{,Vp!tw\\qxLZ6e$Yoj@\"X}d4^AbSIskv/O7%>yfP
    wektor shuffle: unCTc8?#N=l<H)g(.`:;~93DiB1WJ|KF+]rR &[_G20zU'M-a"

    Szyfrowanie znaku polega na wyliczeniu jego pozycji i odczytaniu znaku z klucza.
    Odszyfrowanie jest zadaniem odwrotnym i po znalezieniu znaku w kluczu odczytywana jest
    jego pozycja, na podstawie której wyliczany jest znak ASCII.

    Znaki specjalne m.in. znak nowej lini nie są modyfikowane.
*/


#include <string> 
#include <iostream> 
#include <cassert>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

const short ASCII_BEGIN = 32; //Include (Space)
const short ASCII_END = 127;  //Exclude (DEL)

std::string generateKey() {
    std::vector<char> vKey(ASCII_END - ASCII_BEGIN);
    std::iota(vKey.begin(), vKey.end(), ASCII_BEGIN);
    std::shuffle(vKey.begin(), vKey.end(), std::mt19937{ std::random_device{}() });
    return std::string{ vKey.begin(), vKey.end() };
}

std::string encrypt(std::string m, std::string key) {
    std::transform(m.begin(), m.end(), m.begin(), 
        [&key](char c) {
            return (c >= ASCII_BEGIN && c < ASCII_END) ? key[c - ASCII_BEGIN] : c; });
    return m;
}

std::string decrypt(std::string m, std::string key) {
    std::transform(m.begin(), m.end(), m.begin(),
        [&key](char c) {
            return (c >= ASCII_BEGIN && c < ASCII_END) ? key.find(c) + ASCII_BEGIN : c; });
    return m;
}

int main() {
    std::string message = "Hello,\tCoders School!";

    auto key = generateKey();
    auto cypher = encrypt(message, key);
    auto result = decrypt(cypher, key);

    std::cout << "Message: " << message << '\n';
    std::cout << "Cypher : " << cypher << '\n';
    std::cout << "Result : " << result << '\n';

    assert(message == result);
    return 0;
}