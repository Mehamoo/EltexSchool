Задание 2.2. Изменить программы из задания 2.1 так,
чтобы использовался буферизованный ввод-вывод.

Задание 2.1. Написать 2 программы: первая
дописывает в файл строку, введенную пользователем. Вторая
выводит содержимое файла. Имя файла указывается в
параметрах запуска приложения. Использовать
небуферизованный ввод-вывод.

===

Программа file3_2_1_fileIn, пока пользователь из неё выйдет, запрашивает у пользователя строку и вписывает
её в указанный в аргументах запуска файл.
Программа file3_2_1_fileOut выводит содержимое указанного в аргументах запуска файла.
Путь к файлу прописывается так же пользователем при запуске.
Используется нуферизованный ввод-вывод.

===

Пример запуска: 
./task3_2_2_fileIn file.txt
./task3_2_2_fileOut file.txt
Пример работы на рисунке example.png.