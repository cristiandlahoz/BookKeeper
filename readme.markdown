# BootKeeper Library Management System

**Introduction**\
BootKeeper is a library management system developed in C that allows you to perform a wide range of operations on books, authors, users, and loans. It offers a Command Line Interface (CLI) with options for adding, modifying, deleting, listing, saving, and returning items within the system. The interface is simple, allowing for intuitive navigation and management of the library's data.

If you do not want to compile the code yourself, you can simply download the pre-compiled `BootKeeper.exe`, which includes all dependencies.

**Installing the conio Library**\
To use the BootKeeper Library Management System, you need to install a specific library called conio, which is provided in this repository. Unfortunately, this library is only compatible with Windows, so the system will not work on other operating systems.

**Supported Windows Versions for conio:**\
The `conio` library is specifically designed to interact with Windows systems. It is compatible with the following Windows versions:

- Windows XP
- Windows 7
- Windows 8
- Windows 10
- Windows 11

**Download the conio Library:**\
The conio library files are included in this repository. Make sure to download or clone the entire repository to your local machine.

**Include the conio Library in Your Project:**\
Ensure that the `conio.h` header file and the corresponding `conio.c` source file are in the same directory as your `BookKeeper.c` file. When including the library in your C code, use double quotes (`"conio.h"`) instead of angle brackets (`<conio.h>`), as it is a local file.

```c
#include "conio.h"
```

**Compilation Methods:**

1. **Using Pre-compiled Executable:**

   - Download the pre-compiled `BootKeeper.exe` from the repository.
   - Run `BootKeeper.exe` directly to start the application.

2. **Using GCC in Command Line:**

   - Open a command prompt and navigate to the directory containing `BookKeeper.c`, `conio.h`, and `conio.c`.
   - Use the following command to compile the BootKeeper system with the conio library:
     ```bash
     gcc -o BootKeeper BookKeeper.c conio.c -std=c99
     ```
   - After compilation, run the executable with:
     ```bash
     ./BootKeeper
     ```

3. **Using an IDE:**

   - Open your preferred IDE (e.g., Code::Blocks, Visual Studio).
   - Create a new project and add `BookKeeper.c`, `conio.h`, and `conio.c` to the project.
   - Ensure that the IDE is set to use the C99 standard.
   - Build and run the project from within the IDE.

4. **Alternative Compilation Without conio (For Non-Windows Systems):**

   - If you are using Linux or macOS, you will need to remove all references to `conio.h` from the code.
   - Modify `BookKeeper.c` to replace functions like `getch()` with standard input functions such as `getchar()`.
   - Compile with:
     ```bash
     gcc -o BootKeeper BookKeeper.c -std=c99
     ```

By following these steps, you will be able to compile and run the BootKeeper Library Management System on a Windows machine. If you encounter any issues, make sure that all files are correctly placed and that you have a compatible C compiler installed.

---

**Features**\
BootKeeper enables the following CRUD (Create, Read, Update, Delete) operations for various entities:

### Books

- **Add** new books to the library's database.
- **Modify** book details such as title, author, genre, and ISBN.
- **Delete** books from the library.
- **List** all books in the library's collection.
- **Save** changes to the book database.
- **Return** books that were previously checked out.

### Authors

- **Add** authors to the system.
- **Modify** details for existing authors.
- **Delete** authors.
- **List** all authors.
- **Save** author data to the database.

### Users

- **Register** new users of the library.
- **Modify** user information.
- **Delete** users.
- **List** all registered users.
- **Save** user data to the system's database.

### Loans

- **Issue** new loans by associating books with users.
- **Modify** details of existing loans.
- **Delete** loans.
- **List** all loans in the system.
- **Return** books through the loan management system.

---

**Interface**\
The main menu offers the following options:

- **INGRESAR** – Add a new record.
- **MODIFICAR** – Update an existing record.
- **ELIMINAR** – Remove a record.
- **LISTAR** – View all records of a category.
- **GUARDAR** – Save changes to the database.
- **DEVOLVER** – Return a borrowed book.
- **SALIR** – Exit the program.

Each option corresponds to a CRUD operation on books, authors, users, and loans, providing a streamlined user experience for managing library data.

---

