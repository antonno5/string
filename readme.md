## Задача String

### Зависимости

#### Для сборки проекта

* `cmake`
* `make`
* компилятор с++, поддерживающий c++20

#### Для полноценного тестирования

* `g++`
* `clang++`
* `clang-tidy`

### Как работать с репозиторием

Чтобы скрипты репозитория работали корректно, запустите `init.sh`.

`build.sh`          - собрать проект

`test.sh`           - собрать двумя компиляторами, прогнать тесты и проверить кодстайл

После запуска `test.sh` появятся два файла с логами:

`last_log`          - вывод всех этапов тестирования: компиляторов, тестов и кодстайл проверок

`last_stage_log`    - вывод последнего этапа тестирования. Полезно смотреть, если тесты провалились - там будет ошибка

Менять файлы `test.sh`, `test.cpp`, `TestLib.hpp`, `CMakeLists.txt`, `build.sh`, `.clang-format`, `.clang-tidy`, `checksums` ___запрещено___


Впишите сюда ссылку на посылку в яндекс-контесте, которая получила статус AC.

Посылка:
https://contest.yandex.ru/contest/41270/run-report/73444277/


