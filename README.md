# BootKeeper Library Management System

<div style="background:#FFFFE0;padding:20px;color:#000000;margin-top:10px;">

  
**Introduction**  
BootKeeper is a library management system developed in C that allows you to perform a wide range of operations on books, authors, users, and loans. It offers a Command Line Interface (CLI) with options for adding, modifying, deleting, listing, saving, and returning items within the system. The interface is simple, allowing for intuitive navigation and management of the library's data.

If you do not want to compile the code yourself, you can simply download the pre-compiled `BootKeeper.exe`, which includes all dependencies.

</div>

---

<div style="background:#FFFFE0;padding:20px;color:#000000;margin-top:10px;">

  
**Features**  
BootKeeper enables the following CRUD (Create, Read, Update, Delete) operations for various entities:
</div>

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

<div style="background:#FFFFE0;padding:20px;color:#000000;margin-top:10px;">

  
**Interface**  
The main menu offers the following options:
</div>

- **INGRESAR** – Add a new record.
- **MODIFICAR** – Update an existing record.
- **ELIMINAR** – Remove a record.
- **LISTAR** – View all records of a category.
- **GUARDAR** – Save changes to the database.
- **DEVOLVER** – Return a borrowed book.
- **SALIR** – Exit the program.

Each option corresponds to a CRUD operation on books, authors, users, and loans, providing a streamlined user experience for managing library data.

---

<div style="background:#FFFFE0;padding:20px;color:#000000;margin-top:10px;">

  
**Compilation**  
To compile BootKeeper from the source code, ensure you have a C compiler (such as `gcc`) installed on your system. Use the following command to compile:
</div>

```bash
gcc -o BootKeeper BookKeeper.c -std=c99
```
