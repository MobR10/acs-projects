#include <iostream>
#include <string>

using namespace std;

class Logger{
    public:
    void log(const string& mesaj){
        cout<<"Logged: " + mesaj + "\n";
    }
    static Logger& getInstance(){
        if(instance == nullptr){
            instance = new Logger();
        }
        return *instance;
    }
    private:
    static Logger* instance;

    Logger(){
        cout<<"Sistemul de Jurnalizare a pornit." <<endl;    
    }

    ~Logger() = delete;
    
    Logger(const Logger& other) = delete;
};

Logger* Logger::instance = nullptr;

int main(){


    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();


    logger1.log("Salut din prima referinta");
    logger2.log("Salut din a doua referinta");

    cout << &logger1 << " vs " << &logger2 << std::endl; 
    return 0;
}