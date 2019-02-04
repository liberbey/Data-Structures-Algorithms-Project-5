#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <cmath>

using namespace std;

const long long int MOD = 1e9+7;
vector<string> dictWord;
vector<long long int> dict;
vector<long long int> myWord;
vector<long long int> func;
string word;

long long int hashit(string s, long long int n){

    long long int result = 0;
    for(int i = 0; i < s.length(); i++){

        long long int a = s[i]-'a';
     //   cout << a << endl;
        result = (n * result + s[i] - 'a') %MOD;

    }
    return result;

}

long long int rehash(int big, int small, int n){

    if(small == 0){
        return myWord[big];
    }
    long long int diff = big - small;
    long long int temp = (long long int)pow(n, diff);
//    temp = temp % MOD;
    long long int myHash = (myWord[big] % MOD) - (myWord[small] * temp) % MOD;
    while (myHash < 0){
        myHash+=MOD;
    }
    myHash = myHash%MOD;
    return myHash;

}

long long int funcR(int index, int length){

    long long int count = 0;
    if(index == length){
        func[length] = 1;
        return 1;
    }
    if(func[index]!=-1){
        return func[index];
    }
    for(int i = 0; i < dict.size(); i++){
        long long int temp = dict[i];
        int tempL = dictWord[i].length();
        if(index + tempL <= myWord.size()) {
            long long int hashh = rehash(index+tempL, index, 29);
            hashh += MOD;
            hashh%=MOD;
            if (temp == hashh){
                if(word.substr(index,tempL).compare(dictWord[i]) == 0) {
                    count += funcR(index + tempL, length);
                    count %= MOD;
                }
            }
        }
    }
    while(count < 0){
        count += MOD;
    }
    func[index] = count;
    return func[index];

}


int main(int argc, char* argv[]) {

//    string s = "abc";
//    cout << s.length();
//    long long int a = hashit(s,29);
//    cout << a;

    ifstream infile(argv[1]);
    string line;
    infile >> line;
    word = line;
    infile >> line;
    int N = stoi(line);

    for (int i = 0; i < N; i++) {

        infile >> line;
        dictWord.push_back(line);
        long long int temp = hashit(line, 29);
        dict.push_back(temp);

    }

    myWord.push_back(0);
//    cout << word << endl;

    for(int i = 0; i < word.length(); i++){
        string temp = word.substr(0,i+1);
        long long int wordTemp = hashit(temp, 29);
        myWord.push_back(wordTemp);
    }

//    for(int i = 0; i < word.length() + 1; i++){
//        cout << myWord[i] << endl;
//    }

    for(int i = 0; i <= word.length(); i++){
        func.push_back(-1);
    }

    long long int result = funcR(0, word.length());
//    cout << result << endl;

//    for(int i = 0; i < func.size(); i++){
//        cout << func[i] << endl;
//    }

//    long long int deneme = rehash(3,1,29);
//    cout << deneme;



//    for (int i = 0; i < N; i++){
//        cout << dictWord[i] << " " << dict[i] << endl;
//    }


//    long long int abc = rehash(6, 4, 29);
//    cout << abc << endl;
//    cout << result % MOD << endl;

    ofstream myfile;
    myfile.open(argv[2]);
    myfile << result << endl;
    cout << result;


}