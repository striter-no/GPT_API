#include "gpt4free.hpp"

int main(){
    gptProxyInit();
    
    string responce = ask_gpt(GPT_v3p5_turbo, "Привет, какова площадь Австралии?", true);
    cout<<"> "<<responce<<endl;
}