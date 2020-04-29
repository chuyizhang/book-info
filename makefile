bookInfo : main.cpp database.cpp
	g++ -o bookInfo main.cpp database.cpp menu.cpp operate.cpp -l sqlite3

clean :
	rm bookInfo
