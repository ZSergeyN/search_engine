<h1 align="center">Search in documents</h1>
</h2>
<p align="center">
<img src="https://img.shields.io/badge/made_by-ZSergeyN-blue">
<img src="https://img.shields.io/badge/language-C%2B%2B-red">

<h2 align="center"><i> Search for words in documents</i> | <i> Поиск слов в документах</i></h2>

# Description | Описание
<h3><p><img src="https://img.shields.io/badge/ENG-blue"></p>
<p>  A console application that searches for queries in documents.
The application is configured using JSON files.</p>
<p><img src="https://img.shields.io/badge/RUS-red"></p>
<p>Консольное приложение, которое выполняет поиск запросов в документах.
Настройка приложения выполняется с помощью файлов формата JSON.</p></h3>

# Technologies | Технологии
<p><img src="https://img.shields.io/badge/C%2B%2B-17-green?style=for-the-badge"></p>
<p><img src="https://img.shields.io/badge/CMake-3.24-green?style=for-the-badge"></p>
<p>https://cmake.org/</p>
<p><img src="https://img.shields.io/badge/nlohmann_json-3.11.3-green?style=for-the-badge"></p>
<p>https://github.com/nlohmann/json</p>
<p><img src="https://img.shields.io/badge/GoogleTest-1.15.2-green?style=for-the-badge"></p>
<p>https://github.com/google/googletest</p>

# Files | Файлы
<p><i>config.json</i>
  (Application configuration file | Файл настройки приложения)</p>
<ul>
  <li>name — the name of the application | название приложения</li>
  <li>version — version number | номер версии</li>
  <li>max_responses — maximum number of responses | максимальное количество ответов</li>
  <li>files - file paths to search for | пути к файлам для поиска</li>
</ul></p>
<p><i>requests.json</i>
  (Request file | Файл с запросами)</p>
<p><ul>
  <li>Maximum of 1000 requests | Не более 1000 запросов</li>
  <li>From one to ten words | От одного до десяти слов</li>
  <li>All words consist of lowercase Latin letters | Все слова состоят из строчных латинских букв</li>
</ul></p>
<p><i>answers.json</i>
(A file with responses to queries | Файл с ответами на запросы)</p>
<p><ul>
  <li>request - request number | номер запроса</li>
  <li>result – search result | результат поиска</li>
  <li>docid — document number | номер документа</li>
  <li>rank — search ranking | поисковый рейтинг</li>
</ul></p>
