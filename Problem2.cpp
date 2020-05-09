#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define PLUS 0
#define MINUS 1
#define MULTIPLY 2

vector<int> list_operation(vector<int> target, vector<int>& plus, vector<int>& minus, vector<int>& multi, int order) {
    vector<int> res(target);
    vector<int>::iterator itr;
    if (order == PLUS) {
        for (int i = 0; i < plus.size(); i++) {
            int location = plus[i];
            int mem = res[location] + res[location + 1];
            res.erase(res.begin() + location); res.erase(res.begin() + location);
            res.insert(res.begin() + location, mem);

            for (int j = 0; j < plus.size(); j++) {
                plus[j]--;
            }

            for (int j = 0; j < minus.size(); j++) {
                if (minus[j] > location)
                    minus[j]--;
            }
            for (int j = 0; j < multi.size(); j++) {
                if (multi[j] > location)
                    multi[j]--;
            }
            
        }
    }
    else if (order == MINUS) {
        for (int i = 0; i < minus.size(); i++) {
            int location = minus[i];
            int mem = res[location] - res[location + 1];
            //cout << *(res.begin() + location) << " " << *(res.begin() + location+1) << endl;
            res.erase(res.begin() + location); res.erase(res.begin() + location);
            res.insert(res.begin() + location, mem);
            
            //cout << mem;
            for (int j = 0; j < minus.size(); j++) {
                minus[j]--;
            }
            for (int j = 0; j < plus.size(); j++) {
                if (plus[j] > location)
                    plus[j]--;
            }

            for (int j = 0; j < multi.size(); j++) {
                if (multi[j] > location)
                    multi[j]--;
            }
        }
    }
    else {
        for (int i = 0; i < multi.size(); i++) {
            int location = multi[i];
            int mem = res[location] * res[location + 1];
            res.erase(res.begin() + location); res.erase(res.begin() + location);
            res.insert(res.begin() + location, mem);

            for (int j = 0; j < multi.size(); j++) {
                multi[j]--;
            }
            for (int j = 0; j < plus.size(); j++) {
                if (plus[j] > location)
                    plus[j]--;
            }

            for (int j = 0; j < minus.size(); j++) {
                if (minus[j] > location)
                    minus[j]--;
            }
        }
    }

    return res;
}


long long solution(string expression) {
    long long answer = 0;
    int leng = expression.size();

    string splitter;
    vector<int> numberlist;
    vector<int> location_plus;
    vector<int> location_minus;
    vector<int> location_multi;

    int indexmaking = 0;
    for (int i = 0; i < leng; i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            numberlist.push_back(stoi(splitter));
            if (expression[i] == '+') {
                location_plus.push_back(indexmaking);
            }
            else if (expression[i] == '-') {
                location_minus.push_back(indexmaking);
            }
            else {
                location_multi.push_back(indexmaking);
            }
            indexmaking++;
            splitter.clear();
        }
        else {
            splitter += expression[i];
        }
        if (i == leng - 1) {
            numberlist.push_back(stoi(splitter));
        }
    }

    vector<int> seq;
    vector<int> seq_plus = location_plus;
    vector<int> seq_minus = location_minus;
    vector<int> seq_multi = location_multi;
    if (!seq_plus.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, PLUS);
        if (!seq_minus.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MINUS);
            if (!seq_multi.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MULTIPLY);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        seq_plus = location_plus;
        seq_minus = location_minus;
        seq_multi = location_multi;
        cout << abs(seq[0]) << endl;
    }
    if (!seq_plus.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, PLUS);
        if (!seq_multi.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MULTIPLY);
            if (!seq_minus.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MINUS);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        seq_plus = location_plus;
        seq_minus = location_minus;
        seq_multi = location_multi;
        cout << abs(seq[0]) << endl;
    }
    if (!seq_minus.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, MINUS);
        if (!seq_plus.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, PLUS);
            if (!seq_multi.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MULTIPLY);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        seq_plus = location_plus;
        seq_minus = location_minus;
        seq_multi = location_multi;
        cout << abs(seq[0]) << endl;
    }
    if (!seq_minus.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, MINUS);
        if (!seq_multi.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MULTIPLY);
            if (!seq_plus.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, PLUS);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        seq_plus = location_plus;
        seq_minus = location_minus;
        seq_multi = location_multi;
        cout << abs(seq[0]) << endl;
    }
    if (!seq_multi.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, MULTIPLY);
        if (!seq_plus.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, PLUS);
            if (!seq_minus.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MINUS);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        seq_plus = location_plus;
        seq_minus = location_minus;
        seq_multi = location_multi;
        cout << abs(seq[0]) << endl;
    }
    if (!seq_multi.empty()) {
        seq = list_operation(numberlist, seq_plus, seq_minus, seq_multi, MULTIPLY);
        if (!seq_minus.empty()) {
            seq = list_operation(seq, seq_plus, seq_minus, seq_multi, MINUS);
            if (!seq_plus.empty()) {
                seq = list_operation(seq, seq_plus, seq_minus, seq_multi, PLUS);
            }
        }
        if (answer < abs(seq[0]))
            answer = abs(seq[0]);
        cout << abs(seq[0]) << endl;
    }
    


    return answer;
}