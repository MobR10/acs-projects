#include <iostream>
#include <string>

using namespace std;

class Monster{

    public:
    Monster(){
    }
    void spawn(){
        cout<<"Monster spawns in swamp.\n";
    }
};

class Environment{
    
    public:
    void generateMap(){
        cout<<"Map is generating.\n";
    }
};

class Player{
    int attackDmg=10;

    public:
    void spawn(){
        cout<<"Player spawns in the base.\n";
    }
};

class Game{
    Monster** monsters;
    Environment* environment;
    Player* player;

    public:
    Game (){
        monsters = new Monster*[10];
        environment = new Environment();
        player = new Player();
    }
    void startGame(){
        environment->generateMap();
        for(size_t i = 0; i < 10; i++)
            monsters[i]->spawn();
        player->spawn();
    }

    ~Game(){
        delete player;
        for(size_t i = 0; i < 10; i++)
            delete monsters[i];
        delete[] monsters;
        delete environment;
    }
};

int main(){
    Game game ;
    game.startGame();
}