//
// Created by Vladimir Moshchuk on 24.03.22.
//

#include <fstream>
#include <iostream>
using namespace std;

int  main(){
    int *check = new int [19];
    ifstream file;
    for(int i = 0; i <= 19; i++){
        file.open("../Tests/" + to_string(i+1) + ".out");
        file >> check[i];
        file.close();
    }
    for(int i = 1; i <= 20; i++){
        string command = "/Users/ardonplay/Documents/Developer/C++_Codes/RPIIS_Labs/Lab2/cmake-build-debug/Lab2 ../Tests/"+ to_string(i)+".in";
        system(command.c_str());
    }
    file.open("../Output.txt");
    int *output = new int[19];
    for(int i = 0; i <= 19; i++){
        file >> output[i];
    }
    file.close();
    remove("../Output.txt");

    for(int i = 0; i <= 19; i++){
        cout<<"Test №"<<i+1;
        if(check[i] == output[i]){
            cout<<" PASS!"<<endl;
        }
        else{
            cout<<" Failed!"<<endl;
            cout<<"Your output: "<< output[i] << "  Default output: "<<check[i]<<endl;
        }
    }
    return 0;
}