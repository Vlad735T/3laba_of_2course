( ABOUT TEST )

make
make clean
make run-tests
make coverage
./test_coverage


; Удалите все существующие файлы .gcda, чтобы gcov мог начать с чистого листа
find . -name "*.gcda" -exec rm -f {} \;



xdg-open coverage/index.html 
