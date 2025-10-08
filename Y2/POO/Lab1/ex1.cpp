#include <iostream>
#include <string>

using namespace std;

class Student {

    public:
    string lastName,firstName,group;
    string proSDA;
    string conSDA;
    string summerOccupation;
    string postGradPlan;

    public:
    Student(string lastName,string firstName, string group, string proSDA, string conSDA, string summerOccupation, string postGradPlan);
};

Student::Student(string lastName,string firstName, string group, string proSDA, string conSDA, string summerOccupation, string postGradPlan){
        this->lastName= lastName;
        this->firstName = firstName;
        this->group = group;
        this->proSDA = proSDA;
        this->conSDA = conSDA;
        this->summerOccupation = summerOccupation;
        this->postGradPlan = postGradPlan;
    }

int main(){
    Student student("Anghel","Raffaele","323AC",
    "Mi-a placut laboratorul pentru ca ne-a introdus in multi algoritmi de baza, in GitHub si Chis e fire.",
    "Algoritmii pe care a trebuit sa ii invatam odata cu capitolul de arbori (pretty difficult imo)",
    "Pe langa gamEing, am fost la scoala de vara IPWorkshop (goated), unde m-am distrat cu "\
    "Raspberry PI Pico si am zis sa muncesc o perioada scurta cu rigips.",
    "Intrebarea e cam generala. In prezent am prins un internship mititel si planuiesc sa muncesc si sa invat cat mai multe "\
    "pe parcursul facultatii, astfel incat dupa ce termin facultatea sa am o idee cat mai clara a optiunilor pe care le am si sa iau "\
    "cea mai buna decizie pentru mine.");

    cout<<"Nume: "<<student.lastName<<endl<<"Prenume: "<<student.firstName<<endl\
    <<"Grupa: "<<student.group<<endl<<"Ce mi-a placut la SDA: "<<student.proSDA<<endl\
    <<"Ce nu mi-a placut la SDA: "<<student.conSDA<<endl<<"Ce-am facut vara asta: "<<student.summerOccupation<<endl\
    <<"Ce planuri am dupa ce termin facultatea: "<<student.postGradPlan;
    return 0;
}