# Список

## Введение

Моя собственная структура данных, представляющая собой двухсвязнй список.

## Скачивание и установка проекта

Для установки программы используются утилиты `make` и `git`.

```CMake
    git clone git@github.com:ksshkh/list.git
    make
```

## Принцип работы

Список реализован с помощью массива, что существенно ускоряет выполнение операций с ним. Так, например, поиск n-ного элемента в линеаризованном списке осуществляется за o(1).

Также реализована визуализация списка с помощью Graphviz, что облегчает его отладку и работу с ним.

### Поддерживаемые функции

![overflow](./png_for_readme/first_list.svg)

1. Вставка элемента (как по физическому, так и по логическому адресу)

![overflow](./png_for_readme/second_list.svg)

2. Удаление элемента

![overflow](./png_for_readme/third_list.svg)

3. Swap двух любых элементов

![overflow](./png_for_readme/forth_list.svg)

4. Линеаризация

![overflow](./png_for_readme/fifth_list.svg)

5. Список автоматически реаллоцируется/аллоцируется в зависимости от количества элементов в нём