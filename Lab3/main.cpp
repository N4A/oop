#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>

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
void error_line(char* line);

int main(int argc, char* argv[])
{
    char* in_file;
    char* out_file;


    //get in file and out file path
    switch (argc) {
    case 2:
        in_file = argv[1];
        out_file = "a.cpp";
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
            *out << line << endl;
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

            //open new file
            ifstream in(s.c_str());
            if (!in) {
                cout << "File included not found: " << s << endl;
                //error_line(line);
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
        char key[20];
        char val[20];
        sscanf(cur,"%s %s",key,val);
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
    case ift:
    {
        char key[20];
        sscanf(cur,"%s",key);
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

void error_line(char* line)
{
    cout << "Invalid Instruction: " << line << endl;
    exit(0);
}

