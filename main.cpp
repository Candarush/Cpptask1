#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

class Tabel
{
public:
    
    string group;
    
    class Day
    {
    public:
        
        class Student
        {
        public:
            string person;
            int present;
            Student(string iname, int ipresent)
            {
                person = iname;
                present = ipresent;
            }
        };
        
        vector<Student> Table;
        string date;
        int size;
        
        Day()
        {
            date = "0.0.0";
        }
        
        void show()
        {
            cout<< date;
            for (int i = 0; i<Table.size();i++)
            {
                cout<<Table[i].person<<" "<<Table[i].present<<endl;
            }
            cout<<endl;
        }
        
        void load(string filename)
        {
            ifstream file(filename);
            if (!file.is_open())
            {
                cerr<<"Файл не найден!"<<endl;
                return;
            }
            string readline;
            getline(file,readline);
            date = readline;
            string curStudentPerson;
            int curStudentPresent;
            
            while (getline(file,readline,','))
            {
                curStudentPerson=readline;
                getline(file,readline);
                curStudentPresent = stoi(readline);
                Table.push_back(Student(curStudentPerson,curStudentPresent));
            }
            file.close();
            
        }
        
    };
    
    vector<Day> Array;
    Tabel(string iname)
    {
        group = iname;
    }
    
    void newday(string filename)
    {
        Day curDay;
        curDay.load(filename);
        Array.push_back(curDay);
    }
    
    void unload()
    {
        vector<Day::Student> studArray;
        for (int i = 0; i<Array.size(); i++)
        {
            for (int j = 0; j<Array[i].Table.size(); j++)
            {
                Day::Student curStud = Array[i].Table[j];
                string studName = curStud.person;
                if (studArray.size())
                {
                    for (int k = 0; k < studArray.size();k++)
                    {
                        if (studArray[k].person == studName)
                        {
                            studArray[k].present += curStud.present;
                            break;
                        }
                        if (k == studArray.size()-1)
                        {
                            Day::Student newStud(studName,0);
                            studArray[k].present += curStud.present;
                            studArray.push_back(newStud);
                        }
                    }
                }
                else
                {
                    Day::Student newStud(studName,0);
                    newStud.present += curStud.present;
                    studArray.push_back(newStud);
                }
            }
        }
        
        cout<<group<<endl;
        
        for (int i = 0; i < studArray.size(); i++)
        {
            cout<<studArray[i].person<<" "<<studArray[i].present<<endl;
        }
    }
};

int main(int argc, char *argv[])
{
    Tabel MyTabel("M30-212Б-18");
    
    for (int i = 1; i<argc; i++)
    {
        MyTabel.newday(argv[i]);
        MyTabel.Array[i-1].show();
    }
    
    MyTabel.unload();
    
    return 0;
}
