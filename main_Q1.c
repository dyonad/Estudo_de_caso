#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

// Variável compartilhada para representar a temperatura em Celsius
float temperaturaCelsius = 25.0;

// Função para converter Celsius para Fahrenheit
float celsius_para_fahrenheit(float celsius) {
    return (celsius * 9 / 5) + 32;
}

// Tarefa 1: Leitura da variável compartilhada, adicionar 1.5 °C e imprimir o resultado
void Task1(void* pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(1000); // 1 Hz

    while (1) {
        temperaturaCelsius += 1.5;
        printf("Temperatura em Celsius: %.2f °C\n", temperaturaCelsius);
        vTaskDelay(xDelay);
    }
}

// Tarefa 2: Leitura da variável compartilhada, conversão para Fahrenheit e imprimir o resultado
void Task2(void* pvParameters) {
    const TickType_t xDelay = pdMS_TO_TICKS(500); // 2 Hz

    while (1) {
        float temperaturaFahrenheit = celsius_para_fahrenheit(temperaturaCelsius);
        printf("Temperatura em Fahrenheit: %.2f °F\n", temperaturaFahrenheit);
        vTaskDelay(xDelay);
    }
}

void main_Q1() {
    // Inicialização das tarefas
    xTaskCreate(Task1, "Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(Task2, "Task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Inicialização do scheduler
    vTaskStartScheduler();
}