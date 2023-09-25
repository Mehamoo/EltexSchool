Задание 3.8. На основе решения задачи 3.7 сделать
программу для двухстороннего обмена сообщениями
(персональный чат).

Задание 3.7. Написать две программы, использующие
очередь сообщений: первая отправляет строки в очередь,
а вторая – считывает и выводит на экран. Отправляемые
строки можно читать из файла или генерировать в
программе (например, случайные числа). Для завершения
обмена данными первая программа должна отправить
сообщение с типом 255.

===

В аргументах запуска необходимо указать номер клиента - 1 или 2, который впоследствии
будет указан в типе сообщения. 
В меню программы можно выбрать следующие действия:
1 - ввести сообщение;
2 - прочитать новые сообщения от другого клиента;
0 - выйти из программы.

===

Запуск с двух терминалов: 
./task3_3_8 1
./task3_3_8 2
Пример работы на рисунках example_usr1.png и example_usr2.png. Первый рисунок соответствует первому клиенту, прочитавшему сообщения второго. Второй рисунок соответствует второму клиенту, который первоначально ввёл три сообщения.