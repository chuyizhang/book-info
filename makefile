bookInfo : main.cpp database.cpp
	g++ -o bookInfo main.cpp database.cpp menu.cpp operate.cpp -l sqlite3 -std=c++1z

clean :
	rm bookInfo
