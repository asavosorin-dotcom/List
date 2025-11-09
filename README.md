# Сравнение скорости работы классического списка и списка из структуры массивов
## Ход работы
Для обеспечения полной производительности тесты проводим на зарядке, остановив все прочие программы, а так же отключим троттлинг процессора командой: "performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor" и "-fno-sanitize=address -fno-sanitize=undefined" для отключения Sanitizers
