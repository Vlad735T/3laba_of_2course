( ABOUT TEST )
make clean
make
./test_coverage

; Удалите все существующие файлы .gcda, чтобы gcov мог начать с чистого листа
find . -name "*.gcda" -exec rm -f {} \;



xdg-open coverage/index.html 
make coverage