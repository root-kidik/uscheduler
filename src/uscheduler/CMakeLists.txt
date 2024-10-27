set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

set(SRC 
  ${SRCROOT}/Main.cpp

  ${INCROOT}/Task.hpp

  ${INCROOT}/Scheduler.hpp
  ${SRCROOT}/Scheduler.cpp

  ${INCROOT}/interface/IClock.hpp
  ${INCROOT}/interface/ITimerScheduler.hpp
  ${SRCROOT}/interface/ITimerScheduler.cpp

  ${INCROOT}/scheduler/TimerScheduler.hpp
  ${SRCROOT}/scheduler/TimerScheduler.cpp

  ${INCROOT}/STM32Clock.hpp
  ${SRCROOT}/STM32Clock.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}::drivers)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} verify exit reset"
)