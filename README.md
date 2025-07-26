# Project Report: Data Extraction Tool

## Company: NovaNectar Services Pvt. Ltd.
Author: Mark L F Tlau

Date: July 27, 2025

### Project Overview
The objective of this project was to develop a robust, command-line based utility in C for extracting business contact information. The tool is designed to take a user-defined search query (e.g., "cafes in Delhi"), query the Google Places API for relevant data, and then parse the resulting JSON response to produce a structured Comma-Separated Values (.csv) file.
The core functionality revolves around providing a simple yet powerful interface for users to generate lead lists or data sets containing key business information, such as display names, addresses, locations, and Google Maps URIs, directly from their terminal. The program is built with a focus on performance, modularity, and correct memory management, leveraging standard C libraries and the libcurl library for network communication.

### Duration
The project was developed over a period of 2.5 weeks, from 10-7-2025 to 27-7-2025. This timeframe encompassed initial research, requirements analysis, implementation, debugging, and final documentation.

### Outcome
The project was successfully completed, resulting in a fully functional C application (places_tool) that meets all core requirements.
Key Features Delivered:

1. User-Friendly CLI: The application prompts the user for an API key (and saves it for future use) and a search query.

2. API Integration: Successfully communicates with the Google Places API via HTTP POST requests using libcurl, sending structured JSON queries.

3. Custom JSON Parser: A bespoke, lightweight parser (simpleparse.c) was developed to process the JSON response. It isolates each "place" object from the main array and extracts values for predefined keys.

4. Structured Data Export: The parsed data is organized into a CsvLine struct and then written to two .csv files: a general latest-results.csv and a query-specific file (e.g., cafes in Delhi.csv).

5. Formatted Console Output: In addition to the CSV files, the application displays the extracted data in a neatly formatted table in the console for immediate review.

6. Modular Codebase: The project is organized into logical modules with clear header files (places.h, simpleparse.h, file.h), promoting readability and maintainability.

### Challenges Faced
The development process involved several significant technical challenges that required critical analysis and strategic pivots.

1. Initial Approach: Web Scraping: The initial project description suggested a web scraping approach to extract data from a Google Maps link. An early-stage analysis revealed this to be fundamentally impractical and unreliable in C. Google Maps is a dynamic JavaScript application, and scraping it would require a full browser engine, which is beyond the scope of a C project. Furthermore, this method is brittle (prone to breaking with any UI change) and violates Google's Terms of Service.

2. Strategic Pivot to API Usage: The most critical challenge was successfully arguing for a change in approach. After research, it was determined that the official Google Places API was the correct, professional, and robust solution. This pivot, while a deviation from the original plan, ensured the final tool would be stable, efficient, and legitimate.

4. Memory Management in C: The core of the project's complexity lay in manual memory management.

5. Dangling Pointers: Early iterations of the parser suffered from segmentation faults due to shallow copying. Pointers within the final CsvLine structs were incorrectly pointing to temporary buffers that were freed prematurely. This was solved by implementing a deep copy strategy, using functions like strdup to ensure each data structure owned its own memory.

6. Memory Leaks: Ensuring that every malloc and strdup had a corresponding free was a constant challenge. A disciplined approach was required, especially in the main loop where data for each place was allocated and then had to be meticulously freed after being written to the file.

7. Building a Resilient Parser: Creating a JSON parser from scratch, even a simplified one, was a significant hurdle. The initial version, which relied on counting braces, was found to be too fragile. The final parser, while still specialized, was made more robust to handle variations in whitespace and line breaks within the JSON response, though it still assumes a consistent key-value structure.

### Conclusion
The Data Extraction Tool project was a success, delivering a functional and performant C application that fulfills the core need of automated data gathering. More importantly, it was an invaluable learning experience in backend systems programming.
The journey from a flawed web scraping concept to a stable API-based solution highlights the importance of proper technical analysis before implementation. The project provided deep, practical experience in C programming's most challenging aspects: robust network communication with libcurl, the intricacies of manual memory management, and the logic of data parsing and manipulation. The final result is a testament to the power of C for creating efficient, controlled, and powerful command-line utilities.
