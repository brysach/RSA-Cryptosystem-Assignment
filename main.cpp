#include <iostream>
#include <cmath>
#include <map>
using namespace std;

bool isPrime(int);
bool keyIsValid(int, int, int&, int&);
int computePhi(int, int);
int findD(int, int);
int* decypher(const int*, int, int, int);
void printDText(const int*, int);
void printMessage(map<int, char>, const int*, int);
int gcd(int, int);

int main(){
    int e;
    int n;
    int m; // Number characters in the message
    int p;
    int q;
    int phi; // phi(n)
    int d;
    bool eIsInverse = true;
    map<int, char> BobMap;

    cin >> e >> n;
    cin >> m;

    int* cyphertext = new int[m];
    int* dText = new int[m];

    for(int i = 0; i < m; i++){
        cin >> cyphertext[i];
    }

    // Assign integers to characters
    char letter = 65;
    
    for(int i = 5; i <= 30; i++){
        BobMap.insert({i, letter});
        letter++;
    }
    BobMap.insert({31, ' '});
    BobMap.insert({32, '"'});
    BobMap.insert({33, ','});
    BobMap.insert({34, '.'});
    BobMap.insert({35, '\''});

    //cout << "this is A: " << BobMap[5] << endl;

    //cout << isPrime(5);

    if(!keyIsValid(n, e, p, q))
        cout << "Public key is not valid!" << endl;
    else{
        phi = computePhi(p, q);
        eIsInverse = gcd(e, phi) == 1 ? 1 : 0;
        
        if(eIsInverse){
            d = findD(e, phi);
            delete [] dText;
            dText = decypher(cyphertext, n, d, m);
            cout << p << " " << q << " " << phi << " " << d << endl;
            printDText(dText, m);
            printMessage(BobMap, dText, m);
        } else{
            cout << "Public key is not valid!" << endl;
        }
    }
    
    //cout << p << "-" << q;
    delete [] dText;
    delete [] cyphertext;
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

bool keyIsValid(int n, int e, int& p, int& q){
    //bool pFound = false;
    //bool qFound = false;
    bool isValid = false;
    if(isPrime(n) || n < 0) return false;
    if(e < 1) return false;
    for(int i = 2; i <= n/2; i++){
        if(n % i == 0 && isPrime(i) && !isValid){
            int j = n/i;
            if( j != i && isPrime(j) && n % j == 0){
                p = i;
                q = j;
                isValid = true;
            }

            //p = i;
            //pFound = true;
            //continue;
        }
        // if(n % i == 0 && isPrime(i) && !qFound){
        //     q = i;
        //     qFound = true;
        //     break;
        // }
    }
    // if(!pFound || !qFound){
    //     return false;
    // }

    if(isValid) return true;
    else return false;
    //return true;
}

int computePhi(int p, int q){
    return (p-1)*(q-1);
}

int findD(int e, int phi){
    bool dIsFound = false;
    int d;
    long long i = 1;
    while(!dIsFound){
        i += phi;
        if(i % e == 0){
            dIsFound = true;
            d = i/e;
        }
    }
    return d;
}

int* decypher(const int* cypher, int n, int d, int size){
    int* text = new int[size];

    for(int i = 0; i < size; i++){
        long long M = 1LL; 
        long long dTemp = (long long)d;
        long long C = (long long)cypher[i];        
        // Compute M = C^d (mod n)
        while(dTemp >= 1){
            if(dTemp % 2LL == 1){
                M = (M * C) % n;
                dTemp--;
            } else{
                C = (C * C) % n;
                dTemp /= 2LL;
                if(C == 1){
                    break;
                }
            }
        }
        text[i] = M;
    }

    return text;
}

void printDText(const int* text, int size){
    for(int i = 0; i < size; i++){
        cout << text[i] << " ";
    }
    cout << endl;
}

void printMessage(map<int, char>m, const int* dText, int size){
    for(int i = 0; i < size; i++){
        cout << m[dText[i]];
    }
    cout << endl;
}

int gcd(int a, int b){
        if(a == b){
        return a;
    }
    
    int temp;
    if(a < b ){
        temp = b;
        b = a;
        a = temp;
    }
    return gcd(a - b, b);
}