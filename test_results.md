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

# Test Results - Rylee Ford - Member A

## Valid records, blank lines, comment lines, and records with too few or too many fields.
* Tested with facilities.txt:\
    F001|name\
    F002|name|name|name

* output:

        Error: Could not open testdata/buildings.txt
        Error: Could not open testdata/connections.txt
        Malformed Line: testdata/facilities.txt line 1: incorrect number or format of tokens.

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 1
        Facilities rejected: 1
        Facility Collisions: 0
        Number of Chains: 50
        Number of Facilities Stored: 1
        Facilities Load Factor: 0.02

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

## A missing file.
* tested on empty directory passed to input.
* command './proj2.out testdata'

* output:

        Error: Could not open testdata/buildings.txt
        Error: Could not open testdata/connections.txt
        Warning: File "testdata/facilities.txt" failed to open.

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

## Unknown building references (in connections and in facilities), duplicate and reversed connections, and unknown department parents.

tbd

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
* tested with facilities.txt:\
    F009|Room 205|Science Building|Classroom\
    F010|Research Help Desk|Library|Library\
    F010|research help desk but fake!!!|Library|Library\
    F011|test|test|test

    and with the second F010 line commented out

* both yield the same collision count: 1
* but the duplicate case is handled with:

        Duplicate facility id: F010

        ===== FACILITY LOAD SUMMARY =====
        File: testdata/facilities.txt
        Facilities loaded: 3
        Facilities rejected: 1
        Facility Collisions: 1
        Number of Chains: 5
        Number of Facilities Stored: 3
        Facilities Load Factor: 0.6

* **Result: Passed**

# Test Results - Madison Lusk - Member C

## Empty File

* used an departments.txt file:

    Error: Could not open departments.txt/buildings.txt
    Error: Could not open departments/connections.txt
    Warning: File "departments.txt/facilities.txt" failed to open.
    Warning: File "departments.txt/departments.txt" failed to open.

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

   * **Results: passed**

## Malformed Line

* tbh

## Duplicate Record

*tbh

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
