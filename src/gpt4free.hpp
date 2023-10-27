#include <iostream>
#include <vector>
#include "HTTPRequest.hpp"
#include "windows.h"
using namespace std;

namespace requests{
string post(vector<pair<string, string>> vbody, string addr){
    http::Request request{addr};
    std::string body = "{";//\"foo\": 1, \"bar\": \"baz\"}";
    int a = 0;
    for(auto &pr: vbody){ 
        body += "\"" + pr.first + "\": \"" + pr.second + ((a != vbody.size()-1) ? "\", " : "\" "); 
        a++;
    }
    body += "}";
    const auto response = request.send("POST", body, {
        {"Content-Type", "application/json"}
    });
    return std::string{response.body.begin(), response.body.end()};
}
}

enum gpt_models{
    GPT_v3p5_turbo,
    GPT_4
};

string ask_gpt(gpt_models model,
               string question,
               bool coutingQ = false, 
               string postinstructions = "", 
               string preinstructions  = ""){
    if(coutingQ){
        cout<<"> "<<question<<endl;
    }
    
    return requests::post({
        {"model", to_string(model)},
        {"req",   preinstructions + " --- " + question + " --- " + postinstructions}
    }, "http://127.0.0.1:900"); // localhost (where proxy is)
}

void gptProxyInit(){
    SetConsoleOutputCP(65001);        // utf-8
    system("start python src/proxy.pyw"); // starting python-proxy as sepparated process
    cout<<"starting proxy...\n";
    Sleep(10000);                     // 10 secs for Flask init
    cout<<"ready to work...\n\n";
}