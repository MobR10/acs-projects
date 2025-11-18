#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

using namespace std; 

/*
CSV structure:
1. student_id, STRING
2. age, INT
3. gender, STRING
4. study_hours_per_day, FLOAT
5. social_media_hours, FLOAT
6. netflix_hours, FLOAT
7. part_time_job, STRING
8. attendance_percentage, FLOAT
9. sleep_hours, FLOAT
10. diet_quality, STRING
11. exercise_frequency, INT
12. parental_education_level, STRING
13. internet_quality, STRING
14. mental_health_rating, INT
15. extracurricular_participation, STRING
16. exam_score FLOAT
*/
#define UPB 1
#define MEDICINA 2
#define NUME_FISIER "studenti.csv"

class Random{
    std::mt19937 gen;                          // generator MT
    std::uniform_int_distribution<> dist;      // distribuție [UPB, MEDICINA]

public:
    Random(): gen(std::random_device{}()),  // seed din entropie
          dist(UPB, MEDICINA) {}    // intervalul dorit

    int get() {
        return dist(gen);
    }
};

class Student{
        
    int age;
    float studyHoursPerDay,socialMediaHours;
    string id,partTimeJob;

    public:
        Student(string id,int age, float studyHoursPerDay, float socialMediaHours, string partTimeJob)
        :id(id), age(age),studyHoursPerDay(studyHoursPerDay),socialMediaHours(socialMediaHours), partTimeJob(partTimeJob){}

        void printInfo(){
            printf("Student id: %s\nAge: %d\nStudy hours per day: %f\nSocial media hours: %f\nHas part time job: %s\n====\n",
            id.c_str(),age,studyHoursPerDay,socialMediaHours,partTimeJob.c_str());
        }

        int getAge() const{
            return this->age;
        }

        float getStudyHoursPerDay() const{
            return this->studyHoursPerDay;
        }

        float getSocialMediaHours() const{
            return this->socialMediaHours;
        }

        string getPartTimeJob() const{
            return this->partTimeJob;
        }

        virtual void printOccupation() = 0;

        virtual ~Student() {}
};

class StudentPolitehnica: public Student{

    public:
    StudentPolitehnica(string id,int age, float studyHoursPerDay, float socialMediaHours, string partTimeJob):
    Student(id, age,  studyHoursPerDay, socialMediaHours,  partTimeJob){}

    
    void printOccupation(){
        cout<<"I am building a robot!"<<endl;
    }
};

class StudentMedicina: public Student{

    public:
    StudentMedicina(string id,int age, float studyHoursPerDay, float socialMediaHours, string partTimeJob):
    Student(id, age,  studyHoursPerDay, socialMediaHours,  partTimeJob){}

    void printOccupation(){
        cout<<"I am making a vaccine!"<<endl;
    }
};
class Import{
    
    Random generator;
    public:
    Import() = default;

        // Add a StudentPolitehnica to the dynamic array
    void addPoli(StudentPolitehnica**& arr, int& count, int& capacity, StudentPolitehnica* s) {
        if (count >= capacity) {
            // grow array
            int newCapacity = capacity * 2;
            StudentPolitehnica** newArr = new StudentPolitehnica*[newCapacity];
            for (int i = 0; i < count; i++)
                newArr[i] = arr[i];  // copy old pointers
            delete[] arr;            // free old array
            arr = newArr;
            capacity = newCapacity;
        }
        arr[count++] = s;
    }

    // Add a StudentMedicina to the dynamic array
    void addMedicina(StudentMedicina**& arr, int& count, int& capacity, StudentMedicina* s) {
        if (count >= capacity) {
            int newCapacity = capacity * 2;
            StudentMedicina** newArr = new StudentMedicina*[newCapacity];
            for (int i = 0; i < count; i++)
                newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        arr[count++] = s;
    }

    void readCSV(string fileName,StudentPolitehnica**& studentiPOLI,int& poliCount,int& poliCapacity, StudentMedicina**& studentiMedicina,int& mediCount, int& mediCapacity){
        ifstream f(fileName);

        if(!f.is_open())
            cout<<"Nu s a putut deschide fisierul";
        else{
            /* 
            things we're interested in
            1. student_id, STRING
            2. age, INT
            4. study_hours_per_day, FLOAT
            5. social_media_hours, FLOAT
            7. part_time_job, STRING
            */
            int age;
            float studyHoursPerDay,socialMediaHours;
            string id,partTimeJob;

            string line;
            getline(f,line);
            string temp;

            while(getline(f,line)){

                stringstream ss(line);
                getline(ss,id,',');    
                getline(ss,temp,',');
                age = stoi(temp);

                
                getline(ss,temp,',');
                
                getline(ss,temp,',');
                studyHoursPerDay = stof(temp);
                getline(ss,temp,',');
                socialMediaHours = stof(temp);

                
                getline(ss,temp,',');
                
                getline(ss,partTimeJob,',');

                int choice = generator.get();

            
                if(choice == UPB)
                {   
                    
                    addPoli(studentiPOLI,poliCount,poliCapacity,new StudentPolitehnica(id,age,studyHoursPerDay,socialMediaHours,partTimeJob));
                }
                else
                {
                    addMedicina(studentiMedicina,mediCount,mediCapacity,new StudentMedicina(id,age,studyHoursPerDay,socialMediaHours,partTimeJob));
                }   
            }
        }   
    }
        
};

float getMeanAgeMedicina(StudentMedicina** studentiMedicina, int mediCount){
    float mean = 0;
    for(int i=0;i<mediCount;i++)
        {
            mean += studentiMedicina[i]->getAge();
        }
    return mean/mediCount;
}

float getMeanStudyPoli(StudentPolitehnica** studentiPoli, int poliCount){
    float mean= 0;

    for(int i=0;i<poliCount;i++)
        {
            mean += studentiPoli[i]->getStudyHoursPerDay();
        }
    return mean/poliCount;
}

float getMeanSocialPoli(StudentPolitehnica** studentiPoli, int poliCount){
    float mean= 0;

    for(int i=0;i<poliCount;i++)
        {
            mean += studentiPoli[i]->getSocialMediaHours();
        }
    return mean/poliCount;
}

int getNumberOfStudentsWithJob(StudentPolitehnica **studentiPoli, StudentMedicina** studentiMedicina, int poliCount, int mediCount){
    int counter = 0;

    int i=0,j=0;
    while(i< poliCount && j < mediCount){
        if(studentiPoli[i++]->getPartTimeJob() == "Yes"){
            counter++;
        }
        if(studentiMedicina[j++]->getPartTimeJob()== "Yes"){
            counter++;
        }
    }
    while(i<poliCount){
        if(studentiPoli[i++]->getPartTimeJob() == "Yes"){
            counter++;
        }
    }
    while(j<mediCount){
        if(studentiMedicina[j++]->getPartTimeJob()== "Yes"){
            counter++;
        }
    }

    return counter;
}

int main(){

    Import importer;

    StudentPolitehnica ** studentiPOLI = new StudentPolitehnica*[1];
    StudentMedicina** studentiMedicina= new StudentMedicina*[1];

    int poliCount = 0, mediCount = 0;
    int poliCapacity = 1, mediCapacity = 1;


    // for(int i=0; i <poliCount;i ++)
    //     studentiPOLI[i]->printInfo();
    string input;
    int ok=0;
    cout<<"Introdu numele fisierului csv (hint:"<< NUME_FISIER << "): ";
    while(!ok){
        getline(cin,input);
        try{
            if(input!=NUME_FISIER)
            throw "Numele fisierului este introdus gresit! Mai incearca:";
            else ok= 1;
        }catch(const char* e){
            cout<<e;
        }
    }

    importer.readCSV(input,studentiPOLI,poliCount,poliCapacity,studentiMedicina,mediCount,mediCapacity);
    cout<<"POLI STUDENTS: "<<poliCount<<endl;
    
    cout<<"Medi students: "<<mediCount<<endl;

    cout<<"MEAN AGE MEDICINA: "<<getMeanAgeMedicina(studentiMedicina,mediCount)<<endl;

    cout<<"Mean study hours per day POLI: "<< getMeanStudyPoli(studentiPOLI,poliCount)<<endl;

    cout<<"Mean social hours per day POLI: "<<getMeanSocialPoli(studentiPOLI,poliCount)<<endl;

    cout<<"Number of students with part time job: "<<getNumberOfStudentsWithJob(studentiPOLI,studentiMedicina,poliCount,mediCount)<<endl;

    cout<<"Occupation of poli student: ",studentiPOLI[0]->printOccupation();
    cout<<"Occupation of medicine student: ",studentiMedicina[0]->printOccupation();
    
    for(int i=0; i<poliCount; i++) delete studentiPOLI[i];
    for(int i=0; i<mediCount; i++) delete studentiMedicina[i];
    delete[] studentiPOLI;
    delete[] studentiMedicina;   
}