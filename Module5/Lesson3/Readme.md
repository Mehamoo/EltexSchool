Программа kernelspace представляет собой модуль ядра, который взаимодействует с пространством пользователя через netlink. Пользовательская программа - userspace.

В папке screenshots расположен скриншот сборки модуля и клиентской программы (example_make.png) и примера работы (example_start.png).

Сборка: make
Очистка: make clean
Вставка модуля в ядро: insmod kernelspace.ko
Удаление модуля из ядра: rmmod kernelspace.ko 
Запуск пользовательской программы: ./userspace
