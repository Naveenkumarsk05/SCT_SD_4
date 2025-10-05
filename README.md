# E-commerce Product Data Extractor

A C++ program to extract product information (name, price, and rating) from e-commerce websites or generate sample data for demonstration purposes. The extracted data is saved into a CSV file.

---

## Features

- Extract product data from HTML using regex (requires `libcurl` for real websites).  
- Generate sample product data without internet (demo mode).  
- Save data into a CSV file (`products.csv`).  
- Display extracted products in the console.  

---

## Requirements

- C++ compiler (e.g., g++).  
- `libcurl` library (for URL extraction mode).  
- Standard C++ libraries (`iostream`, `fstream`, `string`, `vector`, `regex`, etc.).

---

## How to Compile

### If using URL extraction (requires `libcurl`):

```bash
g++ main.CPP -o extractor -lcurl
