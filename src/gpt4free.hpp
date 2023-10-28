#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>
#include <memory>
#include <stdexcept>
#include <io.h>
#include <fcntl.h>
#include "HTTPRequest.hpp"
#include "windows.h"
using namespace std;

bool __isContextEnabled = false;
std::wstring history;

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
string wstringToString(std::wstring src){
    return converter.to_bytes(src);
}

namespace requests{
std::wstring post(vector<pair<std::wstring, std::wstring>> vbody, string addr){
    http::Request request{addr};
    std::wstring body = L"{";//\"foo\": 1, \"bar\": \"baz\"}";
    int a = 0;
    for(auto &pr: vbody){
        body += L"\"" + pr.first + L"\": \"" + pr.second + ((a != vbody.size()-1) ? L"\", " : L"\" "); 
        a++;
    }
    body += L"}";
    const auto response = request.send("POST", wstringToString(body), {
        {"Content-Type", "application/json"}
    });
    return std::wstring{response.body.begin(), response.body.end()};
}

std::wstring post2(std::wstring vbody, string addr){
    http::Request request{addr};
    const auto response = request.send("POST", wstringToString(vbody), {
        {"Content-Type", "text/plain"}
    });
    return std::wstring{response.body.begin(), response.body.end()};
}

}

enum gpt_models{
    GPT_v3p5_turbo,
    GPT_v4
};

enum gpt_providers{
    AiAsk, // Fast gpt 3.5-turbo provider , but has big requests problems
    MyShell, // Fast gpt 4 and gpt 3.5-turbo provider, but has strong pre-settings to his character
    ChatBase, // Fast gpt 3.5-turbo provider, has minimum settings to his character ()
    Phind // Standart gpt 4 and gpt 3.5-turbo provider, has minimum settings to his character
};

std::wstring ask_gpt(gpt_models model,
                     std::wstring question,
                     bool coutingQ = false,
                     gpt_providers provider = Phind, 
                     std::wstring preinstructions = L"", 
                     std::wstring postinstructions  = L""){
    if(coutingQ) wcout<<L"> "<<question<<endl;
    if(__isContextEnabled) history += L"#&x0SЯ:" + question + postinstructions;

    std::wstring ans;
    if(!__isContextEnabled){
        ans = requests::post2({
            L"#&x0S" + to_wstring(model) + L"#&x0S" + to_wstring(provider) +  L"#&x0S" + preinstructions + question + postinstructions
        }, "http://127.0.0.1:900"); // localhost (where proxy is)
    } else {
        ans = requests::post2({
            L"#&x0S" + to_wstring(model) + L"#&x0S" + to_wstring(provider) +  L"#&x0S" + history
        }, "http://127.0.0.1:900"); // localhost (where proxy is)
    }

    if(__isContextEnabled) history += L"#&x0SТы:" + ans;
    return ans;
}

void enableContext(){ __isContextEnabled = true; }
void disableContext(){ __isContextEnabled = false; }

void enbaleUTF8(){
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT); 
    SetConsoleOutputCP(65001);
}

void gptProxyInit(){
    system("start python src/proxy.pyw"); // starting python-proxy as sepparated process
    wcout<<"starting proxy...\n";
    Sleep(10000);                     // 10 secs for Flask init
    wcout<<"ready to work...\n\n";
}