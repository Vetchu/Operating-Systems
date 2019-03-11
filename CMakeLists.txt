cmake_minimum_required(VERSION 3.13)
project(zestaw1 C)

set(CMAKE_C_STANDARD 99)

if (NOT Optim)
    set(Optim -O2)
endif ()

option(Optim "Optim" -O2)
option(Test2 "Test2")
option(Test3 "Test3")

set(sources zad2/main.c)
add_executable(static ${sources})
set_target_properties(static PROPERTIES COMPILE_FLAGS "-Wall ${Optim}")
add_executable(shared ${sources})
set_target_properties(shared PROPERTIES COMPILE_FLAGS "-Wall -ldl ${Optim}")
add_executable(dynamic ${sources})
set_target_properties(dynamic PROPERTIES COMPILE_FLAGS "-Wall -D DLL -ldl ${Optim}")

add_library(static_find STATIC zad1/lib.c)
add_library(shared_find SHARED zad1/lib.c)
add_library(dll SHARED zad3a/libdll.c)
TARGET_LINK_LIBRARIES(static static_find)
TARGET_LINK_LIBRARIES(shared shared_find ${CMAKE_DL_LIBS})
TARGET_LINK_LIBRARIES(dynamic dll ${CMAKE_DL_LIBS})

IF (${Test2})
    file(WRITE zad2/raport2.txt "Real\tUser\tSystem\tChildren user\tChildren system\n")
    set(outputfile zad2/raport2.txt)

    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Malo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/X11 xinitrc tmp search /var/log te* tmp output 2.txt write search insert write insert remove 0 remove 1 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Srednio Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/ a* tmp search /var/ c tmp output 2.txt write search insert search /etc/ a* tmp insert write insert remove 0 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Duzo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search / xinitrc tmp search / t* tmp output 2.txt write search insert write insert remove 0 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Dodaj/Usun bloki" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/X11 xinitrc tmp insert search /var/log te* tmp insert search /etc/X11 xinitrc tmp insert search /var/log te* tmp insert search /etc/X11 xinitrc tmp insert search /var/log te* tmp insert output 2.txt write search remove 0 remove 1 remove 2 remove 3 remove 4 remove 5 remove 6 write remove
            )
ENDIF()

IF (${Test3})
    set(outputfile raport3b)
    set(soutput 3b)
    file(WRITE ${outputfile} TestOptimizeLevel=${Optim}\n)
    file(APPEND ${outputfile} "Real\tUser\tSystem\tChildren user\tChildren system\n")

    foreach (linktype static shared dynamic)
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "TEST ${linktype}" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Malo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search /etc/X11 xinitrc search /var/log te* output ${soutput} write search insert write insert remove 0 remove 1 write removed
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Srednio Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search /etc/ a* search /var/ c output ${soutput} write search insert search /etc/ a* insert write insert remove 0 write removed
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Duzo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search / xinitrc search / t* output ${soutput} write search insert write insert remove 0 write removed
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Dodaj/Usun bloki" >> ${outputfile}
            )
    add_custom_command(TARGET  ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 output ${soutput} search /etc/X11 xinitrc insert search /var/log te* insert search /etc/X11 xinitrc insert search /var/log te* insert search /etc/X11 xinitrc insert search /var/log te* insert write insert remove 0 remove 1 remove 2 remove 3 remove 4 remove 5 remove 6 write remove
            )
endforeach (linktype)
ENDIF()

unset(Optim)
unset(Test3)
unset(Test2)