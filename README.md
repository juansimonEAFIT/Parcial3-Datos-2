# Parcial3-Datos-2

## Group Members:
  - Lucas Higuita.
  - Juan Simón Ospina.
  - Santiago Gómez.
  - Miguel Ángel Ortiz.

## Operating System:
  - Microsoft Windows.
  - Windows 11 Home.
  - Linux Ubuntu.

## Programming Language:
  - C++

## Tools:
  - Visual Studio Code.

## Implementations:
  - None.

## Requirements:
Before running the program, ensure you have:
  - C++ installed.
  - An IDE or text editor such as Visual Studio Code to run the Python code.

---

## Instructions:

### Clone or Download the Repository:

#### Cloning:
Clone the repository to your local machine with the following command:
```bash
git clone <repository-url>
```
#### Downloading:
  - Click the green "Code" button at the top of the repository.
  - Select "Download ZIP".
  - Extract the ZIP file on your local machine.

---

## Running the Code:
The code works as a SQL simulator. The actions to be performed work with SQL language statements.
The functions that we implement in the code are CREATE TABLE, INSERT INTO, SELECT, UPDATE and DELETE.

---
## Explanation of the Inputs.
The inputs are based on SQL statements, below you will find the structure of all of them and examples of each one.

### CREATE TABLE
```bash
CREATE TABLE table_name (nameColumn1, nameColumn2, ..., nameColumnN);
```
##### EXAMPLE
```bash
CREATE TABLE Clientes (ID, Nombre, Edad, Ciudad)
```

### INSERT INTO
```bash
INSERT INTO table_name (column1, column2, ..., columnN) VALUES (value1, value2, ..., valueN);
```
##### EXAMPLE
```bash
INSERT INTO Clientes (ID; Nombre, Edad, Ciudad) VALUES (1, Juan, 32, CDMX)
```

### SELECT
```bash
SELECT (column1, column2, ..., columnN) FROM table_name WHERE condition;
```
##### EXAMPLE (1)
```bash
SELECT (ID, Nombre, Edad, Ciudad) FROM Clientes
```
##### EXAMPLE (2)
```bash
SELECT (ID, Nombre, Edad, Ciudad) FROM Clientes WHERE ID=1
```

### UPDATE
```bash
UPDATE table_name SET column1 = value1, column2 = value2, ... WHERE condition;
```
##### EXAMPLE
```bash
UPDATE Clientes SET Edad=32 WHERE ID=1
```

### DELETE
```bash
DELETE FROM table_name WHERE condition;
```
##### EXAMPLE
```bash
DELETE FROM Clientes WHERE Ciudad=CDMX
```
