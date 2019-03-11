cmake_minimum_required(VERSION 2.8.12)
project(zestaw1 C)
set(CMAKE_C_FLAGS "-std=gnu99")
set(CMAKE_C_STANDARD 99)

set(Optim -O2)
option(Optim0 OFF)
option(Optims OFF)

if (${Optim0})
    set(Optim -O0)
elseif (${Optims})
    set(Optim -Os)
else ()

endif ()

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
add_dependencies(dynamic shared_find)
TARGET_LINK_LIBRARIES(static static_find)
TARGET_LINK_LIBRARIES(shared shared_find ${CMAKE_DL_LIBS})
TARGET_LINK_LIBRARIES(dynamic dll ${CMAKE_DL_LIBS})

IF (${Test2})
    file(WRITE raport2.txt "Real\tUser\tSystem\tChildren user\tChildren system\n")
    set(outputfile raport2.txt)

    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Malo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/X11 xinitrc tmp search /var/log te* tmp output ${outputfile} write search insert tmp write insert remove 0 remove 1 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Srednio Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/ a* tmp search /var/ c tmp output ${outputfile} write search insert tmp search /etc/ a* tmp insert tmp write insert remove 0 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Duzo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search / xinitrc tmp search / t* tmp output ${outputfile} write search insert tmp write insert remove 0 write remove
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND echo "Dodaj/Usun bloki" >> ${outputfile}
            )
    add_custom_command(TARGET static POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/static 10 search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp output ${outputfile} write insert remove 0 remove 1 remove 2 remove 3 remove 4 remove 5 remove 6 write remove
            )
ENDIF()

IF (${Test3})
    set(outputfile raport3b)
    set(soutput raport3b)
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
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search /etc/X11 xinitrc tmp search /var/log te* tmp output ${soutput} write search insert tmp write insert remove 0 remove 1 write remove
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Srednio Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search /etc/ a* tmp search /var/ c tmp output ${soutput} write search insert tmp search /etc/ a* tmp insert tmp write insert remove 0 write remove
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Duzo Plikow" >> ${outputfile}
            )
    add_custom_command(TARGET ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search / xinitrc tmp search / t* tmp output ${soutput} write search insert tmp write insert remove 0 write remove
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
    add_custom_command(TARGET ${linktype}  POST_BUILD
            COMMAND echo "Dodaj/Usun bloki" >> ${outputfile}
            )
    add_custom_command(TARGET  ${linktype} POST_BUILD
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/${linktype} 10 search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp search /etc/X11 xinitrc tmp insert tmp search /var/log te* tmp insert tmp output ${soutput} write insert remove 0 remove 1 remove 2 remove 3 remove 4 remove 5 remove 6 write remove
            )
endforeach (linktype)
ENDIF()

unset(Optim)
unset(Test3)
unset(Test2)