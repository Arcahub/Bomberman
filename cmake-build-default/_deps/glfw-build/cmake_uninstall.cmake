
if (NOT EXISTS "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/glfw-build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/glfw-build/install_manifest.txt\"")
endif()

file(READ "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/glfw-build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/home/mathias/App/clion-2020.3.1/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/home/mathias/App/clion-2020.3.1/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

