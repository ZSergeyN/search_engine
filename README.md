<h1 align="center">Search in documents</h1>
<p align="center">
<img src="https://img.shields.io/badge/made_by-ZSergeyN-blue">
<img src="https://img.shields.io/badge/language-C%2B%2B-red">

<h3 align="center"><i> Search for words in documents</i> | <i> Поиск слов в документах</i></h3>

## Description | Описание

![GitHub author](https://img.shields.io/badge/ENG-blue)<br>
 A console application that searches for queries in documents.
The application is configured using JSON files.<br>

![GitHub author](https://img.shields.io/badge/RUS-red)<br>
 Консольное приложение, которое выполняет поиск запросов в документах.
Настройка приложения выполняется с помощью файлов формата JSON.<br>

## Technologies | Технологии
![GitHub author](https://img.shields.io/badge/C%2B%2B-17-green?style=for-the-badge)<br>

![GitHub author](https://img.shields.io/badge/CMake-3.24-green?style=for-the-badge)<br>
<https://cmake.org/><br>

![GitHub author](https://img.shields.io/badge/nlohmann_json-3.11.3-green?style=for-the-badge)<br>
<https://github.com/nlohmann/json><br>

![GitHub author](https://img.shields.io/badge/GoogleTest-1.15.2-green?style=for-the-badge)<br>
<https://github.com/google/googletest><br>

## Files | Файлы
<br>*config.json*
  (Application configuration file | Файл настройки приложения)
  * name — the name of the application | название приложения
  * version — version number | номер версии
  * max_responses — maximum number of responses | максимальное количество ответов
  * files - file paths to search for | пути к файлам для поиска
  
<br>*requests.json*
  (Request file | Файл с запросами)
  * Maximum of 1000 requests | Не более 1000 запросов
  * From one to ten words | От одного до десяти слов
  * All words consist of lowercase Latin letters | Все слова состоят из строчных латинских букв
  
<br>*answers.json*
(A file with responses to queries | Файл с ответами на запросы)
  * request - request number | номер запроса
  * result – search result | результат поиска
  * docid — document number | номер документа
  * rank — search ranking | поисковый рейтинг

## Building & Running | Создание и Запуск
Step 1: Build the project | Создайть проект<br>
  * If you use Visual Studio compiler | Если вы используете компилятор Visual Studi<br>
  
    * For x64 version | Для версии x64<br>
`cmake -A x64 -S . -B "build64"`<br>
`cmake --build build64 --config Release`<br>
    * For x32 version | Для версии x32<br>
`cmake -A Win32 -S . -B "build32"`<br>
`cmake --build build32 --config Release`<br>

  * In other cases use default build | В других случаях используйте сборку по умолчанию<br>
`cmake -S . -B "build"`<br>
`cmake --build build --config Release`<br>

Step 2: Edit files | Редактировать файлы<br>
`.\bin\requests.json`, `.\bin\config.json`, `.\bin\answers.json` and `.\bin\resources` folder<br>

Step 3: Run the application | Запустить приложение<br>
`.\bin\Release\search_engine`<br>
