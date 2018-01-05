#include "function.h"

string RSHash(const char str[]){
        int b = 378551;
        int a = 63689;
        long long hash = 0;
        for (int i = 0;i<strlen(str);i++)
                hash=hash*a+str[i],a=a*b;
        stringstream ss;
        ss<<hash;
        string ans;
        ss>>ans;
        return ans;
}
int string_to_int(string s){
        stringstream ss;
        int ans;
        ss<<s;
        ss>>ans;
        return ans;
}
string int_to_string(int i){
    stringstream ss;
    string ans;
    ss<<i;
    ss>>ans;
    return ans;
}
double string_to_double(string s){
    stringstream ss;
    double ans;
    ss<<s;
    ss>>ans;
    return ans;
}
string double_to_string(double s){
    stringstream ss;
    string ans;
    ss<<s;
    ss>>ans;
    return ans;
}
void get_time(char ch[]){
    time_t t=time(0);
    //strftime(ch,16,"%Y-%02m-%02d",localtime(&t));
    strftime(ch, 64 , "%Y-%m-%d %H:%M:%S",localtime(&t));
}
void write_vec(const char road[],vector<vector<string> > v){
    ofstream f(road,ios::trunc);
    for(vector<string> i:v){
        for(string j:i){
            f<<j<<" ";
        }
        f<<endl;
    }
    f.close();
}
