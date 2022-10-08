#define CROW_MAIN
#include "crow.h"
#include<fstream>
#include <set>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("words.txt");
	vector<string> words;
	string buffer;
	if(fin){
		while(!fin.eof()){
			fin>>buffer;
			words.push_back(buffer);
		}
	}
	fin.close();


    crow::SimpleApp app;

    CROW_ROUTE(app, "/words=<int>")
    ([words](int n){
		crow::json::wvalue x;
		int i=0;
		set<int> used;
		while(i<n){
			int r=rand()%words.size();
			if(used.find(r)==used.end()){
				used.insert(r);
				x["words"][i]=words[r];
				i++;
			}
		}
		return x;
	});

	CROW_ROUTE(app, "/words=<int>+length=<int>")
    ([words](int n, int l){
		crow::json::wvalue x;
		int i=0;
		set<int> used;
		while(i<n){
			int r=rand()%words.size();
			if ( (used.find(r)==used.end()) && (words[r].length()>=l) ){
				used.insert(r);
				x["words"][i]=words[r];
				i++;
			}
		}
		return x;
	});

    app.port(18081)
        .multithreaded()
        .run();
}
