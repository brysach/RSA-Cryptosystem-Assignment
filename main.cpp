#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);
bool pIsValid(int, int&, int&);

int main(){
    int e;
    int n;
    int m; // Number characters in the message
    int p;
    int q;

    cin >> e >> n;
    cin >> m;

    int* cyphertext = new int[m];

    for(int i = 0; i < m; i++){
        cin >> cyphertext[i];
    }

    //cout << isPrime(5);

    if(!pIsValid(n, p, q))
        cout << "Public key is not valid!";
    
    cout << p << "-" << q;

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
