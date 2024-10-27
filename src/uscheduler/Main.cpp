#include "main.h"

#include <chrono>

#include <uscheduler/Scheduler.hpp>
#include <uscheduler/STM32Clock.hpp>
#include <uscheduler/interface/ITimerScheduler.hpp>

#include "gpio.h"

uscheduler::Task Task1(uscheduler::interface::ITimerScheduler& timer_scheduler)
{
    for (;;)
    {
        co_await timer_scheduler.Delay(std::chrono::milliseconds{500});
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}

uscheduler::Task Task2(uscheduler::interface::ITimerScheduler& timer_scheduler)
{
    for (;;)
    {
        co_await timer_scheduler.Delay(std::chrono::milliseconds{1000});
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}

void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    uscheduler::STM32Clock clock;
    uscheduler::Scheduler scheduler{clock};
    scheduler.Run({Task1, Task2});
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
}
#endif
