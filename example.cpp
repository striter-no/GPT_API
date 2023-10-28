#include "gpt4free.hpp"

int main(){
    string responce;
    // gptProxyInit();// can be started at once (for many versions of cpp program)
    enbaleUTF8();
    enableContext();

    gpt_models model = GPT_v4;

    wcout<<ask_gpt(model, L"Привет!")<<endl<<endl;
    while(true){
        wstring question;
        do{
            wstring t;
            wcin>>t;
            question += t + L' ';
        }while(wcin.peek()!='\n');
        // getline "improvisation"
        

        wcout<<(ask_gpt(model, question, false, true))<<endl<<endl;
    }

}