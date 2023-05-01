#include <iostream>
#include <vector>
#include <string>

#include "data.hpp"

void mySplitData(string const &str, const char delim, vector<string> &out) {

    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {

        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

/*==================================MY TRIM FUNCTION=====================================*/

string toRemove_data = " \n\r\t\f\v"; // all types of possible spaces to remove

string leftTrim_data(const string &s){
    auto start = s.find_first_not_of(toRemove_data); // finding the index just after white spaces
    return (start == string::npos) ? "" : s.substr(start); // removed leading white spaces
}
string rightTrim_data(const string &s){
    auto end = s.find_last_not_of(toRemove_data); // finding the index just before white spaces
    return (end == string::npos) ? "" : s.substr(0, end + 1); // removed trailing white spaces
}
string trim_data(const string &s) {
    // first trimming the left white space i.e.
    // leading white spaces and next trimming the right white spaces i.e. trailing white spaces 
    return rightTrim_data(leftTrim_data(s)); 
}
/*========================================================================================*/

int Data::anos(string data_inicial, string data_final){

    vector<string> data_i, data_f;

    mySplitData( data_inicial, '/', data_i );
    mySplitData( data_final, '/', data_f );

    int ano_i, mes_i, dia_i, ano_f, mes_f, dia_f;

    ano_i = stoi(data_i[2]);
    mes_i = stoi(data_i[1]);
    dia_i = stoi(data_i[0]);

    ano_f = stoi(data_f[2]);
    mes_f = stoi(data_f[1]);
    dia_f = stoi(data_f[0]);

    int anos = ano_f - ano_i;

    if( mes_f < mes_i){
        anos -= 1;
    }
    else if( mes_f == mes_i ){
        if( dia_f < dia_i ){
            anos -= 1;
        }
    }

    return anos;
}