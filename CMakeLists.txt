cmake_minimum_required(VERSION 3.10)

project(SistemaDeVoo)

# Defina o padrão do compilador
set(CMAKE_CXX_STANDARD 11)

# Incluir diretórios onde o Google Test está localizado
include_directories(external/googletest/googletest/include)

# Adicionar os arquivos do Google Test
add_subdirectory(external/googletest)

# Incluir os arquivos fonte do seu projeto
include_directories(src)

# Adicionar os arquivos de teste
file(GLOB TEST_FILES test/*.cpp)

# Criação do executável de teste
add_executable(run_tests ${TEST_FILES} src/tripulacao.cpp)

# Linkar o Google Test e o Google Mock com o projeto de testes
target_link_libraries(run_tests gtest gtest_main)

# Habilitar testes no CMake
enable_testing()

# Adicionar os testes
add_test(NAME tripulacao_tests COMMAND run_tests)
