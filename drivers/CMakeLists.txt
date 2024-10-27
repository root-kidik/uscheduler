set(TARGET_NAME_SUFFIX drivers)
set(TARGET_NAME ${PROJECT_NAME}_${TARGET_NAME_SUFFIX})

set(SRCROOT ${CMAKE_CURRENT_LIST_DIR})

set(STM32CUBEMX_GENERATED_FILES
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c 
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
  ${SRCROOT}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c 
  
	${SRCROOT}/Core/Inc/gpio.h
  ${SRCROOT}/Core/Inc/usart.h
  ${SRCROOT}/Core/Inc/main.h
  ${SRCROOT}/Core/Inc/stm32f1xx_hal_conf.h
  ${SRCROOT}/Core/Inc/stm32f1xx_it.h

	${SRCROOT}/Core/Src/gpio.c
  ${SRCROOT}/Core/Src/usart.c
  ${SRCROOT}/Core/Src/stm32f1xx_hal_msp.c
  ${SRCROOT}/Core/Src/stm32f1xx_it.c
  ${SRCROOT}/Core/Src/system_stm32f1xx.c

  ${SRCROOT}/startup_stm32f103xb.s
)

add_library(${TARGET_NAME} OBJECT ${STM32CUBEMX_GENERATED_FILES})
add_library(${PROJECT_NAME}::${TARGET_NAME_SUFFIX} ALIAS ${TARGET_NAME})

target_compile_definitions(${TARGET_NAME} PUBLIC 
  USE_HAL_DRIVER 
  STM32F103xB
)

target_include_directories(${TARGET_NAME} PUBLIC
  Core/Inc
  STM32F1xx_HAL_Driver/Inc
  CMSIS/Device/ST/STM32F1xx/Include
  CMSIS/Include
)

target_compile_options(${TARGET_NAME} PUBLIC
  -mcpu=cortex-m3
  -mthumb
  -mfloat-abi=soft

  -Wall
  -fdata-sections
  -ffunction-sections

  $<$<CONFIG:Debug>:-Og>
)

target_link_options(${TARGET_NAME} PUBLIC
  -T${SRCROOT}/STM32F103C8Tx_FLASH.ld
  -mcpu=cortex-m3
  -mthumb
  -mfloat-abi=soft

  -specs=nano.specs
  -specs=nosys.specs
  
  -lc
  -lm
  -lnosys

  -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.map,--cref
  -Wl,--gc-sections
)