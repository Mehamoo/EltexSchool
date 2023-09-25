Задание 3.9. На основе решения задачи 3.8 сделать групповой чат. Клиенты подключаются к серверу, и сервер готов пересылать сообщения. Клиент отправляет сообщение серверу. Сервер дополняет текст сообщения идентификатором клиента, и рассылает всем это сообщение.

Задание 3.8. На основе решения задачи 3.7 сделать программу для двухстороннего обмена сообщениями (персональный чат).

Задание 3.7. Написать две программы, использующие очередь сообщений: первая отправляет строки в очередь, а вторая – считывает и выводит на экран. Отправляемые строки можно читать из файла или генерировать в программе (например, случайные числа). Для завершения обмена данными первая программа должна отправить сообщение с типом 255.

===

Клиентская программа - task3_3_9_client, серверная - task3_3_9_server.
Одновременно может быть подключено 16 пользователей.
В аргументах запуска клиентского приложения необходимо указать номер пользователя (от 2 до 17) и его имя.
Сервер запоминает имя пользователя и впоследствии подставляет его перед сообщением.
Для завершения работы серверного приложения необходимо запустить клиентское с номером пользователя 1.

Проблемы:
1) Клиент не проверяет и не уведомляет пользователя запущен ли сервер. В случае отключенного сервера сообщения клиентов 
не доходят друг до друга;
2) Возможен запуск нескольких клиентов под одним номером пользователя, при этом имя пользователя будет равно
имени пользователя последнего запущенного клиента.

===

Пример запуска с одного или нескольких терминалов: 
./task3_3_9_server &
./task3_3_9_client 2 Mike
./task3_3_9_client 3 Bob
./task3_3_9_client 4 Petr

Пример работы на рисунках example_firstCls.png и example_secondCls.png. На первом рисунке запускается сервер в фоновом режиме,
клиенты с именами Mike и Bob. Mike отправляет сообщение, Bob его читает и отправляет своё сообщение. На втором рисунке подключается клиент с именем Petr и читает сообщения Mike и Bob.