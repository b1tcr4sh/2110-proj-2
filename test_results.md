# Test Results: File loading - Rylee Ford

## Valid records, blank lines, comment lines, and records with too few or too many fields.
* Tested with facilities.txt:

        # FacilityID|FacilityName|BuildingName|Category
        F009|Room 205|Science Building|Classroom

        F010|research help desk|Library|Library|extra
        # this is a comment
        F011|library room

and buildings.txt:

        Library
        Student Union
        Science Building
        Engineering Building

        Gym
        # this is a comment
        Observatory

* command './proj2.out testdata'

* expected output:
    - facilities loads 1 and rejects 2, buildings loads 6 and rejects 0. 
    - Program continutes and is responsive.


* actual output:

        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 6
        Buildings rejected: 0

        Error: Could not open testdata/connections.txt
        Malformed Line: testdata/facilities.txt line 4: incorrect number or format of tokens.
        Malformed Line: testdata/facilities.txt line 6: incorrect number or format of tokens.

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 1
        Facilities rejected: 2
        ==== COLLISION DIAGNOSTIC ====
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 1
        Facilities Load Factor: 0.02

        Department already exists.
        Warning: Department Physics could not be added. line: 9

        ===== DEPARTMENT LOAD SUMMARY =====
        File: testdata/departments.txt
        Departments loaded: 7
        Departments rejected: 1

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. Search facility by name
        4. Search facility by category
        5. View campus graph
        6. Display graph counts and degrees
        7. Find reachable buildings (BFS)
        8. Find shortest path (BFS)
        9. Add department
        10. Search department
        11. Display department hierarchy
        12. Run preorder traversal
        13. Run postorder traversal
        14. Run level-order traversal
        15. Department statistics
        16. Facility category report
        17. Display graph connectivity report
        18. Exit

        > 

* program is still responsive and works as normal
* **Result: Passed**

## A missing file.
* tested on missing buildings.txt and:

* connections.txt:

        Library|Student Union
        Library|Business Building
        Student Union|Science Building
        Student Union|Gym
        Science Building|Engineering Building
        Business Building|Gym

* facilities.txt:

        F001|Main Reading Room|Library|Library
        F002|Tutoring Center|Library|Tutoring Center
        F003|Student Services Office|Student Union|Student Services Office
        F004|Computer Lab A|Science Building|Computer Lab
        F005|Room 101|Engineering Building|Classroom
        F006|Computer Lab B|Engineering Building|Computer Lab
        F007|Room 101|Business Building|Classroom
        F008|Fitness Center|Gym|Recreation
        F009|Room 205|Science Building|Classroom
        F010|Research Help Desk|Library|Library

* departments.txt:

        University|NONE
        College of Engineering|University
        College of Science|University
        Computer Science|College of Engineering
        Electrical Engineering|College of Engineering
        Mathematics|College of Science
        Physics|College of Science


* command './proj2.out testdata'

* expected output: 
    - buldings.txt produces an error first, then program continues to load files. 
    - All connections fail as there are no loaded buildings. 
    - All facilities are rejected because there are no loaded buildings. 
    - All departments load because they are unaffected by buildings. 
    - Program continues and is responsive.
* actual output:

        Error: Could not open testdata/buildings.txt
        testdata/connections.txt, line 2: Invalid or duplicate connection: Library | Student Union
        testdata/connections.txt, line 3: Invalid or duplicate connection: Library | Business Building
        testdata/connections.txt, line 4: Invalid or duplicate connection: Student Union | Science Building
        testdata/connections.txt, line 5: Invalid or duplicate connection: Student Union | Gym
        testdata/connections.txt, line 6: Invalid or duplicate connection: Science Building | Engineering Building
        testdata/connections.txt, line 7: Invalid or duplicate connection: Business Building | Gym

        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 0
        Connections rejected: 6

        Building does not exist: Library: line: 2
        Building does not exist: Library: line: 3
        Building does not exist: Student Union: line: 4
        Building does not exist: Science Building: line: 5
        Building does not exist: Engineering Building: line: 6
        Building does not exist: Engineering Building: line: 7
        Building does not exist: Business Building: line: 8
        Building does not exist: Gym: line: 9
        Building does not exist: Science Building: line: 10
        Building does not exist: Library: line: 11

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 0
        Facilities rejected: 10
        ==== COLLISION DIAGNOSTIC ====
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 0
        Facilities Load Factor: 0


        ===== DEPARTMENT LOAD SUMMARY =====
        File: testdata/departments.txt
        Departments loaded: 7
        Departments rejected: 0

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. Search facility by name
        4. Search facility by category
        5. View campus graph
        6. Display graph counts and degrees
        7. Find reachable buildings (BFS)
        8. Find shortest path (BFS)
        9. Add department
        10. Search department
        11. Display department hierarchy
        12. Run preorder traversal
        13. Run postorder traversal
        14. Run level-order traversal
        15. Department statistics
        16. Facility category report
        17. Display graph connectivity report
        18. Exit

        > 

* program is still responsive and works as normal
* **Result: Passed**

## Duplicate building names that differ only by capitalization, and duplicate facility IDs that differ only by capitalization.
* tested with buildings.txt:

        Library
        Observatory
        observatory

* connections.txt:

        Library|Observatory
        Library|observatory
        library|Observatory

* facilities.txt:

        F001|Main Reading Room|Library|Library
        F011|blahblah|library|Library
        F012|blahblahblah|observatory|Library
        f012|blahblahblah|observatory|Library

* command './proj2.out testdata'

* expected ouptput:
    - buildings load 2 and rejects 1. "observatory" is rejected as a duplicate.
    - connections loads 1 and rejects 2. The second and third lines are equivalent to the first and so reject because they are duplicate.
    - facilities loads 3 and rejects 1. The last line is rejected as a duplicate because ID is equivalent to the line above it.
    - departments throws and error and continues because file is missing.
    - Program continues and is responsive.

* actual output:

        testdata/buildings.txt, line 4: Duplicate building: observatory

        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 2
        Buildings rejected: 1

        testdata/connections.txt, line 3: Invalid or duplicate connection: Library | observatory
        testdata/connections.txt, line 4: Invalid or duplicate connection: library | Observatory

        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 1
        Connections rejected: 2

        Duplicate facility id: F012: line: 5

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 3
        Facilities rejected: 1
        ==== COLLISION DIAGNOSTIC ====
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 3
        Facilities Load Factor: 0.06

        Warning: File "testdata/departments.txt" failed to open.

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. Search facility by name
        4. Search facility by category
        5. View campus graph
        6. Display graph counts and degrees
        7. Find reachable buildings (BFS)
        8. Find shortest path (BFS)
        9. Add department
        10. Search department
        11. Display department hierarchy
        12. Run preorder traversal
        13. Run postorder traversal
        14. Run level-order traversal
        15. Department statistics
        16. Facility category report
        17. Display graph connectivity report
        18. Exit

        > 


* program is still responsive and works as normal
* **Result: Passed**

## Unknown building references (in connections and in facilities), duplicate and reversed connections, and unknown department parents.

* tested with buildings.txt:

        Library
        Observatory
        observatory

* connections.txt:

        Library|Observatory
        Library|Observatory
        Observatory|Library
        SomeBuilding|Library
        Library|SomeBuilding

* facilities.txt:

        F001|Main Reading Room|Library|Library
        F002|Telescope|Observatory|Equipment
        F003|blahblah|SomeBuilding|Equipment

* departments.txt: 

        University|NONE
        College of Engineering|University
        College of Science|UNT

* command './proj2.out testdata'

* expected output:
    - buildings will load 2 and reject 1. "observatory" will be rejected as a duplicate.
    - connections will load 1 and reject 4. Lines 2 and 3 will be functionally equivalent to line 1 and reject as duplicate. Lines 4 and 5 both reference a nonexistant building and will reject.
    - facilities will load 2 and reject 1. Lines 1 and 2 will load and line 3 will reject because "SomeBuilding" does not exist.
    - departments will load 2 and reject 1. Lines 1 and 2 will load, but line 3 will reject because parent "UNT" does not exist.
    - program continues and is responsive.

* actual output:

        testdata/buildings.txt, line 3: Duplicate building: observatory

        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 2
        Buildings rejected: 1

        testdata/connections.txt, line 2: Invalid or duplicate connection: Library | Observatory
        testdata/connections.txt, line 3: Invalid or duplicate connection: Observatory | Library
        testdata/connections.txt, line 4: Invalid or duplicate connection: SomeBuilding | Library
        testdata/connections.txt, line 5: Invalid or duplicate connection: Library | SomeBuilding

        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 1
        Connections rejected: 4

        Building does not exist: SomeBuilding: line: 3

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 2
        Facilities rejected: 1
        ==== COLLISION DIAGNOSTIC ====
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 2
        Facilities Load Factor: 0.04

        Warning: Department UNT not found. line: 3

        ===== DEPARTMENT LOAD SUMMARY =====
        File: testdata/departments.txt
        Departments loaded: 2
        Departments rejected: 1

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. Search facility by name
        4. Search facility by category
        5. View campus graph
        6. Display graph counts and degrees
        7. Find reachable buildings (BFS)
        8. Find shortest path (BFS)
        9. Add department
        10. Search department
        11. Display department hierarchy
        12. Run preorder traversal
        13. Run postorder traversal
        14. Run level-order traversal
        15. Department statistics
        16. Facility category report
        17. Display graph connectivity report
        18. Exit

        > 


* program continues and is still responsive.
*  **Result: Passed**

## A file with Windows line endings, extra whitespace around fields, a lowercase ID in a data file, and a # inside a name.

* tested with buildings.txt (with windows line endings):

        Library
         Student Union 
        business building

* connections.txt (with windows line endings):

         library |student union
        Library| Business Building 

* facilities.txt (with windows line endings):

        F001|  Main Reading Room#   |Student Union|Union
        F002 |#Tutoring Center| Business Building |Tutoring Center
         f003 |Checkout #Desk|Library| library 

* departments.txt (with windows line endings):

        University| NONE
         College of Engineering|University

* command './proj2.out testdata'


* expected output:
    - buidlings loads 3 rejects 0.
    - connections loads 2 rejects 0.
    - facilities loads 3 rejects 0.
    - departments loads 2 rejects 0.

* actual output:

        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 3
        Buildings rejected: 0


        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 2
        Connections rejected: 0


        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 3
        Facilities rejected: 0
        ==== COLLISION DIAGNOSTIC ====
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 3
        Facilities Load Factor: 0.06


        ===== DEPARTMENT LOAD SUMMARY =====
        File: testdata/departments.txt
        Departments loaded: 2
        Departments rejected: 0

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. Search facility by name
        4. Search facility by category
        5. View campus graph
        6. Display graph counts and degrees
        7. Find reachable buildings (BFS)
        8. Find shortest path (BFS)
        9. Add department
        10. Search department
        11. Display department hierarchy
        12. Run preorder traversal
        13. Run postorder traversal
        14. Run level-order traversal
        15. Department statistics
        16. Facility category report
        17. Display graph connectivity report
        18. Exit

        > 

* program continues and is still responsive.
*  **Result: Passed**

# Test Results: Hash Table and Search - Rylee Ford

## Successful, lowercase, invalid-format, and not-found ID searches.

* tested with facilities.txt:

        F001|Main Reading Room|Library|Library

* buildings.txt:

        Library

* command: './proj2.out testdata'
* chosen option: 2

* input 'F001'
    - *expected output:* record 'F001' is found.
    - *actual output:* outputs record successfully
* input 'f001'
    - *expected output:* record 'F001' is found.
    - *actual output:* outputs record successfully
* input '1232' 
    - *expected output:* format is invalid
    - *actual output:* "Invalid format: an ID is F followed by exactly three digits"
* input '1111' outputs:
    - *expected output:* input is malformed.
    - *actual output:* malformed input: 11111: input should be more than 0 characters and less than 4 characters.
* input 'F999' outputs:
    - *expected output:* record 'F999' is not found because it does not exist.
    - *actual output:* Not found: no facility with ID F999

* **Result: Passed**

## At least one hash collision, using your own collision test data directory and the HASH-7 diagnostic, and a duplicate-key insertion attempt (confirming that it does not change the collision count).
* test **case 1** facilities.txt:

        F009|Room 205|Science Building|Classroom
        F010|Research Help Desk|Library|Library
        F010|research help desk but fake!!!|Library|Library

    test **case 2** facilities.txt:

        F009|Room 205|Science Building|Classroom
        F010|Research Help Desk|Library|Library
        #F010|research help desk but fake!!!|Library|Library

* command: './proj2.out testdata'

* both yield the same collision count: 1
* **case 1 results:**
    - *expected output:* facilities loads 2 rejects 1. Line 3 rejects as duplicate. There is 1 collision because there is only 1 bucket.
    - *actual output:* 

        Duplicate facility id: F010: line: 3

        ===== FACILITY LOAD SUMMARY =====\
        File: testdata/facilities.txt\
        Facilities loaded: 2\
        Facilities rejected: 1\
        ==== COLLISION DIAGNOSTIC ====\
        Facility Collisions: 1\
        Number of Chains: 1\
        Number of Facilities Stored: 2\
        Facilities Load Factor: 2

* **case 2 results:**
    - *expected output:* facilities loads 2 and rejects 0. There is 1 collision because there is only 1 bucket.
    - *actual output:*

        ===== FACILITY LOAD SUMMARY =====\
        File: testdata/facilities.txt\
        Facilities loaded: 2\
        Facilities rejected: 0\
        ==== COLLISION DIAGNOSTIC ====\
        Facility Collisions: 1\
        Number of Chains: 1\
        Number of Facilities Stored: 2\
        Facilities Load Factor: 2

* **Result: Passed**




# Test Results: Graph and BFS – Rylan Smith

### Compilation

* Compiled the program using Visual Studio C++.
* Program compiled successfully with no errors.
* **Result: Passed**

### Loading Buildings

* Loaded buildings from `data/buildings.txt`.
* 7 buildings loaded and 0 rejected.
* **Result: Passed**

### Loading Connections

* Loaded connections from `data/connections.txt`.
* 6 connections loaded and 0 rejected.
* **Result: Passed**

### Graph Display

* Checked that all buildings displayed their connections correctly.
* Verified that Observatory displayed "(no connections)" because it has no connections.
* **Result: Passed**

### Graph Statistics

* Checked the total number of buildings and connections.
* Verified the degree of each building.
* Program displayed 7 buildings and 6 connections.
* All building degrees matched the expected results.
* **Result: Passed**

### BFS

* Ran BFS starting at Library.
* Checked that buildings displayed in the correct order and had the correct distances.
* Program showed 6 out of 7 buildings were reachable.
* **Result: Passed**

### Invalid BFS Starting Building

* Ran BFS starting with "Fake Building".
* Verified that the program displayed "Building not found."
* Confirmed that the program returned to the main menu without crashing.
* **Result: Passed**

### Case-Insensitive Search

* Tested BFS using "library" instead of "Library".
* Program still found the correct building and displayed the same results.
* **Result: Passed**

### Invalid Connections

* Tested self-connections, connections to buildings that don't exist, missing building names, and duplicate connections.
* Program rejected the invalid connections and displayed error messages with the line numbers.
* **Result: Passed**

### Shortest Path

* Tested the shortest path from the Library to the Engineering Building.
* Tested two buildings with multiple shortest routes to make sure the program followed the connection order.
* **Result: Passed**

### Shortest Path Edge Cases

* Tested starting and destination buildings that were the same.
* Verified that the program displayed 0 connections.
* Tested an unknown starting building and an unknown destination building.
* Tested buildings that had no path between them.
* Confirmed that the program displayed the correct error messages and did not crash.
* **Result: Passed**

### Graph Connectivity Report

* Tested the connectivity report using the campus building and connection data.
* Verified that the program displayed 7 buildings and 6 connections.
* Confirmed that Student Union had the highest degree of 3.
* Verified that Observatory was listed as an isolated building.
* Confirmed that the graph had 2 connected components.
* **Result: Passed**

### Menu Integration

* Added options to find the shortest path and display the graph connectivity report.
* Tested options 10, 11, and 12.
* Confirmed that the shortest path and connectivity report displayed correctly and that Exit closed the program.
* **Result: Passed**


# Test Results - Madison Lusk - Member C

## Department Load Summary

* loaded from departments from `departments.txt`
* 8 Departments loaded and 0 rejected

   * **Results: passed**

## Department Hierarchy

* Ran code to type the departments and then ran the code to display them in their hiearchy
* no issues in the leveling and they show correctly

* **Results: passed**

## Running Preorder traversal

* Ran the code that would place each department in it's pre order position
* No issues arised in the sorting
 * **Results: passed**

## Add Department with unknown parent or duplicate name

* tested with "history" in parent department

        Department name > Physics
        Parent department > history
        Department tree is empty.
        Parent department not found.

        ==== Campus Navigator ====
        1. View all facilities
        2. Search facility by ID
        3. View campus graph
        4. Display graph counts and degrees
        5. Find reachable buildings (BFS)
        6. Add department
        7. Search department
        8. Display department hierarchy
        9. Run preorder traversal
        10. Exit

    * **results: passed**    
