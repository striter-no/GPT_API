# GPT Free C++ API

Этот инструмент позволяет легко и бесплатно обращаться к gpt-моделям (например gpt-4 или gpt-3.5 turbo)
Данный проект является оберткой над `python прокси` который и задает запросы через [`g4f`](https://github.com/xtekky/gpt4free).
Для успешного запуска нужно:
- Компилятор g++
- Python 3
- Установленная python-библиотека `g4f`
- Установленная python-библиотека `flask`

Библиотеки python'а можно установить через командную строку:
```
pip install -U g4f
pip install flask
```

Для компиляции проекта нужна такая команда:
```
g++ -o example example.cpp -I src -lws2_32
```

Использование библиотеки максимально простое. Чтобы задать вопрос требуется всего-лишь указать модель, сам запрос, а также можно указать доп. параметры (вывод вопроса, пост-текст (текст будет вставляться после вашего вопроса) и пре-текст (текст будет вставляться перед вашим вопросом))
Ожидание ответа на запрос может занять до 5 секунд.

Вот пример `"Hello world"`:
```cpp
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

        wcout<<(ask_gpt(model, question, false, true))<<endl<<endl;
    }

}
```

Эта программа позволяет вести диалог с Chat GPT, и также позволяет использовать символы юникода (UTF-16)