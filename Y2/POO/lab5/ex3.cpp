#include <iostream>
#include <string>


using namespace std;

class Clasa{
    private:
    string string1, string2;

    public:
    Clasa(string string1="N/A", string string2="N/A"): string1(string1),string2(string2){}

    string operator+(){
        return string1 + string2;
    }

    void operator-(string s) {

            size_t pos1 = s.find('.');
            size_t pos2 = s.find(',');
            size_t pos;

            if (pos1 != string::npos) {pos= pos1;}
            else if (pos2 != string::npos) pos = pos2;
            else {
                cout<<"Nu exista delimitatorii '.' sau ','\n";
                return;
            }

            cout<<"Stringul pana la primul delimitator: " << s.substr(0, pos)<<"\nStringul ramas: "<< s.substr(pos+1)<< endl;

    }
    
};

int main(){
    Clasa clasa;

    cout<<+clasa<<endl;

    clasa - "salu,tgigele";
    
}