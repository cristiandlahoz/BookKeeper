# BookKeeper Library Management System

<div align="center">

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Console](https://img.shields.io/badge/Console-4D4D4D?style=for-the-badge&logo=windows-terminal&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

**Windows-Exclusive Console Library Management System**

*Comprehensive CRUD operations for books, authors, users, and loans with an intuitive CLI interface*

</div>

## <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/windows8/windows8-original.svg" width="24" height="24"/> Platform Requirements

> **This application is exclusively designed for Windows due to system-specific dependencies**

### System Architecture

```mermaid
graph TB
    A[BookKeeper.exe] --> B[Custom conio Library]
    A --> C[Windows File System]
    B --> D[Windows Console API]
    C --> E[C:\Windows\TEMP\]
    E --> F[USUARIOS.txt]
    E --> G[LIBROS.txt] 
    E --> H[AUTORES.txt]
    E --> I[PRESTAMO.txt]
    
    style A fill:#0078D6,stroke:#fff,stroke-width:2px,color:#fff
    style B fill:#00599C,stroke:#fff,stroke-width:2px,color:#fff
    style C fill:#4D4D4D,stroke:#fff,stroke-width:2px,color:#fff
```

## <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" width="24" height="24"/> Dependencies

### Custom conio Library
The application uses a custom `conio` implementation for Windows console operations:

| Component | Purpose | Location |
|-----------|---------|----------|
| <img src="https://simpleicons.org/icons/c.svg" width="16" height="16"/> `conio.h` | Header definitions | `lib/conio.h` |
| <img src="https://simpleicons.org/icons/c.svg" width="16" height="16"/> `conio.c` | Implementation | `lib/conio.c` |

**Key Functions:**
- `getch()` - Non-blocking keyboard input
- `clrscr()` - Screen clearing
- Color management and cursor positioning

### <img src="https://simpleicons.org/icons/microsoft.svg" width="20" height="20"/> Windows Compatibility Matrix

```mermaid
gantt
    title Windows Version Support
    dateFormat X
    axisFormat %s
    
    section Supported
    Windows XP     : 0, 1
    Windows 7      : 0, 1  
    Windows 8      : 0, 1
    Windows 10     : 0, 1
    Windows 11     : 0, 1
```

### File System Integration
Data persistence utilizes Windows system directories:

```
C:\Windows\TEMP\
├── AUTORES.txt    (Authors database)
├── LIBROS.txt     (Books database)  
├── USUARIOS.txt   (Users database)
└── PRESTAMO.txt   (Loans database)
```

## <img src="https://simpleicons.org/icons/visualstudiocode.svg" width="24" height="24"/> Installation & Compilation

### <img src="https://simpleicons.org/icons/github.svg" width="20" height="20"/> Quick Start

```bash
git clone https://github.com/cristiandelahooz/BookKeeper.git
cd BookKeeper
```

### Compilation Options

```mermaid
flowchart LR
    A[Source Code] --> B{Compilation Method}
    B -->|Option 1| C[Pre-compiled Executable]
    B -->|Option 2| D[GCC Command Line]
    B -->|Option 3| E[IDE Build]
    
    C --> F[BookKeeper.exe]
    D --> G[Custom Build]
    E --> H[IDE Output]
    
    F --> I[Ready to Run]
    G --> I
    H --> I
    
    style A fill:#f9f,stroke:#333,stroke-width:2px
    style I fill:#9f9,stroke:#333,stroke-width:2px
```

#### <img src="https://simpleicons.org/icons/windows.svg" width="16" height="16"/> Option 1: Pre-compiled Executable

```powershell
# Navigate to build directory
cd build
# Run the application
./BookKeeper.exe
```

#### <img src="https://simpleicons.org/icons/gnubash.svg" width="16" height="16"/> Option 2: Manual Compilation

```bash
# Compile with GCC
gcc -o BookKeeper BookKeeper.c lib/conio.c -std=c99

# Run the compiled executable  
./BookKeeper.exe
```

#### <img src="https://simpleicons.org/icons/visualstudio.svg" width="16" height="16"/> Option 3: IDE Compilation

**Supported IDEs:**
- Visual Studio
- Code::Blocks
- Dev-C++

**Project Setup:**
1. Create new C project
2. Add source files: `BookKeeper.c`, `lib/conio.c`, `lib/conio.h`
3. Set compiler standard to C99
4. Build and run

## <img src="https://simpleicons.org/icons/bookstack.svg" width="24" height="24"/> Features

The system provides comprehensive CRUD operations across four main entities:

### <img src="https://simpleicons.org/icons/readthedocs.svg" width="20" height="20"/> Entity Management

```mermaid
erDiagram
    LIBRO {
        string ISBN PK
        string titulo
        string editora
        string idautor FK
        date fechaedicion
        int edicion
    }
    
    AUTOR {
        string idautor PK
        string nombres
        string apellidos
        date fechanacimiento
    }
    
    USUARIO {
        string iddocumento PK
        string telefono
        string nombres
        string apellidos
    }
    
    PRESTAMOS {
        string iddocumento FK
        string ISBN FK
        date fecprestamo
        date fecdevolucion
        int diasprestamo
        float montoprestamo
        float recargodiario
    }
    
    AUTOR ||--o{ LIBRO : writes
    USUARIO ||--o{ PRESTAMOS : borrows
    LIBRO ||--o{ PRESTAMOS : borrowed_in
```

### Available Operations

| Entity | <img src="https://simpleicons.org/icons/plus.svg" width="16" height="16"/> Create | <img src="https://simpleicons.org/icons/book.svg" width="16" height="16"/> Read | <img src="https://simpleicons.org/icons/pencil.svg" width="16" height="16"/> Update | <img src="https://simpleicons.org/icons/trash.svg" width="16" height="16"/> Delete |
|--------|---------|------|---------|---------|
| **Books** | Add new books | List all books | Modify book details | Remove books |
| **Authors** | Register authors | View author list | Update author info | Delete authors |
| **Users** | Register users | List all users | Modify user data | Remove users |
| **Loans** | Issue new loans | View loan history | Update loan details | Delete loans |

### Data Persistence
- **Auto-save** functionality to Windows temp directory
- **File-based** storage system
- **Data integrity** through structured file formats

## <img src="https://simpleicons.org/icons/terminal.svg" width="24" height="24"/> User Interface

### Console Menu System

```mermaid
flowchart TD
    A[Main Menu] --> B[INGRESAR<br/>Add Records]
    A --> C[MODIFICAR<br/>Modify Records]  
    A --> D[ELIMINAR<br/>Delete Records]
    A --> E[LISTAR<br/>List Records]
    A --> F[GUARDAR<br/>Save Data]
    A --> G[DEVOLVER<br/>Return Books]
    A --> H[SALIR<br/>Exit Program]
    
    B --> I[Books/Authors/<br/>Users/Loans]
    C --> I
    D --> I  
    E --> I
    
    style A fill:#0078D6,stroke:#fff,stroke-width:2px,color:#fff
    style H fill:#dc3545,stroke:#fff,stroke-width:2px,color:#fff
    style F fill:#28a745,stroke:#fff,stroke-width:2px,color:#fff
```

### Navigation Controls

| Key | Function | Description |
|-----|----------|-------------|
| <img src="https://simpleicons.org/icons/keybase.svg" width="16" height="16"/> **Arrow Keys** | Navigation | Move through menu options |
| <img src="https://simpleicons.org/icons/keybase.svg" width="16" height="16"/> **Enter** | Select | Confirm menu selection |
| <img src="https://simpleicons.org/icons/keybase.svg" width="16" height="16"/> **Escape** | Exit | Return to previous menu |
| <img src="https://simpleicons.org/icons/keybase.svg" width="16" height="16"/> **Backspace** | Delete | Remove characters during input |

### Menu Options

- <img src="https://simpleicons.org/icons/plus.svg" width="16" height="16"/> **INGRESAR** – Add new records (Books, Authors, Users, Loans)
- <img src="https://simpleicons.org/icons/pencil.svg" width="16" height="16"/> **MODIFICAR** – Update existing record details
- <img src="https://simpleicons.org/icons/trash.svg" width="16" height="16"/> **ELIMINAR** – Remove records from the system
- <img src="https://simpleicons.org/icons/list.svg" width="16" height="16"/> **LISTAR** – Display all records by category
- <img src="https://simpleicons.org/icons/database.svg" width="16" height="16"/> **GUARDAR** – Persist changes to file system
- <img src="https://simpleicons.org/icons/undo.svg" width="16" height="16"/> **DEVOLVER** – Process book returns
- <img src="https://simpleicons.org/icons/x.svg" width="16" height="16"/> **SALIR** – Exit application

---

## <img src="https://simpleicons.org/icons/warning.svg" width="24" height="24"/> Important Notes

> **Windows-Only Limitation**: This application cannot run on macOS or Linux due to:
> - Windows-specific console API dependencies
> - Hard-coded Windows file system paths
> - Custom conio library requirements

**For cross-platform compatibility, significant code modifications would be required.**

