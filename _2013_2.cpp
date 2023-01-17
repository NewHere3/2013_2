#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct town
{
    string name;
    string county;
    int residents;
};

struct county
{
    string name;
    int residents_min= INT_MAX;
    int residents_all=0;
};

void read(vector<town>& cities);
void write(vector<county> districts);

int main()
{
    vector<town> cities;
    vector<county> districts;
    vector<string> districts_names;

    read(cities);

    districts_names.push_back(cities[0].county);

    for (int i = 0; i < cities.size(); i++)
    {
        bool exists = 0;
        for (int j = 0; j < districts_names.size(); j++)
        {
            if (cities[i].county == districts_names[j])
            {
                exists = 1;
            }
        }
        if (!exists)
        {
            districts_names.push_back(cities[i].county);
        }
    }

    for (int j = 0; j < districts_names.size(); j++)
    {
        county temp;
        temp.name = districts_names[j];
        for (int i = 0; i < cities.size(); i++)
        {
            if (districts_names[j] == cities[i].county)
            {
                temp.residents_all += cities[i].residents;
                if (temp.residents_min > cities[i].residents) { temp.residents_min = cities[i].residents; }
            }
        }
        districts.push_back(temp);
    }
    // sort PAGAL ABECELE???????????
    for (int i = 0; i < districts.size(); i++)
    {
        for (int j = i+1; j < districts.size(); j++)
        {
            if(districts[i].residents_min == districts[j].residents_min)
            {
                for (size_t k = 0; k < districts[i].name.size(); k++)
                {
                    if (districts[i].name[k] > districts[j].name[k])
                    { 
                        swap(districts[i], districts[j]);
                        break;
                    }
                    else if (districts[i].name[k] < districts[j].name[k])
                    {
                        break;
                    }
                }
            }else if (districts[i].residents_min > districts[j].residents_min) { swap(districts[i], districts[j]); }
        }
    }
 
    write(districts);
    return 0;
}

void read(vector<town>& cities)
{
    ifstream duom("Duomenys.txt");
    int n;
    duom >> n;
    for (int i = 0; i < n; i++)
    {
        duom.ignore();
        char temp[21];
        duom.get(temp, 21);

        char temp2[14];
        duom.get(temp2, 14);

        int x;
        duom >> x;
        town temp3 = {temp, temp2, x};
        cities.push_back(temp3);
    }
}

void write(vector<county> districts)
{
    ofstream rez("Rezultatai.txt");
    for (int i = 0; i < districts.size(); i++)
    {
        rez << districts[i].name << districts[i].residents_min << ' ' << districts[i].residents_all << '\n';
    }
}