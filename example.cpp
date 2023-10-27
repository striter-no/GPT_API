#include "gpt4free.hpp"

int main(){
    string responce;
    gptProxyInit();
    
    responce = ask_gpt(GPT_v3p5_turbo, "Привет, какова площадь Австралии?", true);
    cout<<"> "<<responce<<endl;
    
    cout<<endl;

    responce = ask_gpt(GPT_v4, "Привет, какова площадь Австралии?", true);
    cout<<"> "<<responce<<endl;
}