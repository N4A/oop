#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
#include "Eval.h"

using namespace std;

#define BUF 1024
#define IS_BLANK(s) (*(s)==' ' || *(s)=='\t')
#define IS_END(s) (*(s)=='\0')
#define SKIP_BLANK(s) do {  \
  while(!IS_END(s) && IS_BLANK(s))  \
    (s)++;  \
} while(0);

typedef enum {err=-1,include,define,undef,ifdef,ifndef,ift,elset,endif} insid_t;

typedef struct ins {
    char* name;
    insid_t id;
    int len;
} ins_t;

typedef map<string,string>::iterator id_it;

ins_t ins_table[] = {
    {"#include",include,8},
    {"#define",define,7},
    {"#undef",undef,6},
    {"#ifdef",ifdef,6},
    {"#ifndef",ifndef,7},
    {"#if",ift,3},
    {"#else",elset,5},
    {"#endif",endif,6}
};
const int ins_table_size = 8;
const int stdlib_size = 2;
const string stdlib[] = {"iostream","fstream","string","stdio.h","map","vector","stdlib.h"};

bool print = true;//define whether to print cur line
map<string,string> id_map;
bool has_id(string key) {
    return id_map.count(key);
}
void add_id(string key, string value) {
    id_map.insert(pair<string,string>(key, value));
}

void rm_id(string key) {
    id_map.erase(key);
}

ins_t find_ins(char* name);
void parse_file(ifstream* in, ofstream* out);
void parse_line(char* line, ofstream* out);
void parse_ins(char* line, ofstream* out);
void parse_code(char* line, ofstream* out);
void error_line(string line);
bool is_between_quotation(size_t pos,string strl);
bool is_stdlib(string key);
string replace_code(string code);
vector<string> parse_parameter(string fun);

Eval* eval = new Eval();//计算表达式真假

int main(int argc, char* argv[])
{
    char* in_file;
    char* out_file;
    cout << "hello baby" << endl;
    //get in file and out file path
    switch (argc) {
    case 2:
        in_file = argv[1];
        out_file = "pre_lab3.cpp";
        break;
    case 3:
        in_file = argv[1];
        out_file = argv[2];
        break;
    default:
        cout << "Argument error, you should enter 'pre in_file [out_file]'";
        return 0;
    }

    //cout << in_file << "/" << out_file << endl;


    //handle file
    ifstream in(in_file);
    if (!in) {
        cout << "File not found: " << in_file << endl;
        exit(0);
    }
    ofstream out(out_file);
    parse_file(&in, &out);

    return 0;
}

//find the instruction
ins_t find_ins(char* name)
{
    int i;
    for (i = 0; i < ins_table_size; i++)
        if (!strncmp(name, ins_table[i].name, ins_table[i].len))
            return ins_table[i];
    error_line(name);
}

//parse file and output to out
void parse_file(ifstream* in, ofstream* out) {
    char line[BUF];
    while (!(*in).eof()) {
        (*in).getline(line, BUF);
        parse_line(line, out);
    }
}

//parse each line
void parse_line(char* line, ofstream * out)
{
    char* cur = line;
    SKIP_BLANK(cur);
    if (*cur == '#') {//this is a pre compiled instruction
        parse_ins(cur, out);
    }
    else {//code
        if (print)
            parse_code(line, out);
    }
}

//parse instruction
void parse_ins(char* line, ofstream * out)
{
    char* cur = line;
    ins_t ins = find_ins(cur);
    cur += ins.len;
    SKIP_BLANK(cur);
    switch (ins.id) {
    case include:
    {
        char sign = *cur;
        cur++;
        if (sign == '<' || sign == '"') {
            string s = "";
            while (*cur != sign) {
                s += *cur;
                cur++;
            }

            if (is_stdlib(s)) {
                *out << line << endl;
                 break;
            }

            //open new file
            ifstream in(s.c_str());
            if (!in) {
                cout << "File included not found: " << s << endl;
                error_line(line);
            }
            else
                parse_file(&in, out);
        }
        else {
           error_line(line);
        }
        break;
    }
    case define:
    {
        char key[128];
        char val[128];
        string str = string(cur);

        int pos1 = str.find("(");
        int pos2 = str.find(" ");
        if (pos1 < pos2) {//has parameter
            int i = 0;
            while (true) {//skip blank
                if (str[i] == ')')
                    break;
                if (str[i] == ' ') {
                    str.replace(i,1,"");
                    i--;
                }
                i++;
            }
        }


        sscanf(str.c_str(),"%s %s",key,val);
        add_id(string(key),string(val));
        break;
    }
    case undef:
    {
        char key[20];
        sscanf(cur,"%s",key);
        rm_id(string(key));
        break;
    }
    case ifdef:
    {
        char key[20];
        sscanf(cur,"%s",key);
        if (has_id(string(key)))
            print = true;
        else
            print = false;
        break;
    }
    case ifndef:
    {
        char key[20];
        sscanf(cur,"%s",key);
        if (has_id(string(key)))
            print = false;
        else
            print = true;
        break;
    }
    case ift://TODO
    {
        char key[20];
        sscanf(cur,"%s",key);

        string val = string(key);

        val = replace_code(val);

        //去掉空格
        for (int i = 0; i < val.length(); i++) {
            if (val[i] == ' '){
                val.replace(i,1,"");
                i--;
            }
        }

        if(eval->Func(val) == false)
            print = false;
        else
            print = true;
        break;
    }
    case elset:
    {
        if (print)
            print = false;
        else
            print = true;
        break;
    }
    case endif:
    {
        print = true;
        break;
    }
    default:
    {
        error_line(line);
    }
    }
}

void parse_code(char* line, ofstream* out)
{
    *out << replace_code(string(line)) << endl;
}

string replace_code(string code)
{
    string strl = code;
    for (id_it it = id_map.begin(); it != id_map.end(); it++) {
        string key = it->first;
        size_t pos_l = key.find("(");
        if (pos_l == string::npos) {//normal macro
            size_t pos = strl.find(key);
            while (pos != string::npos) {
                if (!is_between_quotation(pos,strl))
                    strl.replace(pos,key.length(),it->second);
                pos = strl.find(key,pos+1);
            }
        }
        else {//macro with parameter
            size_t pos_r = key.find(")");
            if (pos_r == string::npos)
                error_line(key);

            string key1 = key.substr(0,pos_l);
            size_t pos = strl.find(key1);
            //parse the parameter in key
            vector<string> key_para = parse_parameter(key);

            while (pos != string::npos) {
                if (!is_between_quotation(pos,strl)) {
                    size_t pos2 = strl.find(")",pos+1);//end of macro to be replaced.
                    size_t len = pos2 - pos + 1;
                    string fun = strl.substr(pos,len);
                    vector<string> fun_para = parse_parameter(fun);//get macro function parameter

                    //get value and replace parameter
                    string value = it->second;
                    for (size_t i = 0; i < key_para.size(); i++) {
                        size_t p = value.find(key_para[i]);
                        value.replace(p,key_para[i].length(),fun_para[i]);
                    }
                    strl.replace(pos,len,value);
                }
                pos = strl.find(key1,pos+1);
            }
        }
    }

    return strl;
}

bool is_between_quotation(size_t pos, string strl)
{
    size_t pos1 = strl.find('"');
    while (pos1 != string::npos && pos1 < pos) {
        size_t pos2 = strl.find('"',pos1 + 1);
        if (pos2 > pos)
            return true;
        if (pos2 < strl.length()-1)
            pos1 = strl.find('"',pos2 + 1);
        else
            return false;
    }

    return false;
}

vector<string> parse_parameter(string fun)
{
    vector<string> p;
    size_t pos_s = fun.find("(") + 1;
    size_t pos_e = fun.find(")");
    size_t pos_n = fun.find(",", pos_s);
    while (pos_n != string::npos) {
        p.push_back(fun.substr(pos_s,pos_n-pos_s));

        pos_s = pos_n + 1;
        pos_n = fun.find(",",pos_s);
    }
    p.push_back(fun.substr(pos_s,pos_e-pos_s));//the last parameter

    return p;
}

void error_line(string line)
{
    cout << "Invalid Instruction: " << line << endl;
    exit(0);
}

bool is_stdlib(string key)
{
    for (int i = 0; i < stdlib_size; i++) {
        if (key == stdlib[i])
            return true;
    }
    return false;
}
