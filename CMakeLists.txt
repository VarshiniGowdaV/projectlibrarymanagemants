cmake_minimum_required(VERSION 3.16)

project(projectlibrarymanagements LANGUAGES C)

add_executable(projectlibrarymanagements main.c
    admin.c
    admin.h
    borrowedbook.h
    book.h
    returnedbook.h
    staff.h
    student.h
    sortbyauthor.h
    sortbybookname.h
    book.c
    main1.h
    borrowedbook.c
    main1.c
    returnedbook.c
    sortbyauthor.c
    sortbybookname.c
    staff.c
    student.c
    filehanding.h
    filehanding.c)

include(GNUInstallDirs)
install(TARGETS projectlibrarymanagements
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
