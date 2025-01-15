# CycleDB

**CycleDB** — это простое приложение для работы с базой данных, реализованной на C++. Все данные хранятся в формате JSON, и взаимодействие с базой данных осуществляется через терминал.

## Описание

CycleDB — это приложение, предназначенное для хранения и обработки данных в формате JSON. Данные могут быть записаны, прочитаны, обновлены или удалены через командную строку. База данных хранит информацию в одном JSON-файле, который используется для всех операций с данными.

## Возможности

- Добавление новых записей.
- Чтение и поиск существующих записей.
- Обновление и удаление записей.
- Простое хранение данных в JSON-формате.

## Установка

1. Склонируйте репозиторий:

    ```bash
    git clone https://github.com/apchhui/CycleDB.git
    cd CycleDB
    ```

2. Скомпилируйте проект:

    Если у вас установлен C++ и CMake, выполните следующие команды:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

## Использование

После компиляции и сборки вы можете использовать приложение через командную строку.

### Запуск приложения:

```bash
./CycleDB
