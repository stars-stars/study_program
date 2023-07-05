#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_number(string str) {
    for(const char &ch : str) {
        if(!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

int main(void) {
    string path, input;
    vector<string> ques(0), ans(0);
    int start_num, ques_num, ans_num, revise_num;
    time_t t = time(nullptr);
    const tm *now = localtime(&t);

    // ファイル名の入力
    cout << "保存するファイル名を入力(拡張子を含まずに) << ";
    getline(cin, path);
    path += ".txt";
    ifstream is_exist(path); // 読み取りファイルのオープンが成功したらtrueになる
    while(is_exist) {
        cout << "このファイル名は既に存在しています" << endl;
        cout << "保存するファイル名を入力(拡張子を含まずに) << ";
        getline(cin, path);
        path += ".txt";
        is_exist.open(path, ios::in);
    }

    // 回答の入力
    cout << "問題番号の始まりを入力 << ";
    getline(cin, input);
    while(!is_number(input)) {
        cout << "数値を入力してください" << endl;
        cout << "問題番号の始まりを入力 << ";
        getline(cin, input);
    }
    start_num = atoi(input.c_str());
    ques_num = start_num;
    cout << "\n各問の回答を入力" << endl;
    cout << "exitで入力の終了, reviseで入力の修正" << endl;
    do {
        cout << "問" << ques_num << ". << ";
        getline(cin, input);
        if(input == "exit") {
            break;
        }
        if(input == "revise") {
            cout << "修正したい問題番号を入力 << ";
            getline(cin, input);
            while(!is_number(input)) {
                cout << "数値を入力してください" << endl;
                cout << "修正したい問題番号を入力 << ";
                getline(cin, input);
            }
            revise_num = atoi(input.c_str());
            if(revise_num >= ques_num) {
                cout << "入力済みの問題しか修正できません" << endl;
            } else {
                cout << "(修正)問" << revise_num << ". << ";
                getline(cin, input);
                ques[revise_num - start_num] = input;
            }
            input = "";
            continue;
        } else {
            ques.push_back(input);
            ques_num++;
        }
    } while(true);

    // 解答の入力
    cout << "\n\n各問の解答を入力" << endl;
    cout << "reviseで入力の修正" << endl;
    ans_num = start_num;
    do {
        cout << "問" << ans_num << ". << ";
        getline(cin, input);
        if(input == "revise") {
            cout << "修正したい問題番号を入力 << ";
            getline(cin, input);
            while(!is_number(input)) {
                cout << "数値を入力してください" << endl;
                cout << "修正したい問題番号を入力 << ";
                getline(cin, input);
            }
            revise_num = atoi(input.c_str());
            if(revise_num >= ans_num) {
                cout << "入力済みの問題しか修正できません" << endl;
            } else {
                cout << "(修正)問" << revise_num << ". << ";
                getline(cin, input);
                ans[revise_num - start_num] = input;
            }
            input = "";
            continue;
        } else {
            ans.push_back(input);
            ans_num++;
        }
    } while(ans_num < ques_num);

    // 正答率の計算
    vector<bool> is_correct(ques.size());
    vector<int> wrongs(0);
    for(int i = 0; i < ques.size(); i++) {
        if(ques[i] == ans[i]) {
            is_correct[i] = true;
        } else {
            is_correct[i] = false;
            wrongs.push_back(start_num + i);
        }
    }

    // 結果の表示
    cout << "\n------------------------------------------------" << endl;
    cout << "問番号       正誤        予想        解答" << endl;
    for(int i = 0; i < ques.size(); i++) {
        cout << "問" << setw(3) << setfill(' ') << start_num + i << "         ";
        if(is_correct[i]) {
            cout << "○           ";
        } else {
            cout << "×           ";
        }
        cout << ques[i] << "           " << ans[i] << endl;
    }
    cout << "------------------------------------------------\n" << endl;
    cout << "\x1b[36m問題数は" << ques.size() << ", 正解数は" << ques.size() - wrongs.size() << ", 正答率は";
    cout << fixed << setprecision(0);
    cout << (static_cast<double>(ques.size() - wrongs.size()) / static_cast<double>(ques.size())) * 100;
    cout << "%" << endl;
    cout << "\x1b[92m以下間違った問題" << endl;
    for(int i = 0; i < wrongs.size(); i++) {
        cout << "問" << wrongs[i] << endl;
    }

    // 結果の書き込み
    ofstream file(path);
    if(!file) {
        cout << "ファイルが開けませんでした" << endl;
    } else {
        file << 1900 + now->tm_year << "-" << now->tm_mon << "-" << now->tm_mday << endl;
        file << "問題数は" << ques.size() << ", 正解数は" << ques.size() - wrongs.size() << ", 正答率は";
        file << fixed << setprecision(0);
        file << (static_cast<double>(ques.size() - wrongs.size()) / static_cast<double>(ques.size())) * 100;
        file << "%" << endl;
        file << "以下間違った問題" << endl;
        for(int i = 0; i < wrongs.size(); i++) {
            file << "問" << wrongs[i] << endl;
        }
        file << "\n\n------------------------------------------------" << endl;
        file << "問番号       正誤        予想        解答" << endl;
        for(int i = 0; i < ques.size(); i++) {
            file << "問" << setw(3) << setfill(' ') << start_num + i << "         ";
            if(is_correct[i]) {
                file << "○           ";
            } else {
                file << "×           ";
            }
            file << ques[i] << "          " << ans[i] << endl;
        }
        file << "------------------------------------------------\n" << endl;
        cout << "\nファイル名  " << path << "で保存しました" << endl;
    }
}