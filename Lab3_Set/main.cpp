#include "Set.h"
#include "parser.h"

#include <iostream>

using namespace std;


int main() {


    Set A, B, result;
    Set *pizdec = new Set [100];
    string path = "../test.txt";
    Parser pars(path);

    if (pars.isParsedSuccessfully()) {

        int count =0;
        for (auto i : pars.parsedSets) {
            i.pprint();
            count++;
        }
        cout<<endl<<endl;
        for(int index =0; index < count; index++){
            pizdec[index] = pars.parsedSets[index];
        }
        int count_2 = ((count*(count+1))/2);
        for(int i = 0; i < count_2/count; i++){
            for(int j = 0; j < count; j++) {
                if(i != j) {
                    result.SymmetricDifference(pizdec[i], pizdec[j]);
                    result.pprint();
                }
            }
        }
    }


    return 0;
}
