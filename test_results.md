# Test Results – Rylan Smith - Member B

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

# Test Results - Rylee Ford - Member A

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

* expected output: facilities loads 1 and rejects 2, buildings loads 6 and rejects 0. Program continutes and is responsive.


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

* expected output: buldings.txt produces an error first, then program continues to load files. All connections fail as there are no loaded buildings. All facilities are rejected because there are no loaded buildings. All departments load because they are unaffected by buildings. Program continues and is responsive.
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
* tested with facilities.txt:\
    f001|name|name|name\
    F001|Name|Name|Name\
    F002|name|name|name

* output:

        Error: Could not open testdata/buildings.txt
        Error: Could not open testdata/connections.txt
        Duplicate facility id: F001

        ===== FACILITY LOAD SUMMARY =====

        File: testdata/facilities.txt
        Facilities loaded: 2
        Facilities rejected: 1
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 2
        Facilities Load Factor: 0.04

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

* program is still responsive and works as normal
* **Result: Passed**

## Unknown building references (in facilities)
* tested with facilities.txt:\
    F001|Main Reading Room|willis library|Library\
    F002|Tutoring Center|Library|Tutoring Center

* output: 
        
        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 7
        Buildings rejected: 0

        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 6
        Connections rejected: 0

        Building does not exist: willis library: line: 2

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 1
        Facilities rejected: 1
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 1
        Facilities Load Factor: 0.02

and buildings.txt:

        Library

* program succesfuly rejects facility iwth "willis library" entry and works as normal
*  **Result: Passed**

## Successful, lowercase, invalid-format, and not-found ID searches.
* tested with 'F001' outputs record successfully
* tesetd with 'f001' outputs same record successfully
* tested with '1232' outputs:\
    Invalid format: an ID is F followed by exactly three digits
* tested with '1111' outputs:\
    malformed input: 11111: input should be more than 0 characters and less than 4 characters.
* tested with 'F999' outputs:\
    Not found: no facility with ID F999

* **Result: Passed**

## At least one hash collision, using your own collision test data directory and the HASH-7 diagnostic, and a duplicate-key insertion attempt (confirming that it does not change the collision count).
* tested with facilities.txt:

        F009|Room 205|Science Building|Classroom
        F010|Research Help Desk|Library|Library
        F010|research help desk but fake!!!|Library|Library

    and 

        F009|Room 205|Science Building|Classroom
        F010|Research Help Desk|Library|Library
        #F010|research help desk but fake!!!|Library|Library


* both yield the same collision count: 1
* the duplicate (first) case outputs:

        Duplicate facility id: F010: line: 4

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 2
        Facilities rejected: 1
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 2
        Facilities Load Factor: 0.04

* and the commented out (second) case outputs:

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 2
        Facilities rejected: 0
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 2
        Facilities Load Factor: 0.04

* **Result: Passed**

## Empty files
* tested with an empty ./testdata directory

* output:

        Error: Could not open testdata/buildings.txt
        Error: Could not open testdata/connections.txt
        Warning: File "testdata/facilities.txt" failed to open.
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

* prgoram is responsive and proceeds as normal
* **Result: Passed**


## Empty required fields
* tested with facilities.txt:

        F001| | | 
        F002|Tutoring Center|Library|Tutoring Center

* buldings.txt:

        Library
        Business Building

* connections.txt:

        Library| 
        Library|Business Building

* departments.txt:

        University|NONE
        College of Engineering|
        College of Science|University

* output:

        ===== BUILDING LOAD SUMMARY =====
        File: testdata/buildings.txt
        Buildings loaded: 2
        Buildings rejected: 0

        testdata/connections.txt, line 2: Missing building name.

        ===== CONNECTION LOAD SUMMARY =====
        File: testdata/connections.txt
        Connections loaded: 1
        Connections rejected: 1

        Warning: Entry has empty field: line 2

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 1
        Facilities rejected: 1
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 1
        Facilities Load Factor: 0.02

        Warning: Entry has empty field: line 3

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

* all correct fields are loaded and all malformed ones are rejected
* **Result: Passed**

## A file with Windows line endings, extra whitespace around fields, a lowercase ID in a data file, and a # inside a name.




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

        Preorder Traversal:
        - University
        - College of Engineering
        - Computer Science
        - Electrical Engineering
        - College of Science
        - Mathmatics
        - Physics

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

## Postorder and level-order traversals; department statistics for an empty tree, a root-only tree, and the sample tree.

* Postorder Traversal Output

        Postorder Traversal:
        - Computer Science
        - Electrical Engineering
        - College of Engineering
        - Mathmaticas
        - Physics
        - College of Science
        - University

* **results: passed**

* Level-Order Traversal Output

        Level-Order Traversal:
        - University
        - College of Engineering
        - College of Science
        - Computer Science
        - Electrical Engineering
        - Mathematics
        - Physics

* **results: passed**


* Department Statistics with an empty tree

        No departments are loaded.
        Total departments: 0
        Leaf departments: 0
        Tree height: N/A

* **results: passed**

* Department Statistics with a root-only tree

* Department Statisitcs with the sample tree:

         ======== Department Statistics ========
         Total Department: 7
         Leaf Departments: 4
         Tree Height: 2

* **results: passed**