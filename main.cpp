#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);
bool pIsValid(int, int&, int&);
int computePhi(int, int);
int findD(int, int);

int main(){
    int e;
    int n;
    int m; // Number characters in the message
    int p;
    int q;
    int phi; // phi(n)
    int d;

    cin >> e >> n;
    cin >> m;

    int* cyphertext = new int[m];

    for(int i = 0; i < m; i++){
        cin >> cyphertext[i];
    }

    //cout << isPrime(5);

    if(!pIsValid(n, p, q))
        cout << "Public key is not valid!";
    else{
        phi = computePhi(p, q);
        d = findD(e, phi);
    }
    
    cout << d;
    //cout << p << "-" << q;

    return 0;
}

bool isPrime(int n){
    if(n < 2) return false;
    if(n == 2) return true;

    double val = static_cast<double>(n);   

    for(int i = 2; i <= static_cast<int>(floor(sqrt(val))); i++){
        if(n % i == 0) return false;
    }

    return true;
}

bool pIsValid(int n, int& p, int& q){
    bool pFound = false;
    if(isPrime(n)) return false;
    for(int i = 2; i <= n/2; i++){
        if(n % i == 0 && isPrime(i) && !pFound){
            p = i;
            pFound = true;
            continue;
        }
        if(n % i == 0 && isPrime(i)){
            q = i;
            break;
        }
    }
    return true;
}

int computePhi(int p, int q){
    return (p-1)*(q-1);
}

int findD(int e, int phi){
    bool dIsFound = false;
    int d;
    int i = 1;
    while(!dIsFound){
        i += phi;
        if(i % e == 0){
            dIsFound = true;
            d = i/e;
        }
    }
    return d;
}
