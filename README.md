# E-commerce Product Data Extractor

A C++ program to extract product information (name, price, and rating) from e-commerce websites or generate sample data for demonstration purposes. The extracted data is saved into a CSV file.

## Features
- Extract product data from HTML using regex (requires `libcurl` for real websites).  
- Generate sample product data without internet (demo mode).  
- Save data into a CSV file (`products.csv`).  
- Display extracted products in the console.  

## Requirements
- C++ compiler (e.g., g++).  
- `libcurl` library (for URL extraction mode).  
- Standard C++ libraries (`iostream`, `fstream`, `string`, `vector`, `regex`, etc.).

## How to Compile
If using URL extraction (requires `libcurl`):
g++ main.CPP -o extractor -lcurl

If using only sample data (no `libcurl` needed):
g++ main.CPP -o extractor

## How to Run
./extractor

1. Program asks for mode selection:  
   - 1 – Extract from URL (requires internet and `libcurl`).  
   - 2 – Use sample product data (demo mode).  
2. If using mode 1, enter the e-commerce website URL.  
3. Program downloads HTML (mode 1) or generates sample data (mode 2).  
4. Extracted product data is displayed in the console and saved in `products.csv`.

## CSV Output
The CSV file `products.csv` has the following format:

Product Name,Price,Rating  
Wireless Bluetooth Headphones,49.99,4.5  
Smart Watch Pro,199.99,4.7  
USB-C Charging Cable,12.99,4.2  
...

## Notes
- Regex patterns are examples and may need adjustments depending on website structure.  
- For websites with complex HTML or dynamic content, consider using an HTML parser.  
- Sample data mode is provided for testing without network connectivity.

## Example Output
=== Extracted Products ===  
1. Wireless Bluetooth Headphones - $49.99 - Rating: 4.5/5  
2. Smart Watch Pro - $199.99 - Rating: 4.7/5  
3. USB-C Charging Cable - $12.99 - Rating: 4.2/5  
...  
Data successfully saved to products.csv

## Author
Naveen Kumar S K  
[GitHub Profile](https://github.com/Naveenkumarsk05)

## Workflow Diagram
[URL / Sample Data]  
        |  
        v  
   [HTML / Generated Data]  
        |  
        v  
  [Regex Extraction / Sample Parsing]  
        |  
        v  
 [Vector<Product> Storage]  
        |  
        v  
  [Display in Console + CSV File]
