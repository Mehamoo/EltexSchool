Задание 1.4. Написать программу, похожую на командный
интерпретатор. При запуске выводится приглашение, и
пользователь вводит имя и аргументы программы, которую
желает запустить. Программы для запуска находятся в том же
каталоге (например, программа для вычисления суммы
аргументов, «склеивания» строк, поиска наибольшего
значения или наибольшей длины строки и т.д.).

===

Программа запрашивает у пользователя имя программы и аргументы.
Аргументы записываются в динамический массив строк, под который выделяется память.
Запуск программы производится в дочернем процессе.
Программы, доступные для запуска - sumTwoArgs и maxFromTwoArgs, вычисляющие сумму двух аргументов и 
максимальный среди двух аргументов соответственно.

===

Запуск: ./task3_1_4
Пример работы на рисунке example.png.
