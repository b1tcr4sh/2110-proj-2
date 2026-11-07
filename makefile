proj2.out : main.o
	g++ -Wall main.o Files.o CampusGraph.o Facility.o FacilityChain.o FacilityTable.o -o proj2.out

Files.o: include/Files.h src/Files.cpp
	g++ -Wall -c include/Files.h src/Files.cpp

CampusGraph.o: include/CampusGraph.h src/CampusGraph.cpp
	g++ -Wall -c include/CampusGraph.h src/CampusGraph.cpp

Facility.o: include/Facility.h src/Facility.cpp
	g++ -Wall -c include/Facility.h src/Facility.cpp

FacilityChain.o: Facility.o include/FacilityChain.h src/FacilityChain.cpp
	g++ -Wall -c include/FacilityChain.h src/FacilityChain.cpp

FacilityTable.o: Files.o FacilityChain.o include/FacilityTable.h src/FacilityTable.cpp
	g++ -Wall -c include/FacilityTable.h src/FacilityTable.cpp

main.o: FacilityTable.o CampusGraph.o src/main.cpp
	g++ -Wall -c src/main.cpp

clean:
	rm include/*.gch *.o proj2.out