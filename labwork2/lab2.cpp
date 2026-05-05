#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void fill_rand(vector<int>& data, double max, double min)
{
    // устанавливает стартовую точку для генерации
    // случайных чисел по текущему времени
    srand((unsigned) clock());
    for(int i=0; i<data.size(); ++i)
    {
        data[i]=round((rand()*(max-min))/RAND_MAX+min);
    }
}

void fill_rand_deque(deque<int>& data, double max, double min)
{
    // устанавливает стартовую точку для генерации
    // случайных чисел по текущему времени
    srand((unsigned) clock());
    for(int i=0; i<data.size(); ++i)
    {
        data[i] = (round((rand()*(max-min))/RAND_MAX+min));
    }
}

void Dynamic_array(){
    cout << "----Start of work with dynamic array----" << endl;
    int size = 10;
    double* array = new double[size];
    for (int i = 0; i < size; i++){
        array[i] = 10*i;
        cout << array[i] << " ";
    }
    cout << endl;
    int avg = 0;
    for (int i = 0; i < size; i++){
        avg += array[i];
    }
    avg = avg/size;
    cout << avg << endl;
    cout << "----End of work with dynamic array----" << endl;
    cout << endl;
}

vector<int> Vector(){
    cout << "----Start of work with a vector----" << endl;
    cout << "Generating of a vector of ints" << endl;
    vector<int> vec;
    int size = 15;
    vec.resize(size);
    fill_rand(vec, 5, 0);
    for (int i = 0; i < size; i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "End of generating" << endl;
    cout << endl;
    return vec;
}

void Algorithm_Vec(vector<int> vec){
    cout << "Start of algorithms on a vector" << endl;
    auto it = max_element(vec.begin(), vec.end());
    cout << "Maximum element of vector: " << *it << endl;
    cout << "Sum of all elements: " << accumulate(vec.begin(), vec.end(), 0) << endl;
    vector<int>::iterator new_end = remove(vec.begin(), vec.end(), 0);
    vec.resize(distance(vec.begin(), new_end));
    sort(vec.begin(), vec.end());
    cout << "Vector after sorting:\n";
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
    new_end = unique(vec.begin(), vec.end());
    vec.resize(distance(vec.begin(), new_end));
    cout << "Vector after deleting zeros and duplicate elements:\n";
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
    cout << "----Ending of work with a vector----" << endl;
    cout << endl;
}

list<double> List(){
    list<double> List_double;
    cout << "----Working with a list----" << endl;
    cout << "Start of input" << endl;
    bool flag = true;
    while (flag){
        cout << "Continue input? (y/n)" << endl;
        char answer;
        cin >> answer;
        if (answer == 'n' || answer == 'N'){
            cout << "End of input" << endl;
            flag = false;
        }
        else if(answer == 'y' || answer == 'Y'){
            cout << "Enter a number: ";
            double new_num;
            cin >> new_num;
            List_double.push_back(new_num);
        }
        else{
            cout << "Incorrect option" << endl;
        }
    };
    cout << "The final list:\n";
    for (auto it = List_double.begin(); it != List_double.end(); ++it){
        cout << (*it) << ' ';
    };
    cout << endl;
    auto max_el = max_element(List_double.begin(), List_double.end());
    cout << "Maximum element: " << (*max_el) << endl;
    cout << "----End of work with a list----" << endl;
    cout << endl;
    return List_double;
}

map<string, double> Glasses(){
    cout << "----Start of work with a map----" << endl;
    map<string, double> glasses;
    ifstream file("glass.txt");

    if (!file.is_open()){
        cerr << "There is no file to reading" << endl;
        return {};
    }

    string name;
    double refractive_idx;
    while(file >> name >> refractive_idx){
        glasses[name] = refractive_idx;
    };
    cout << "Glasses:" << endl;
    for (const auto& it : glasses){
        cout << it.first << ": " << it.second << endl;
    }
    cout << endl;
    auto [first, second] = minmax_element(glasses.begin(), glasses.end(), [](auto &a, auto &b){ return a.second > b.second;});
    cout << "Max refractive index: " << first->first << " " << first->second << endl;
    cout << "Min refractive index: " << second->first << " " << second->second << endl;
    cout << "----End of work with a map----" << endl << endl;
    return glasses;
}

pair<deque<int>, set<int>> Deque_set(){
    cout << "----Start of work with a deque and a set----" << endl;
    cout << endl;
    deque<int> new_deque;
    int size = 15;
    new_deque.resize(size);
    fill_rand_deque(new_deque, 5, 0);
    set<int> new_set;
    cout << "Deque of ints:" << endl;
    for (auto it = new_deque.begin(); it < new_deque.end(); ++it){
        cout << *it << " ";
        new_set.insert(*it);
    };
    cout << endl;
    cout << "Set of ints:" << endl;
    for (const auto& element : new_set){
        cout << element << " ";
    };
    cout << endl;
    cout << "----End of work with a deque and a set----";
    pair<deque<int>, set<int>> p(new_deque, new_set);
    return p;
}

int main(){
    Dynamic_array();
    vector<int> New_Vector = Vector();
    Algorithm_Vec(New_Vector);
    list<double> New_Lis = List();
    map<string, double> New_map = Glasses();
    pair<deque<int>, set<int>> p = Deque_set();
    return 1;
}