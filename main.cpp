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
            cout<< date<<endl;
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

    void unload_scr();
    void unload_file(string filename);
};

void Tabel::unload_scr()
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
    
    cout<<group;
    for (int i = 0; i<15-group.length();i++)
    {
        cout << " ";
    }
    cout<<"|";
    for (int i = 0; i<Array.size();i++)
    {
        cout << " " << Array[i].date<< " |";
    }
    cout<< " Total" <<endl;
    
    for (int l = 0; l < studArray.size(); l++)
    {
        cout<<studArray[l].person;
        for (int j = 0; j<15-studArray[l].person.length()/2;j++)
        {
            cout << " ";
        }
        cout<<"|";
        
        for (int i = 0; i<Array.size(); i++)
        {
            for (int j = 0; j<Array[i].Table.size(); j++)
            {
                Day::Student curStud = Array[i].Table[j];
                if (curStud.person==studArray[l].person && curStud.present)
                {
                    cout<<"     +    |";
                    break;
                }
                if (j==Array[i].Table.size()-1)
                {
                    cout<<"     -    |";
                }
            }
        }
        cout<< " " << studArray[l].present<<endl;
    }
}

void Tabel::unload_file(string filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr<<"Файл не найден!"<<endl;
        return;
    }
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
    
    file<<group;
    for (int i = 0; i<Array.size();i++)
    {
        file << "," <<Array[i].date;
    }
    file<<",Total"<<endl;
    
    for (int l = 0; l < studArray.size(); l++)
    {
        file<<studArray[l].person;

        for (int i = 0; i<Array.size(); i++)
        {
            for (int j = 0; j<Array[i].Table.size(); j++)
            {
                Day::Student curStud = Array[i].Table[j];
                if (curStud.person==studArray[l].person && curStud.present)
                {
                    file<<",+";
                    break;
                }
                if (j==Array[i].Table.size()-1)
                {
                    file<<",-";
                }
            }
        }
        file<< "," << studArray[l].present<<endl;
    }
    file.close();
}
    
int main(int argc, char *argv[])
{
    if (argc<2)
    {
        cerr<<"Недостаточно аргументов, 1 аргумент - файл для вывода данных, остальные - файлы для чтения данных!";
        return 1;
    }
    
    Tabel MyTabel("M30-666-18");
    
    for (int i = 2; i<argc; i++)
    {
        MyTabel.newday(argv[i]);
        MyTabel.Array[i-2].show();
    }
    
    MyTabel.unload_scr();
    
    MyTabel.unload_file(argv[1]);
    
    return 0;
}
