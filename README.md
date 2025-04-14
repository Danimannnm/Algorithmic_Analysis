# Assignment 2: Advanced Algorithms and Data Structures in C++

## Contents
- **Q.1: d-Ary Heap Implementation (C++)**
  - Overview of a generic d-ary heap supporting both min-heap and max-heap configurations.
  - Key operations: insertion (bubble-up), extraction (bubble-down), bulk heap construction.
  - Time complexity analysis with supporting diagrams and tables.
  
- **Q.2: Enhanced Finite Automata String Matching with Wildcards (C++)**
  - Implementation of a finite automata string matching algorithm enhanced for wildcard support.
  - Transition tables and state diagrams for patterns (e.g., "a?ple" and "g?ape").
  - Detailed preprocessing and searching time complexity analysis.
  
- **Q.3: Garden Algorithms (C++)**
  - **Part (a):** Top k gardens algorithm using a max heap.
  - **Part (b):** Pseudocode and C++ implementation for extracting gardens exceeding a specified threshold.

## Files & Deliverables
- **Source Code:**
  - C++ implementation files: `dary_heap.cpp`, `string_matching.cpp`, `garden_algorithms.cpp`.
- **Report:**
  - `Report.pdf` containing comprehensive documentation, analysis, diagrams, and performance metrics.
- **Test Cases:**
  - CSV/JSON files with generated test cases, each labeled as Valid, Invalid, or Boundary.
- **Documentation:**
  - Additional diagrams, tables, and explanatory materials as referenced in the report.

## Requirements
- **Programming Language:** C++ (C++11 or later recommended)
- **Build Tools:**
  - A C++ compiler (e.g., `g++`, `clang++`)
  - CMake (optional for project management)
- **Libraries:**
  - Standard C++ libraries (no external libraries required unless specified)

## Compilation & Execution
1. **Clone the Repository:**
   ```bash
   git clone <repository-url>
   cd <repository-directory>
    ```
2. **Compile Code:**
  ```bash
     g++ -std=c++11 -o dary_heap dary_heap.cpp
     g++ -std=c++11 -o string_matching string_matching.cpp
  ```

3. **Run the executables:**
   ```bash
   ./dary_heap
   ./string_matching
    ```

## Output & Deliverables
- **Test Case Files:**  
  CSV files containing the generated test cases along with category labels (Valid, Invalid, Boundary).
- **Coverage Graph:**  
  A PNG file (`coverage_history.png`) displaying the GA’s progress in test coverage over generations (if applicable).
- **Terminal Output:**  
  Summaries including:
  - Generation count and achieved coverage percentage.
  - Counts of test cases in each category.
  - Comparison of GA performance vs. combined GA + local search.
 
  ## Report & Analysis
- An explanation of the fitness function design and chromosome representation choices.
- An analysis of parameter tuning (e.g., the impact of the 15% mutation rate).
- Detailed results including coverage metrics for valid, invalid, and boundary test cases.
- A comparison of the GA’s efficiency versus baseline random testing.
- Visualizations (e.g., line graphs) showing how the GA’s coverage improved over generations.

## Contributing
Contributions and improvements are welcome! To contribute:
1. Fork the repository and create a feature branch.
2. Follow the established coding style and directory structure.
3. Ensure your changes are well tested.
4. Submit a pull request with a detailed description of your modifications.

## License
This project is licensed under the MIT License.
