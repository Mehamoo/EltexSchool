Задание 3.11. Решить задачу 3.8 с использованием очередей POSIX.

Задание 3.8. На основе решения задачи 3.7 сделать программу для двухстороннего обмена сообщениями (персональный чат).

Задание 3.7. Написать две программы, использующие очередь сообщений: первая отправляет строки в очередь, а вторая – считывает и выводит на экран. Отправляемые строки можно читать из файла или генерировать в программе (например, случайные числа). Для завершенияобмена данными первая программа должна отправить сообщение с типом 255.

===

В аргументах запуска необходимо указать номер клиента - 1 или 2. 
Создаётся две очереди - для клиента 1 и 2.
В меню программы можно выбрать следующие действия:
1 - ввести сообщение (в очередь другого клиента);
2 - прочитать новые сообщения от другого клиента (из очереди текущего клиента);
0 - выйти из программы.

===

Запуск с двух терминалов: 
./task3_3_11 1
./task3_3_11 2
Пример работы на рисунках example_usr1.png и example_usr2.png. На первом рисунке клиент 1 отправляет сообщение второму клиенту и затем читает сообщение от него, на рисунке 2 наоборот, второй клиент сначала читает, потом отправляет.
