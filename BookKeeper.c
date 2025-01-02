#include "conio.c"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DERECHA 12
#define IZQUIERDA 11
#define ARRIBA 72
#define ABAJO 80

#define ESC 27
#define ENTER 13
#define BKSP 8
#define PUNTO 46
#define ESP 32
#define NUMEROS_FECHA 8

#define STR_FECHA 10
#define SHOW_MU 7
#define SHOW_RESP 2
#define SHOW_STRUCTS 4
#define SHOW_SCROLL 4
#define SHOW_M_AUTOR -3 // M de modificar
#define SHOW_M_USUARIO -2
#define SHOW_M_LIBRO -1

#define COL_OPCIONS 14

#define LENISBN 14
#define LENTITULO 51
#define LENEDIT 81
#define LENIDAUTOR 11
#define LENNOMB 41
#define LENAPEL 36
#define LENIDDOC 21
#define LENTELEFONO 13

#define CANTINI 2
#define CANTINC 3

#define ARCH_AT "C:\\Windows\\TEMP\\AUTORES.txt"
#define ARCH_LB "C:\\Windows\\TEMP\\LIBROS.txt"
#define ARCH_USR "C:\\Windows\\TEMP\\USUARIOS.txt"
#define ARCH_PRT "C:\\Windows\\TEMP\\PRESTAMO.txt"

typedef struct {
  unsigned short int dd, mm, yyy;
} FECHA;

typedef struct {
  char ISBN[LENISBN];
  char titulo[LENTITULO];
  char editora[LENEDIT];
  char idautor[LENIDAUTOR];
  FECHA fechaedicion;
  int edicion;
} LIBRO;

typedef struct {
  char idautor[LENIDAUTOR];
  char nombres[LENNOMB];
  char apellidos[LENAPEL];
  FECHA fechanacimiento;
} AUTOR;

typedef struct {
  char iddocumento[LENIDDOC];
  char telefono[LENTELEFONO];
  char nombres[LENNOMB];
  char apellidos[LENAPEL];
} USUARIO;

typedef struct {
  char iddocumento[LENIDDOC];
  char ISBN[LENISBN];
  FECHA fecprestamo;
  FECHA fecdevolucion;
  int diasprestamo;
  float montoprestamo;
  float recargodiario;
} PRESTAMOS;

typedef struct nodo_at {
  AUTOR at;
  struct nodo_at *sig, *ant;
} NODO_AT;

typedef struct nodo_lb {
  LIBRO lb;
  struct nodo_lb *sig, *ant;
} NODO_LB;

typedef struct nodo_usr {
  USUARIO usr;
  struct nodo_usr *sig, *ant;
} NODO_USR;

typedef struct nodo_prt {
  PRESTAMOS prt;
  struct nodo_prt *sig, *ant;
} NODO_PRT;

void prestar(NODO_PRT **, NODO_PRT **, NODO_LB *, NODO_USR *, int *, int, int);
int capidautora_books(char *, char *, NODO_AT *, int, int, int);
void showusuarios_scroll(NODO_USR *, int, int, int, int, int);
void capbooks(NODO_LB **, NODO_LB **, NODO_AT *, int *, int);
void insertnodofin_prt(NODO_PRT **, NODO_PRT **, PRESTAMOS);
void showautores_scroll(NODO_AT *, int, int, int, int, int);
void showid_scroll_usr(NODO_USR *, int, int, int, int, int);
void showbooks_scroll(NODO_LB *, int, int, int, int, int);
void showid_scroll_lb(NODO_LB *, int, int, int, int, int);
void insertnodofin_usr(NODO_USR **, NODO_USR **, USUARIO);
void showid_scroll_at(NODO_AT *, int, int, int, int, int);
void showopcxy(char[][COL_OPCIONS], int, int, int, int);
void insertnodofin_ats(NODO_AT **, NODO_AT **, AUTOR);
void insertnodofin_lbs(NODO_LB **, NODO_LB **, LIBRO);
void openfiles(FILE **, FILE **, FILE **, FILE **);
void showautores_cursor(NODO_AT *, int, int, int);
void capusuarios(NODO_USR **, NODO_USR **, int *);
void showusers_cursor(NODO_USR *, int, int, int);
int showid_cursor_usr(NODO_USR *, int, int, int);
void showbooks_cursor(NODO_LB *, int, int, int);
int gets_usr(FILE *, NODO_USR **, NODO_USR **);
void capautores(NODO_AT **, NODO_AT **, int *);
void showprt_cursor(NODO_PRT *, int, int, int);
int showid_cursor_at(NODO_AT *, int, int, int);
int gets_prt(FILE *, NODO_PRT **, NODO_PRT **);
void MODbooks(NODO_LB *, NODO_AT *, int, int);
int validador_campostr(char *, int, int, int);
int gets_ats(FILE *, NODO_AT **, NODO_AT **);
int gets_lbs(FILE *, NODO_LB **, NODO_LB **);
int showid_cursor(NODO_LB *, int, int, int);
void capid_usuario(NODO_USR *, char *, int);
void guardar_prestamos(NODO_PRT *, FILE *);
FECHA Capf_prestamo(char *, int, int, int);
void showfield(char *, int, int, int, int);
void guardar_usuarios(NODO_USR *, FILE *);
int capisbn(NODO_LB *, char *, int, int);
void guardar_autores(NODO_AT *, FILE *);
void guardar_libros(NODO_LB *, FILE *);
int numtelefono(char *, int, int, int);
FECHA capfecha(char *, int, int, int);
void capid(NODO_AT *, char *, int);
void MODusuario(NODO_USR *, int);
void MODautor(NODO_AT *, int);
FECHA evaluarfecha(char *);
float flotantes(int, int);
int contar_digitos(int);
void setcolor(int, int);
int numerivo(int, int);
void colordefault();
char *Fecha_ACT();
int opciones(int);

int main() {

  FILE *pf_at, *pf_lb, *pf_usr, *pf_prt;
  openfiles(&pf_at, &pf_lb, &pf_usr, &pf_prt);

  NODO_USR *cabeza_usrs, *cola_usrs;
  NODO_AT *cabeza_ats, *cola_ats;
  NODO_LB *cabeza_lbs, *cola_lbs;
  NODO_PRT *cabeza_prt, *cola_prt;

  int op, cant_at, cant_lb, cant_usr, cant_prt;
  cabeza_ats = cola_ats = NULL;
  cabeza_lbs = cola_lbs = NULL;
  cabeza_usrs = cola_usrs = NULL;
  cabeza_prt = cola_prt = NULL;

  cant_usr = gets_usr(pf_usr, &cabeza_usrs, &cola_usrs);
  cant_at = gets_ats(pf_at, &cabeza_ats, &cola_ats);
  cant_lb = gets_lbs(pf_lb, &cabeza_lbs, &cola_lbs);
  cant_prt = gets_prt(pf_prt, &cabeza_prt, &cola_prt);

  do {
    switch ((op = opciones(SHOW_MU))) {
    case 0: // INGRESAR
      switch (opciones(SHOW_STRUCTS)) {
      case 0: // LIBRO
        capbooks(&cabeza_lbs, &cola_lbs, cabeza_ats, &cant_lb, cant_at);
        break;
      case 1: // AUTORES
        capautores(&cabeza_ats, &cola_ats, &cant_at);
        break;
      case 2: // USUARIOS
        capusuarios(&cabeza_usrs, &cola_usrs, &cant_usr);
        break;
      case 3: // PRESTAMOS
        prestar(&cabeza_prt, &cola_prt, cabeza_lbs, cabeza_usrs, &cant_prt,
                cant_lb, cant_usr);
        break;
      default:
        break;
      }
      break;
    case 1: // MODIFICAR
      switch (opciones(SHOW_STRUCTS)) {
      case 0: // LIBRO
        MODbooks(cabeza_lbs, cabeza_ats, cant_lb, cant_at);
        break;
      case 1: // AUTORES
        MODautor(cabeza_ats, cant_at);
        break;
      case 2: // USUARIOS
        MODusuario(cabeza_usrs, cant_usr);
        break;
      default:
        break;
      }
      break;
    case 3: // listar
      switch (opciones(SHOW_STRUCTS)) {
      case 0:                                        // LIBRO
        showbooks_cursor(cabeza_lbs, 2, 4, cant_lb); // 2 , 4 para posicion xy
        break;
      case 1: // AUTORES
        showautores_cursor(cabeza_ats, 2, 4, cant_at);
        break;
      case 2: // USERS
        showusers_cursor(cabeza_usrs, 2, 4, cant_usr);
        break;
      case 3: // PRESTAMO
        showprt_cursor(cabeza_prt, 2, 4, cant_prt);
        break;
      default:
        break;
      }
      break;
    case 4: // GUARDAR
      switch (opciones(SHOW_STRUCTS)) {
      case 0: // libros
        switch (opciones(SHOW_RESP)) {
        case 0: // si
          guardar_libros(cabeza_lbs, pf_lb);
          break;
        case 1: // NO
          break;
        }
        break;
      case 1: // Autores
        switch (opciones(SHOW_RESP)) {
        case 0: // si
          guardar_autores(cabeza_ats, pf_at);
          break;
        case 1: // NO
          break;
        }
        break;
      case 2: // USUARIOS
        switch (opciones(SHOW_RESP)) {
        case 0: // si
          guardar_usuarios(cabeza_usrs, pf_usr);
          break;
        case 1: // NO
          break;
        }
        break;
      case 3: // PRESTAMOS
        switch (opciones(SHOW_RESP)) {
        case 0: // si
          guardar_prestamos(cabeza_prt, pf_prt);
          break;
        case 1: // NO
          break;
        }
        break;
      default:
        break;
      }
      break;
    default:
      break;
    }
  } while (op != SHOW_MU - 1);

  fclose(pf_at);
  fclose(pf_lb);
  fclose(pf_usr);
  return (0);
}

/**
Funci�n: opciones.
Argumento: int nmu. menu a mostrar
Objetivo: mostrar opciones continuamente hasta que el usuario seleccione una
          o salga, a la vez que crea la animaci�n de moverse entre las
opciones.. returno: Retorna la opcion seleccionada por el usuario de ser el
caso. caso contrario retorna ESC.
*/
int opciones(int nmu) {
  system("cls");

  int FILS;
  char(*opciones)[COL_OPCIONS];
  char menu[][COL_OPCIONS] = {"INGRESAR     ", "MODIFICAR    ", "ELIMINAR     ",
                              "LISTAR       ", "GUARDAR      ", "DEVOLVER     ",
                              "SALIR        "};

  char respuesta[][COL_OPCIONS] = {"     SI      ", "     NO      "};

  char estructuras[][COL_OPCIONS] = {"LIBROS       ", "AUTORES      ",
                                     "USUARIOS     ", "PRESTAMOS    "};

  char LIBRO[][COL_OPCIONS] = {"ISBN         ", "TITULO       ",
                               "AUTOR        ", "FECHA        ",
                               "EDICION      "};

  char AUTOR[][COL_OPCIONS] = {"NOMBRES      ", "APELLIDOS    ",
                               "FECHA        "};

  char USER[][COL_OPCIONS] = {"NOMBRES      ", "APELLIDOS    ",
                              "TELEFONO     "};

  if (nmu == SHOW_MU) {
    opciones = &menu[0];
    FILS = sizeof(menu) / sizeof(menu[0]);
  } else if (nmu == SHOW_RESP) {
    opciones = &respuesta[0];
    FILS = sizeof(respuesta) / sizeof(respuesta[0]);
  } else if (nmu == SHOW_STRUCTS) {
    opciones = &estructuras[0];
    FILS = sizeof(estructuras) / sizeof(estructuras[0]);
  } else if (nmu == SHOW_M_AUTOR) {
    opciones = &AUTOR[0];
    FILS = sizeof(AUTOR) / sizeof(AUTOR[0]);
  } else if (nmu == SHOW_M_LIBRO) {
    opciones = &LIBRO[0];
    FILS = sizeof(LIBRO) / sizeof(LIBRO[0]);
  } else if (nmu == SHOW_M_USUARIO) {
    opciones = &USER[0];
    FILS = sizeof(LIBRO) / sizeof(LIBRO[0]);
  }

  char tecla;
  int opc = 0;

  _setcursortype(0);
  do {
    showopcxy(opciones, FILS, 20, 6, opc);
    do {
      tecla = getch();
    } while (tecla != ESC && tecla != ENTER && tecla != ARRIBA &&
             tecla != ABAJO);

    if (tecla != ESC) {

      if (tecla == ARRIBA) {
        if (opc != 0)
          opc--;
        else
          opc = FILS - 1;
      }
      if (tecla == ABAJO) {
        if (opc < FILS - 1)
          opc++;
        else
          opc = 0;
      }
    }
  } while (tecla != ESC && tecla != ENTER);
  _setcursortype(100);

  if (tecla == ENTER)
    return opc;
  else
    return (ESC);
}
/**
Funci�n: insertnodofin_ats.
Argumentos: Nodo_AT **cabeza. direcci�n de memoria de la cabeza del nodo de
autores. NODO_AT **cola. direcci�n de memoria de la cabeza del nodo de autores.
            AUTOR at. cantidad total de autores.
Objetivo: isertar el libro en la ultima posici�n del nodo.
*/
void insertnodofin_ats(NODO_AT **cabeza, NODO_AT **cola, AUTOR at) {
  NODO_AT *nuevo;

  nuevo = (NODO_AT *)malloc(sizeof(NODO_AT));

  nuevo->at = at;

  nuevo->sig = NULL;
  nuevo->ant = *cola;

  if (*cabeza == NULL)
    *cabeza = nuevo;
  if (*cola)
    (*cola)->sig = nuevo;
  *cola = nuevo;
}
/**
Funci�n: gets_ats.
Argumentos: FILE *pf. Puntero al file con los autores a leer.
            Nodo_AT **cabeza. direcci�n de memoria de la cabeza del nodo de los
autores. NODO_AT **cola. direcci�n de memoria de la cabeza del nodo de los
autores. Objetivo: Leer todos los autores desde el archivo proporcionado y
guardarlo en su nodo correspondiente.
*/
int gets_ats(FILE *pf, NODO_AT **cabeza, NODO_AT **cola) {
  int cant = 0;
  NODO_AT *IND = NULL;
  IND = (NODO_AT *)malloc(sizeof(NODO_AT));
  while (fread(&IND->at, sizeof(AUTOR), 1, pf) == 1) {
    insertnodofin_ats(cabeza, cola, IND->at);
    IND = (NODO_AT *)malloc(sizeof(NODO_AT));
    cant++;
  }

  return cant;
}

/**
Funci�n: insertnodofin_lbs.
Argumentos: Nodo_LB **cabeza. direcci�n de memoria de la cabeza del nodo de
libros. NODO_LB **cola. direcci�n de memoria de la cabeza del nodo de libros.
            LIBRO lb. cantidad total de libros.
Objetivo: isertar el libro en la ultima posici�n del nodo.
*/
void insertnodofin_lbs(NODO_LB **cabeza, NODO_LB **cola, LIBRO lb) {
  NODO_LB *nuevo;

  nuevo = (NODO_LB *)malloc(sizeof(NODO_LB));

  nuevo->lb = lb;

  nuevo->sig = NULL;
  nuevo->ant = *cola;

  if (*cabeza == NULL)
    *cabeza = nuevo;
  if (*cola)
    (*cola)->sig = nuevo;
  *cola = nuevo;

  return;
}

/**
Funci�n: gets_lbs.
Argumentos: FILE *pf. Puntero al file con los libros a leer.
            Nodo_LB **cabeza. direcci�n de memoria de la cabeza del nodo de
libros. NODO_LB **cola. direcci�n de memoria de la cabeza del nodo de los
libros. Objetivo: Leer todos los libros desde el archivo proporcionado y
guardarlo en su nodo correspondiente
*/
int gets_lbs(FILE *pf, NODO_LB **cabeza, NODO_LB **cola) {
  int cant = 0;
  NODO_LB *IND = NULL;
  IND = (NODO_LB *)malloc(sizeof(NODO_LB));
  while (fread(&IND->lb, sizeof(LIBRO), 1, pf) == 1) {
    insertnodofin_lbs(cabeza, cola, IND->lb);
    IND = (NODO_LB *)malloc(sizeof(NODO_LB));
    cant++;
  }

  return cant;
}

/**
Funci�n: insertnodofin_usr.
Argumentos: Nodo_USR **cabeza. direcci�n de memoria de la cabeza del nodo de
usuarios. NODO_UDR **cola. direcci�n de memoria de la cabeza del nodo de
usuarios. USUARIO usr. cantidad total de usuarios. Objetivo: isertar el usuario
en la ultima posici�n del nodo.
*/
void insertnodofin_usr(NODO_USR **cabeza, NODO_USR **cola, USUARIO usr) {
  NODO_USR *nuevo;
  nuevo = (NODO_USR *)malloc(sizeof(NODO_USR));
  nuevo->usr = usr;
  nuevo->sig = NULL;
  nuevo->ant = *cola;

  if (*cabeza == NULL)
    *cabeza = nuevo;
  if (*cola)
    (*cola)->sig = nuevo;
  *cola = nuevo;

  return;
}

/**
Funci�n: gets_user.
Argumentos: FILE *pf. Puntero al file con los usuarios a leer.
            Nodo_USR **cabeza. direcci�n de memoria de la cabeza del nodo de
usuarios. NODO_UDR **cola. direcci�n de memoria de la cabeza del nodo de
usuarios. Objetivo: Leer todos los usuarios desde el archivo proporcionado y
guardarlo en su nodo correspondiente
*/
int gets_usr(FILE *pf, NODO_USR **cabeza, NODO_USR **cola) {
  int cant = 0;
  NODO_USR *IND = (NODO_USR *)malloc(sizeof(NODO_USR));
  while (fread(&IND->usr, sizeof(USUARIO), 1, pf) == 1) {
    insertnodofin_usr(cabeza, cola, IND->usr);
    IND = (NODO_USR *)malloc(sizeof(NODO_USR));
    cant++;
  }

  return cant;
}

/**
Funci�n: showopcxy.
Argumento: char menu[][COLUMNAS]. arreglo que contiene las opciones a mostrar.
           int n. cantidad de opciones. int (px) y (py).
           posicion de columna y fila del puntero en la terminal.
           int fil. fila seleccionada actualmente.
Objetivo: mostrar todas las opciones del arreglo e identificar la fila
seleccionada actualmente.
*/
void showopcxy(char menu[][COL_OPCIONS], int n, int px, int py, int fil) {
  char opcions[] = {"OPCIONES:"};
  gotoxy(px, py);
  setcolor(BLACK, MAGENTA);
  printf("%-*s", COL_OPCIONS - 1, opcions);
  for (int ind = 0; ind < n; ind++) {
    setcolor(YELLOW, BLUE);
    gotoxy(px, py + ind + 1);
    if (fil == ind)
      setcolor(BLUE, YELLOW);
    printf("%s", menu[ind]);
  }
  colordefault();
}

/**
Funci�n: setcolor.
Argumento: int text. color de texto. int fond. color de fondo.
Objetivo: cambiar el color de texto y fondo a voluntad de un area especificada.
*/
void setcolor(int text, int fond) {
  textcolor(text);
  textbackground(fond);
}

/**
Funci�n: colordefault.
Argumento: sin argumentos.
Objetivo: cambiar el color de texto y fondo con colores
          predeterminados de un area especificada.
*/
void colordefault() { setcolor(YELLOW, BLACK); }

/**
Funci�n: openfiles.
Argumento: FILE** pf_at. direcci�n de puntero al archivo de autores.
           FILE** pf_lb. direcci�n de puntero al archivo de libros.
           FILE** pf_usr. direcci�n de puntero al archivo de usuarios.
           FILE **pf_prt. direcci�n de puntero del archivo de prestamos.
Objetivo: Abrir todos los archivos necesarios para
          la correcta ejecuci�n del programa.
*/
void openfiles(FILE **pf_at, FILE **pf_lb, FILE **pf_usr, FILE **pf_prt) {
  if ((*pf_at = fopen(ARCH_AT, "rb")) == NULL) {
    if ((*pf_at = fopen(ARCH_AT, "wb")) == NULL) {
      printf("No se pudo crear el archivo %s.\n", ARCH_AT);
      exit(-1);
    }
  }
  if ((*pf_lb = fopen(ARCH_LB, "rb")) == NULL) {
    if ((*pf_lb = fopen(ARCH_LB, "wb")) == NULL) {
      printf("No se pudo crear el archivo %s.\n", ARCH_LB);
      exit(-1);
    }
  }
  if ((*pf_usr = fopen(ARCH_USR, "rb")) == NULL) {
    if ((*pf_usr = fopen(ARCH_USR, "wb")) == NULL) {
      printf("No se pudo crear el archivo %s.\n", ARCH_USR);
      exit(-1);
    }
  }

  if ((*pf_prt = fopen(ARCH_PRT, "rb")) == NULL) {
    if ((*pf_prt = fopen(ARCH_PRT, "wb")) == NULL) {
      printf("No se pudo crear el archivo %s.\n", ARCH_PRT);
      exit(-1);
    }
  }
}

/**
Funci�n: showautores_cursor
Argumentos: NODO *cabeza. Lista con los datos de autores a mostrar.
            int x, y. posicion de columna y fila a utilizar en la terminal.
            int cont_at. Canidad de autores capturados.
objetivo: mostrar los datos del autor realizando el efecto de scroll.
*/
void showautores_cursor(NODO_AT *cabeza, int x, int y, int cant_at) {
  ;
  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY AUTORES REGISTRADOS!!!\n");
    system("pause");
    return;
  }

  if (cant_at < scroll)
    scroll = cant_at;

  _setcursortype(0);
  system("cls");

  do {
    showautores_scroll(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_at - 1;
        comienzo = cant_at - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_at - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC);
  _setcursortype(100);
}

/**
Funci�n: showautores_scroll.
Argumentos: NODO_AT *cabeza. Lista de autores a motrar. int x, y. posicion de
columna y fila a usar en la terminal. int Fil. indice del autor seleccionado al
momento de mostrar. int comienzo. indice desde donde se empezara a imprimir.
Objetivo: Mostrar los autores desde la posicion comienzo hasta mostrar, y
resaltar el autor en que se encuentra el cursor en ese momento.
*/
void showautores_scroll(NODO_AT *cabeza, int x, int y, int fil, int comienzo,
                        int mostrar) {
  ScreenClear();
#define CARACTERES_NM_AP 10

  char id[] = {"IDAUTOR"};
  char name[] = {"NOMBRES"};
  char lname[] = {"APELLIDOS"};
  char fecha[] = {"FECHA"};

  NODO_AT *nc, *nm;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  int nb_m = strlen(nc->at.nombres), ap_m = strlen(nc->at.apellidos);
  for (nm = nc; i < comienzo + mostrar; nm = nm->sig, i++) {
    int tempm = strlen(nm->at.nombres), tempap = strlen(nm->at.apellidos);
    if (tempm > nb_m)
      nb_m = tempm;
    if (tempap > ap_m)
      ap_m = tempap;
  }

  if (nb_m < CARACTERES_NM_AP)
    nb_m = CARACTERES_NM_AP;
  if (ap_m < CARACTERES_NM_AP)
    ap_m = CARACTERES_NM_AP;
  setcolor(YELLOW, BLACK);
  gotoxy(x, y);
  printf("%-*s%-*s%-*s%-*s", LENIDAUTOR, id, nb_m + 1, name, ap_m + 1, lname,
         STR_FECHA, fecha);

  for (int ind = 0; ind < comienzo; ind++) {
    gotoxy(x, y + ind + 1);
    colordefault();
    printf("                                                                   "
           "                                   ");
    delline();
  }
  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(WHITE, MAGENTA);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLACK, YELLOW);
    printf("%-*s%-*s%-*s%2hu/%2hu/%-4hu", LENIDAUTOR, nc->at.idautor, nb_m + 1,
           nc->at.nombres, ap_m + 1, nc->at.apellidos,
           nc->at.fechanacimiento.dd, nc->at.fechanacimiento.mm,
           nc->at.fechanacimiento.yyy);
  }
  colordefault();
}

/**
Funci�n: showbooks_cursor
Argumentos: NODO *cabeza. Lista con los datos de libros a mostrar.
            int x, y. posicion de columna y fila a utilizar en la terminal.
            int cont_at. Canidad de libros capturados.
objetivo: mostrar los datos del autor realizando el efecto de scroll.
*/
void showbooks_cursor(NODO_LB *cabeza, int x, int y, int cant_lb) {

  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY LIBROS REGISTRADOS!!!\n");
    system("pause");
    return;
  }

  if (cant_lb < scroll)
    scroll = cant_lb;

  _setcursortype(0);
  system("cls");

  do {
    showbooks_scroll(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_lb - 1;
        comienzo = cant_lb - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_lb - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC);
  _setcursortype(100);
}

/**
Funci�n: showbooks_scroll.
Argumentos: NODO_LB *cabeza. Lista de libros a motrar. int x, y. posicion de
columna y fila a usar en la terminal. int Fil. indice del libro seleccionado al
momento de mostrar. int comienzo. indice desde donde se empezara a imprimir.
Objetivo: Mostrar los libros desde la posicion comienzo hasta mostrar, y
resaltar el libro en que se encuentra el cursor en ese momento.
*/
void showbooks_scroll(NODO_LB *cabeza, int x, int y, int fil, int comienzo,
                      int mostrar) {
#define CARACTERES_TTL 7
#define CARACTERES_EDT 8
  ScreenClear();

  char ISBN[] = {"ISBN"};
  char titulo[] = {"TITULO"};
  char editora[] = {"EDITORA"};
  char id[] = {"IDAUTOR"};
  char fecha[] = {"FECHA"};
  char edicion[] = {"EDICION"};

  NODO_LB *nc, *nm;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  int ttl_m = strlen(nc->lb.titulo), edt_m = strlen(nc->lb.editora),
      edn_m = contar_digitos(nc->lb.edicion);
  for (nm = nc; i < comienzo + mostrar; nm = nm->sig, i++) {
    int tempttl = strlen(nm->lb.titulo), tempedt = strlen(nm->lb.editora),
        tempedn = contar_digitos(nm->lb.edicion);
    if (tempttl > ttl_m)
      ttl_m = tempttl;
    if (tempedt > edt_m)
      edt_m = tempedt;
    if (tempedn > edn_m)
      edn_m = tempedn;
  }

  if (ttl_m < CARACTERES_TTL)
    ttl_m = CARACTERES_TTL;
  if (edt_m < CARACTERES_EDT)
    edt_m = CARACTERES_EDT;
  if (edn_m < CARACTERES_EDT)
    edn_m = CARACTERES_EDT;

  setcolor(YELLOW, BLACK);
  gotoxy(x, y);
  printf("%-*s%-*s%-*s%-*s%-*s%-*s", LENISBN + 1, ISBN, ttl_m + 1, titulo,
         edt_m + 1, editora, LENIDAUTOR, id, STR_FECHA + 1, fecha, edn_m + 1,
         edicion);

  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(WHITE, MAGENTA);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLACK, YELLOW);
    printf("%-*s%-*s%-*s%-*s%2hu/%2hu/%-4hu%*d", LENISBN + 1, nc->lb.ISBN,
           ttl_m + 1, nc->lb.titulo, edt_m + 1, nc->lb.editora, LENIDAUTOR,
           nc->lb.idautor, nc->lb.fechaedicion.dd, nc->lb.fechaedicion.mm,
           nc->lb.fechaedicion.yyy, edn_m + 1, nc->lb.edicion);
  }
  colordefault();
}

/**
Funci�n:capbooks.
Argumento: NODO_LB **cabeza. direcci�n de memoria del puntero hacia el primer
nodo de la lista de libros. NODO_LB **cola. direcci�n de memoria del puntero
hacia el ultimo nodo de la lista de libros NOTO_AT *cabeza. direcci�n de memoria
del primer nodo de la lista de autores. int *cant_lb. puntero al total de libros
capturados actualmente. int cant_at. cantidad total de libros. Objetivo:
capturar una estructura libro y guardarla en la lista de los libros
*/
void capbooks(NODO_LB **cabeza, NODO_LB **cola, NODO_AT *cabeza_at,
              int *cant_lb, int cant_at) {
  LIBRO lb;
  memset(&lb, 0, sizeof(LIBRO));
  char campofecha[STR_FECHA] = {0};

  ScreenClear();
  gotoxy(2, 2);
  setcolor(YELLOW, BLACK);
  printf("INGRESE EL ISBN: ");
  if (capisbn(*cabeza, lb.ISBN, 19, 2)) {
    if (capidautora_books(lb.idautor, lb.editora, cabeza_at, 9, 4, cant_at)) {
      gotoxy(2, 4);
      setcolor(YELLOW, BLACK);
      printf("TITULO: ");
      if ((validador_campostr(lb.titulo, LENTITULO, 9, 4))) {
        gotoxy(2, 6);
        setcolor(YELLOW, BLACK);
        printf("Fecha de edici%cn(dd/mm/yyyy): ", 162);
        lb.fechaedicion = capfecha(campofecha, STR_FECHA, 32, 6);
        if (lb.fechaedicion.dd) {
          gotoxy(2, 8);
          setcolor(YELLOW, BLACK);
          printf("Edici%cn(#): ", 162);
          if ((lb.edicion = numerivo(14, 8))) {
            insertnodofin_lbs(cabeza, cola, lb);
            *cant_lb += 1;
            colordefault();
            return;
          }
        }
      }
    }
  }
  colordefault();
  system("cls");
  printf("HAS CANCELADO EL INGRESO DEL LIBRO!!\n");
  system("pause");
}

/**
Funci�n: validador_campostr.
Argumento: char *str. Direcci�n de la fila o campo a capturar.
           int n. maximo caracteres a capturar. int (x) y (y).
           posicion de columna y fila del puntero en la terminal.
Objetivo: Capturar un campo tanto de caracteres como letras.
*/
int validador_campostr(char *str, int n, int x, int y) {
  int ind = 0, crt = 0;
  char chr;

  _setcursortype(100);
  do {
    showfield(str, ind, n, x, y);
    do {
      chr = getch();
    } while (!(isalpha(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != ESP &&
             chr != '-');
    if (chr == DERECHA) {
      if (ind < n - 1)
        ind++;
    } else {
      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {
        if (chr != ENTER && chr != ESC) {
          if (chr == BKSP) {
            if (ind) {
              ind--;
              strcpy(str + ind, str + ind + 1);
            }
          } else {
            if (ind < n) {
              if (chr == ESP && !(isalpha(str[0])))
                continue;
              *(str + ind) = chr;
              ind++;
              if (isalpha(chr))
                crt++;
            }
          }
        } else if (chr == ENTER && !crt) {
          gotoxy(x, y + 3);
          printf("ERROR!!! DEBE INGRESAR AL MENOS UN CARACTER\n");
          Sleep(1000);
          gotoxy(x, y + 3);
          delline();
          chr++;
        }
      }
    }
  } while (chr != ENTER && chr != ESC);

  if (chr != ESC) {
    *(str + ind) = '\0';
    return (1);
  } else
    return (0);
}

/**
Funci�n: capidautora_books
Argumento: char *idautor. arreglo a guardar el id del libro seleccionado.
           char *editora. arreglo a guardar el nombre y apellido del libro.
           NODO_AT *cabeza. nodo a cabeza.
           int x. int y. posici�n del puntero.
           int cant_at. cantidad total de autores
Objetivo: Mostrar los id de los autores contenido en NODO_AT y guardar el
seleccionado en *idautora a la vez que se guarda el nombre y apellido del mismo.
return: 1 si se ha seleccionado un id y 0 en caso de que se haya cancelado.
*/
int capidautora_books(char *idautor, char *editora, NODO_AT *cabeza, int x,
                      int y, int cant_at) {
  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY LIBROS REGISTRADOS!!!\n");
    system("pause");
    return (0);
  }

  if (cant_at < scroll)
    scroll = cant_at;

  _setcursortype(0);
  system("cls");

  do {
    showid_scroll_at(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_at - 1;
        comienzo = cant_at - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_at - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC && s != ENTER);
  _setcursortype(100);
  system("cls");

  if (s == ENTER) {
    NODO_AT *nc;
    int i = 0;
    for (nc = cabeza; i < FIL; nc = nc->sig, i++)
      ;

    strcpy(idautor, nc->at.idautor);
    strcpy(editora, nc->at.nombres);
    editora[strlen(editora)] = ESP;
    strcat(editora, nc->at.apellidos);
    return (1);
  } else
    return (0);
}

/**
Funci�n: showid_scroll_lb.
Argumento: NODO_LB *cabeza. puntero al primer nodo de la lista de libros.
           int n. cantidad de id. int (px) y (py).
           posicion de columna y fila del puntero en la terminal.
           int fil. fila seleccionada actualmente.
           int comienzo. dede que numero de nodo se mostrara.
           int mostrar. que cantidad de libro mostrar despues de comienzo.
Objetivo: mostrar todas los id del arreglo e identificar el id seleccionado.
*/
void showid_scroll_lb(NODO_LB *cabeza, int x, int y, int fil, int comienzo,
                      int mostrar) {
  int size = 19;

  NODO_LB *nc;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  gotoxy(x, y);
  setcolor(BLACK, MAGENTA);
  printf("SELECCIONA EL ISBN");
  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(YELLOW, BLUE);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLUE, YELLOW);
    printf("%-*s", size, nc->lb.ISBN);
  }

  colordefault();
}

/** Funci�n: evaluarfecha
Argumento: char *str. direcci�n de la fila a evaluar.
objetivo: evaluar si se ha ingresado un fecha y en tal caso
          si es correcta.
returna:  Un struct FECHA con la fecha correspondiente si es correcta.
          con 0 en el caso contrario.
 */
FECHA evaluarfecha(char *str) {
  unsigned short int dd, mm, yyy, maximo_dias;
  FECHA fecha;

  fecha.dd = 0;
  fecha.mm = 0;
  fecha.yyy = 0;
  for (int ind = 0; str[ind]; ind++)
    if (str[ind] == '/' && (str[ind + 3] == '/' || str[ind + 2] == '/')) {
      char agnoo[] = {str[ind + 4], str[ind + 5], str[ind + 6], str[ind + 7],
                      '\0'};
      char mess[] = {str[ind + 1], str[ind + 2], '\0'};

      if (!(isdigit(str[ind - 2]))) {
        char diaa[] = {str[ind - 1], '\0'};
        dd = atoi(diaa);
      } else {
        char diaa[] = {str[ind - 2], str[ind - 1], '\0'};
        dd = atoi(diaa);
      }

      yyy = atoi(agnoo);
      mm = atoi(mess);
    }

  if (mm < 1 || mm > 12)
    return (fecha);

  if (mm == 2) {
    if ((yyy % 4 == 0 && yyy % 100 != 0) || yyy % 400 == 0)
      maximo_dias = 29;
    else
      maximo_dias = 28;
  } else if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
    maximo_dias = 30;
  else
    maximo_dias = 31;

  if (dd < 1 || dd > maximo_dias)
    return (fecha);

  fecha.dd = dd;
  fecha.mm = mm;
  fecha.yyy = yyy;

  return (fecha);
}

/**
Funci�n: Caofecha.
Argumento: char *str. Direcci�n de la fila o campo a capturar.
           int n. maximo caracteres a capturar. int (x) y (y).
           posicion de columna y fila del puntero en la terminal.
Objetivo: Capturar una fecha y evaluar si esta es correcta o no.
retorna: una estructura compuesta por 3 variables int, dias, mes y yyy.
*/
FECHA capfecha(char *str, int n, int x, int y) {
  int ind = 0, digitos = 0, validacion = 0;
  char chr;
  FECHA fecha;

  _setcursortype(100);
  do {
    if (validacion == 1) {
      validacion--;
      system("cls");
      gotoxy(2, y);
      printf("Fecha de edici%cn(dd/mm/yyyy): ", 162);
    }
    *(str + 2) = '/';
    *(str + 5) = '/';
    showfield(str, ind, n, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != ESP);

    if (chr == DERECHA) {
      if (ind < n - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr != ENTER && chr != ESC) {
          if (chr == BKSP && isdigit(str[ind - 1])) {
            if (ind) {
              digitos--;
              ind--;
              str[ind] = ESP;
            }
          } else if (chr == BKSP)
            continue;
          else {
            if (ind < n && digitos < NUMEROS_FECHA) {
              digitos++;
              *(str + ind) = chr;
              if (ind == 1 || ind == 4)
                ind += 2;
              else
                ind++;
            }
          }
        }
      }
    }
    if (chr == ENTER) {
      fecha = evaluarfecha(str);
      if (!(fecha.dd)) {
        chr = 0;
        ind = 0;
        digitos = 0;
        validacion++;
        for (int ind = 0; ind < n; ind++)
          str[ind] = 0;
        gotoxy(2, 8);
        if (fecha.yyy == 0)
          printf("FECHA ERRONEA!!! INTENTE NUEVAMENTE:\n");
        system("pause");
        system("cls");
      } else
        return (fecha);
    }
    if (chr == ESC) {
      fecha.dd = 0;
      return (fecha);
    }

  } while (chr != ENTER);
  return fecha;
}

/**
Funci�n: capisbn.
Argumento: NODO_LB *cabeza. puntero al primer nodo de la lista de libros.
           char *str. Direcci�n del campo del telefonoa capturar.
           int (x) y (y).posicion de columna y fila del puntero en la terminal.
           int total. cantidad de digitos a capturar.
Objetivo: capturar un campo de digitos respectando las pautas resividas.
*/
int capisbn(NODO_LB *cabeza, char *str, int x, int y) {

  int ind = 0, digitos = 0, validacion = 0;
  char chr;

  _setcursortype(100);
  do {
    if (validacion == 1) {
      validacion--;
      system("cls");
      gotoxy(2, y);
      printf("INGRESE EL ISBN: ");
    }

    showfield(str, ind, LENISBN - 1, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != ESP);

    if (chr == DERECHA) {
      if (ind < LENISBN - 1 - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr != ENTER && chr != ESC) {
          if (chr == BKSP) {
            if (ind) {
              digitos--;
              ind--;
              str[ind] = ESP;
            }
          } else {
            if (ind < LENISBN - 1 && digitos < LENISBN - 1) {

              *(str + ind) = chr;
              ind++;
              digitos++;
            }
          }
        }
      }
    }
    if (chr == ENTER) {
      if (digitos < LENISBN - 1) {
        gotoxy(x, y + 3);
        printf("ERROR!!! DEBE INGRESAR UN TOTAL DE [%d] DIGITOS\n",
               LENISBN - 1);
        Sleep(1000);
        gotoxy(x, y + 3);
        delline();
        chr++;
      } else if (cabeza) {
        *(str + ind) = '\0';

        for (NODO_LB *ind0 = cabeza; ind0; ind0 = ind0->sig)
          if (strcmp(ind0->lb.ISBN, str) == 0) {
            chr++;
            validacion++;
            break;
          }

        if (validacion == 1) {
          gotoxy(x, y + 3);
          printf("ERROR!!! ESTE ISBN YA SE ENCUENTRA CAPTURADO, INTENTE "
                 "NUEVAMENTE\n");
          Sleep(1000);
          gotoxy(x, y + 3);
          delline();
          for (int i = 0; i < digitos; str[i] = 0, i++)
            ;
          ind = digitos = 0;
        }
      }
    }
  } while (chr != ENTER && chr != ESC);

  if (chr != ESC)
    return (1);
  else
    return (0);
}

/**
Funci�n: numerivo.
Argumento:int (x) y (y).
          posicion de columna y fila del puntero en la terminal.
Objetivo: capturar un campo de digitos respectando las pautas resividas..
*/
int numerivo(int x, int y) {

  int ind = 0;
  char chr;
  int cant = 0, total = CANTINI;
  char *str = (char *)malloc(sizeof(char) * total);
  memset(str, 0, sizeof(str));
  if (!str) {
    printf("Error al asignar memoria");
    return -1;
  }

  _setcursortype(100);
  do {
    if (cant == total) {
      total += CANTINC;
      str = (char *)realloc(str, sizeof(char) * total);
      memset(str + cant, 0, sizeof(str));
    }
    showfield(str, ind, total, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA);

    if (chr == DERECHA) {
      if (ind < total - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr == BKSP) {
          if (ind) {
            ind--;
            total--;
            strcpy(str + ind, str + ind + 1);
          }
        } else {
          if (ind < total) {
            *(str + ind) = chr;
            ind++;
            cant++;
          }
        }
      }
    }
  } while (chr != ENTER && chr != ESC);
  int edicion = atoi(str);
  if (chr != ESC) {
    *(str + ind) = '\0';
    free(str);
    return (edicion);
  } else
    return (0);
}
/**
Funci�n: capautores.
Argumento: NODO_AT **cabeza. direcci�n de memoria del nodo que apunta a la
primera posici�n. NODO_AT **cola. direcci�n de memoria del nodo de autores que
apunta a la ultima posici�n. int *cant_at. direcci�n de memoria de la variable
que contiene la cantidad de autores total. Objetivo: capturar un autor y
guardarlo en su lista.
*/
void capautores(NODO_AT **cabeza, NODO_AT **cola, int *cant_at) {
  system("cls");
  AUTOR at;
  memset(&at, 0, sizeof(AUTOR));
  char campofecha[STR_FECHA] = {0};

  capid(*cola, at.idautor, *cant_at);
  gotoxy(2, 4);
  setcolor(YELLOW, BLACK);
  printf("NOMBRES:");
  if ((validador_campostr(at.nombres, LENNOMB, 10, 4))) {
    gotoxy(2, 6);
    setcolor(YELLOW, BLACK);
    printf("APELLIDOS:");
    if ((validador_campostr(at.apellidos, LENAPEL, 12, 6))) {
      gotoxy(2, 8);
      setcolor(YELLOW, BLACK);
      printf("Fecha(dd/mm/yyyy):");
      at.fechanacimiento = capfecha(campofecha, STR_FECHA, 20, 8);
      if (at.fechanacimiento.dd) {
        insertnodofin_ats(cabeza, cola, at);
        *cant_at += 1;
        colordefault();
        return;
      }
    }
  }

  colordefault();
  system("cls");
  printf("HAS CANCELADO EL INGRESO DEL AUTOR!!\n");
  system("pause");
}

/**
Funci�n: capid.
Argumentos: NODO_AT *cabeza.  id anteriores.
            int cant_lb. Cantidad total de id .
            char *id. Donde se guardara el id
Objetivo: obtener el id correspondiente teniendo en cuenta el anterior y
sumandole uno a este. en caso de ser el primero se llenara de ceros, y se le
sumara 1 a la ultima posici�n.
*/
void capid(NODO_AT *cola, char *id, int cant_lb) {
  if (cant_lb) {
    strcpy(id, cola->at.idautor);

    for (int ind = LENIDAUTOR - 2; ind >= 0; ind--) {
      if (cola->at.idautor[ind] < '9') {
        id[ind]++;
        break;
      } else if (cola->at.idautor[ind] == '9' && ind > 0) {
        id[ind] = '0';
        id[ind - 1] = '1';
        break;
      } else if (cola->at.idautor[ind] == '9') {
        id[ind] = '1';
        break;
      } else if (cola->at.idautor[ind] != '0') {
        id[ind] = cola->at.idautor[ind] + 1;
        break;
      }
    }
  } else {
    for (int ind = 0; ind < LENIDAUTOR - 1; ind++) {
      if (ind == LENIDAUTOR - 2) {
        id[ind] = '1';
        break;
      } else
        id[ind] = '0';
    }
  }
}

/**
Funci�n: guardar_autores.
Argumento: NODO_AT *cabeza. primer nodo.
           FILE *pf. direcci�n del archivo de autores.
Objetivo: guardar todos los autores en la direcci�n proporcionada.
*/
void guardar_autores(NODO_AT *cabeza, FILE *pf) {

  if ((pf = fopen(ARCH_AT, "wb")) == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  for (NODO_AT *ind = cabeza; ind; ind = ind->sig)
    fwrite(&(ind->at), sizeof(AUTOR), 1, pf);

  fclose(pf);
}
/**
Funci�n: guardar_libros.
Argumento: NODO_LB *cabeza. primer nodo.
           FILE *pf. direcci�n del archivo de libros.
Objetivo: guardar todos los libros en la direcci�n proporcionada.
*/
void guardar_libros(NODO_LB *cabeza, FILE *pf) {

  if ((pf = fopen(ARCH_LB, "wb")) == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  for (NODO_LB *ind = cabeza; ind; ind = ind->sig)
    fwrite(&(ind->lb), sizeof(LIBRO), 1, pf);

  fclose(pf);
}

/**
Funci�n: contar_digitos.
Argumento: int num. n�mero a contar sus digitos.
Objetivo: contar la cantidad de digitos de un n�mero.
Retorna: la cantidad de digitos contados.
*/
int contar_digitos(int num) {
  int cant;
  for (cant = 0; num; num /= 10, cant++)
    ;

  return cant;
}

/**
Funci�n: capusuarios.
Argumento: NODO_USR **cabeza. direcci�n de memoria del nodo que apunta a la
primera posici�n. NODO_USR **cola. direcci�n de memoria del nodo de usuarios que
apunta a la ultima posici�n. int *cant_usr. direcci�n de memoria de la variable
que contiene la cantidad de usuarios total. Objetivo: capturar un usuario y
guardarlo en su lista.
*/
void capusuarios(NODO_USR **cabeza, NODO_USR **cola, int *cant_usr) {
  system("cls");
  USUARIO usr;
  memset(&usr, 0, sizeof(USUARIO));

  capid_usuario(*cola, usr.iddocumento, *cant_usr);
  gotoxy(2, 4);
  setcolor(YELLOW, BLACK);
  printf("NOMBRES:");
  if ((validador_campostr(usr.nombres, LENNOMB, 10, 4))) {
    gotoxy(2, 6);
    setcolor(YELLOW, BLACK);
    printf("APELLIDOS:");
    if ((validador_campostr(usr.apellidos, LENAPEL, 12, 6))) {
      gotoxy(2, 8);
      setcolor(YELLOW, BLACK);
      printf("TELEFONO: ");
      if (numtelefono(usr.telefono, LENTELEFONO - 1, 12, 8)) {
        insertnodofin_usr(cabeza, cola, usr);
        *cant_usr += 1;
        return;
      }
    }
  }

  colordefault();
  system("cls");
  printf("HAS CANCELADO EL INGRESO DEL USUARIO!!\n");
  system("pause");
}

/**
Funci�n: numtelefono.
Argumento: char *str. Direcci�n del campo del telefonoa capturar.
           int n. maximo caracteres a capturar. int (x) y (y).
           posicion de columna y fila del puntero en la terminal.
           int total. cantidad de digitos a capturar.
Objetivo: capturar un campo de digitos respectando las pautas resividas.
*/
int numtelefono(char *str, int n, int x, int y) {
  int ind = 0, digitos = 0;
  char chr;

  _setcursortype(100);
  do {
    *(str + 3) = '-';
    *(str + 7) = '-';
    showfield(str, ind, n, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != ESP);

    if (chr == DERECHA) {
      if (ind < n - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr != ENTER && chr != ESC) {
          if (chr == BKSP && isdigit(str[ind - 1])) {
            if (ind) {
              digitos--;
              ind--;
              str[ind] = ESP;
            }
          } else if (chr == BKSP)
            continue;
          else {
            if (ind < n && digitos < n) {

              *(str + ind) = chr;
              if (ind == 2 || ind == 6)
                ind += 2;
              else
                ind++;
              digitos++;
            }
          }
        }
      }
    }
    if (chr == ENTER && digitos < n - 2) {
      gotoxy(x, y + 3);
      printf("ERROR!!! DEBE INGRESAR UN TOTAL DE [%d] DIGITOS\n", n - 2);
      Sleep(1000);
      gotoxy(x, y + 3);
      delline();
      chr = 0;
    }
  } while (chr != ENTER && chr != ESC);

  if (chr != ESC) {
    *(str + ind) = '\0';
    return (1);
  } else
    return (0);
}

/**
Funci�n: capid_usuario.
Argumentos: NODO_USR *cola. id anterior.
            int cantA. Cantidad total de id .
            char *id. Donde se guardara el id
Objetivo: obtener el id correspondiente teniendo en cuenta el anterior y
sumandole uno a este. en caso de ser el primero se llenara de ceros, y se le
sumara 1 a la ultima posici�n.
*/
void capid_usuario(NODO_USR *cola, char *id, int cant_usr) {
  if (cant_usr) {
    strcpy(id, cola->usr.iddocumento);

    for (int ind = LENIDDOC - 2; ind >= 0; ind--) {
      if (cola->usr.iddocumento[ind] < '9') {
        id[ind]++;
        break;
      } else if (cola->usr.iddocumento[ind] == '9' && ind > 0) {
        id[ind] = '0';
        id[ind - 1] = '1';
        break;
      } else if (cola->usr.iddocumento[ind] == '9') {
        id[ind] = '1';
        break;
      } else if (cola->usr.iddocumento[ind] != '0') {
        id[ind] = cola->usr.iddocumento[ind] + 1;
        break;
      }
    }
  } else {
    for (int ind = 0; ind < LENIDDOC - 1; ind++) {
      if (ind == LENIDDOC - 2) {
        id[ind] = '1';
        break;
      } else
        id[ind] = '0';
    }
  }
}

/**
Funci�n: showusers_cursor
Argumentos: NODO *cabeza. Lista con los datos de usuarios a mostrar.
            int x, y. posicion de columna y fila a utilizar en la terminal.
            int cont_usr. Canidad de usuarios capturados.
objetivo: mostrar los datos del usuario realizando el efecto de scroll.
*/
void showusers_cursor(NODO_USR *cabeza, int x, int y, int cant_usr) {

  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY USUARIOS REGISTRADOS!!!\n");
    system("pause");
    return;
  }

  if (cant_usr < scroll)
    scroll = cant_usr;

  _setcursortype(0);
  system("cls");

  do {
    showusuarios_scroll(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_usr - 1;
        comienzo = cant_usr - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_usr - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC);
  _setcursortype(100);
}

/**
Funci�n: showusuarios_scroll.
Argumentos: NODO_USR *cabeza. Lista de usuarios a motrar. int x, y. posicion de
columna y fila a usar en la terminal. int Fil. indice del libro seleccionado al
momento de mostrar. int comienzo. indice desde donde se empezara a imprimir. int
mostrar. cantidad de datos a mostrar. Objetivo: Mostrar los usuarios desde la
posicion comienzo hasta mostrar, y resaltar el usuario en que se encuentra el
cursor en ese momento.
*/
void showusuarios_scroll(NODO_USR *cabeza, int x, int y, int fil, int comienzo,
                         int mostrar) {
#define CARACTERES_NM 8
#define CARACTERES_AP 10
  ScreenClear();

  char IDDOCUMENTO[] = {"IDDOCUMENTO"};
  char nombres[] = {"NOMBRES"};
  char apellidos[] = {"APELLIDOS"};
  char telefono[] = {"TELEFONO"};

  NODO_USR *nc, *nm;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;
  int nm_m = strlen(nc->usr.nombres), apl_m = strlen(nc->usr.apellidos);
  for (nm = nc; i < comienzo + mostrar; nm = nm->sig, i++) {
    int tempttl = strlen(nm->usr.nombres), tempedt = strlen(nm->usr.apellidos);
    if (tempttl > nm_m)
      nm_m = tempttl;
    if (tempedt > apl_m)
      apl_m = tempedt;
  }

  if (nm_m < CARACTERES_NM)
    nm_m = CARACTERES_NM;
  if (apl_m < CARACTERES_AP)
    apl_m = CARACTERES_AP;

  setcolor(YELLOW, BLACK);
  gotoxy(x, y);
  printf("%-*s%-*s%-*s%-*s", LENIDDOC, IDDOCUMENTO, nm_m + 1, nombres,
         apl_m + 1, apellidos, LENTELEFONO, telefono);

  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(WHITE, MAGENTA);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLACK, YELLOW);
    printf("%-*s%-*s%-*s%-*s", LENIDDOC, nc->usr.iddocumento, nm_m + 1,
           nc->usr.nombres, apl_m + 1, nc->usr.apellidos, LENTELEFONO,
           nc->usr.telefono);
  }
  colordefault();
}

/**
Funci�n: guardar_usuarios.
Argumento: NODO_USR *cabeza. primer nodo.
           FILE *pf. direcci�n del archivo de libros.
Objetivo: guardar todos los libros en la direcci�n proporcionada.
*/
void guardar_usuarios(NODO_USR *cabeza, FILE *pf) {
  if ((pf = fopen(ARCH_USR, "wb")) == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  for (NODO_USR *ind = cabeza; ind; ind = ind->sig)
    fwrite(&(ind->usr), sizeof(USUARIO), 1, pf);

  fclose(pf);
}

/**
Funci�n: showid_cursor
Argumento:NODO_LB *cabeza. direcci�n del primer nodo de la lista de libros
          int x. int y. posici�n del puntero.
          int cant_lb. cantidad de libros actuales.
Objetivo: Mostrar los id de los autores contenido en NODO_AT y guardar el
seleccionado en *idautora a la vez que se guarda el nombre y apellido del mismo.
return: 1 si se ha seleccionado un id y 0 en caso de que se haya cancelado.
*/
int showid_cursor(NODO_LB *cabeza, int x, int y, int cant_lb) {
  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY LIBROS REGISTRADOS!!!\n");
    system("pause");
    return (0);
  }

  if (cant_lb < scroll)
    scroll = cant_lb;

  _setcursortype(0);
  system("cls");

  do {
    showid_scroll_lb(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_lb - 1;
        comienzo = cant_lb - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_lb - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC && s != ENTER);
  _setcursortype(100);
  system("cls");

  if (s == ENTER)
    return (FIL);
  else
    return (0);
}

/**
Funci�n:MODbooks.
Argumento: NODO_LB *cabeza. direcci�n de memoria del puntero hacia el primer
nodo de la lista de libros. NODO_AT *cabeza_at. direcci�n de memoria del primer
nodo de la lista de autores. int cant_lb. cantidad total de libros. int cant_at.
cantidad total de autores. Objetivo: capturar una estructura libro y guardarla
en la lista de los libros
*/
void MODbooks(NODO_LB *cabeza, NODO_AT *cabeza_at, int cant_lb, int cant_at) {
  NODO_LB *ind;
  LIBRO lb;
  memset(&lb, 0, sizeof(LIBRO));
  char campofecha[STR_FECHA] = {0};

  ScreenClear();
  int book = showid_cursor(cabeza, 2, 4, cant_lb), i = 0;
  for (ind = cabeza; i < book; i++, ind = ind->sig)
    ;
  switch (opciones(SHOW_M_LIBRO)) {
  case 0: // ISBN
    gotoxy(2, 2);
    setcolor(YELLOW, BLACK);
    printf("INGRESE EL ISBN: ");
    if (capisbn(cabeza, lb.ISBN, 19, 2)) {
      strcpy(ind->lb.ISBN, lb.ISBN);
      return;
    }

    break;
  case 1: // TITULO
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("TITULO: ");
    if ((validador_campostr(lb.titulo, LENTITULO, 9, 4))) {
      strcpy(ind->lb.titulo, lb.titulo);
      return;
    }
    break;
  case 2: // AUTOR
    if (capidautora_books(lb.idautor, lb.editora, cabeza_at, 9, 4, cant_at)) {
      strcpy(ind->lb.idautor, lb.idautor);
      strcpy(ind->lb.editora, lb.editora);
      return;
    }
    break;
  case 3: // FECHA
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("Fecha de edici%cn(dd/mm/yyyy): ", 162);
    lb.fechaedicion = capfecha(campofecha, STR_FECHA, 32, 6);
    if (lb.fechaedicion.dd) {
      ind->lb.fechaedicion = lb.fechaedicion;
      return;
    }
  case 4: // EDICI�N
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("Edici%cn(#): ", 162);
    if ((lb.edicion = numerivo(14, 8))) {
      ind->lb.edicion = lb.edicion;
      return;
    }
  default:
    break;
  }
  colordefault();
  system("cls");
  printf("HAS CANCELADO LA MODIFICACION DEL LIBRO!!\n");
  system("pause");
}

/**
Funci�n: showid_scroll_at.
Argumento: NODO_AT *cabeza. puntero al primer nodo de la lista de autores.
           int n. cantidad de id. int (px) y (py).
           posicion de columna y fila del puntero en la terminal.
           int fil. fila seleccionada actualmente.
           int comienzo. dede que numero de nodo se mostrara.
           int mostrar. que cantidad de autores mostrar despues de comienzo.
Objetivo: mostrar todas los id del arreglo e identificar el id seleccionado.
*/
void showid_scroll_at(NODO_AT *cabeza, int x, int y, int fil, int comienzo,
                      int mostrar) {
  int size = 17;

  NODO_AT *nc;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  gotoxy(x, y);
  setcolor(BLACK, MAGENTA);
  printf("SELECCIONA EL ID");
  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(YELLOW, BLUE);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLUE, YELLOW);
    printf("%-*s", size, nc->at.idautor);
  }

  colordefault();
}

/**
Funci�n:MODautor.
Argumento: NODO_AT *cabeza. direcci�n de memoria del puntero hacia el primer
nodo de la lista de autores. int cant_at. cantidad total de autores. Objetivo:
capturar una estructura libro y guardarla en la lista de los autores
*/
void MODautor(NODO_AT *cabeza, int cant_at) {
  NODO_AT *ind;
  AUTOR at;
  memset(&at, 0, sizeof(AUTOR));
  char campofecha[STR_FECHA] = {0};

  int book = showid_cursor_at(cabeza, 2, 4, cant_at), i = 0;
  for (ind = cabeza; i < book; i++, ind = ind->sig)
    ;
  switch (opciones(SHOW_M_AUTOR)) {
  case 0: // NOMBRES
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("NOMBRES:");
    if ((validador_campostr(at.nombres, LENNOMB, 10, 4))) {
      strcpy(ind->at.nombres, at.nombres);
      return;
    }
    break;
  case 1: // APELLIDOS
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("APELLIDOS:");
    if ((validador_campostr(at.apellidos, LENAPEL, 12, 4))) {
      strcpy(ind->at.apellidos, at.apellidos);
      return;
    }
    break;
  case 2: // FECHA
    gotoxy(2, 8);
    setcolor(YELLOW, BLACK);
    printf("Fecha(dd/mm/yyyy):");
    at.fechanacimiento = capfecha(campofecha, STR_FECHA, 20, 8);
    if (at.fechanacimiento.dd) {
      ind->at.fechanacimiento = at.fechanacimiento;
      return;
    }
    break;
  default:
    break;
  }

  colordefault();
  system("cls");
  printf("HAS CANCELADO LA MODIFICACION DEL AUTOR!\n");
  system("pause");
}

/**
Funci�n: showid_cursor_at
Argumento:NODO_AT *cabeza. direcci�n del primer nodo de la lista de autores
          int x. int y. posici�n del puntero.
          int cant_at. cantidad de autores actuales.
Objetivo: Mostrar los id de los autores contenido en NODO_AT y retornar el
seleccionado. return: 1 si se ha seleccionado un id y 0 en caso de que se haya
cancelado.
*/
int showid_cursor_at(NODO_AT *cabeza, int x, int y, int cant_at) {
  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY AUTORES REGISTRADOS!!!\n");
    system("pause");
    return (0);
  }

  if (cant_at < scroll)
    scroll = cant_at;

  _setcursortype(0);
  system("cls");

  do {
    showid_scroll_at(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_at - 1;
        comienzo = cant_at - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_at - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC && s != ENTER);
  _setcursortype(100);
  system("cls");

  if (s == ENTER)
    return (FIL);
  else
    return (0);
}
/**
Funci�n: showfield.
Argumento: char *s. puntero a fila de caracteres a mostrar. int n. cantidad
           de caracteres a mostrar. int x y int y. posicion de fila y columa.
Objetivo: imprimir una fila de caracteres con los colores y tama�o
correspondientes.
*/
void showfield(char *s, int pos, int n, int x, int y) {

  setcolor(BLACK, WHITE);
  for (int ind = 0; ind < n; ind++) {
    gotoxy(x + ind + 1, y);
    if (s[ind])
      printf("%c", s[ind]);
    else
      printf(" ");
  }
  colordefault();
  gotoxy(x + pos + 1, y);

  return;
}

/**
Funci�n:MODusuario.
Argumento: NODO_USR *cabeza. direcci�n de memoria del puntero hacia el primer
nodo de la lista de usuarios. int cant_usr. cantidad total de usuarios.
Objetivo: capturar una estructura libro y guardarla en la lista de los usuarios
*/
void MODusuario(NODO_USR *cabeza, int cant_usr) {
  NODO_USR *ind;
  USUARIO usr;
  memset(&usr, 0, sizeof(USUARIO));
  char campofecha[STR_FECHA] = {0};

  int book = showid_cursor_at(cabeza, 2, 4, cant_usr), i = 0;
  for (ind = cabeza; i < book; i++, ind = ind->sig)
    ;
  switch (opciones(SHOW_M_AUTOR)) {
  case 0: // NOMBRES
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("NOMBRES:");
    if ((validador_campostr(usr.nombres, LENNOMB, 10, 4))) {
      strcpy(ind->usr.nombres, usr.nombres);
      return;
    }
    break;
  case 1: // APELLIDOS
    gotoxy(2, 4);
    setcolor(YELLOW, BLACK);
    printf("APELLIDOS:");
    if ((validador_campostr(usr.apellidos, LENAPEL, 12, 4))) {
      strcpy(ind->usr.apellidos, usr.apellidos);
      return;
    }
    break;
  case 2: // FECHA
    gotoxy(2, 8);
    setcolor(YELLOW, BLACK);
    printf("TELEFONO: ");
    if (numtelefono(usr.telefono, LENTELEFONO - 1, 12, 8)) {
      strcpy(ind->usr.telefono, usr.telefono);
      return;
    }

    break;
  default:
    break;
  }

  colordefault();
  system("cls");
  printf("HAS CANCELADO LA MODIFICACION DEL USUARIO!\n");
  system("pause");
}

/**
Funci�n: showid_cursor_usr
Argumento:NODO_USR *cabeza. direcci�n del primer nodo de la lista de usuarios
          int x. int y. posici�n del puntero.
          int cant_usr. cantidad de usuarios actuales.
Objetivo: Mostrar los id de los usuarios contenido en NODO_USR y retornar el
seleccionado. return: 1 si se ha seleccionado un id y 0 en caso de que se haya
cancelado.
*/
int showid_cursor_usr(NODO_USR *cabeza, int x, int y, int cant_usr) {
  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY USUARIOS REGISTRADOS!!!\n");
    system("pause");
    return (0);
  }

  if (cant_usr < scroll)
    scroll = cant_usr;

  _setcursortype(0);
  system("cls");

  do {
    showid_scroll_usr(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_usr - 1;
        comienzo = cant_usr - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_usr - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC && s != ENTER);
  _setcursortype(100);
  system("cls");

  if (s == ENTER)
    return (FIL);
  else
    return (0);
}

/**
Funci�n: showid_scroll_usr.
Argumento: NODO_USR *cabeza. puntero al primer nodo de la lista de usuarios.
           int n. cantidad de id. int (px) y (py).
           posicion de columna y fila del puntero en la terminal.
           int fil. fila seleccionada actualmente.
           int comienzo. dede que numero de nodo se mostrara.
           int mostrar. que cantidad de usuarios mostrar despues de comienzo.
Objetivo: mostrar todas los id del arreglo e identificar el id seleccionado.
*/
void showid_scroll_usr(NODO_USR *cabeza, int x, int y, int fil, int comienzo,
                       int mostrar) {
  char s[] = {"SELECCIONA EL USUARIO"};
  NODO_USR *nc;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  gotoxy(x, y);
  setcolor(BLACK, MAGENTA);
  printf("%-*s", LENIDDOC, s);
  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(YELLOW, BLUE);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLUE, YELLOW);
    printf("%-*s", LENIDDOC, nc->usr.iddocumento);
  }

  colordefault();
}

/**Funci�n: insertnodofin_prt.
Argumentos: NODO_PRT **cabeza. direcci�n de memoria de la cabeza del nodo de
prestamos. NODO_PRT **cola. direcci�n de memoria de la cabeza del nodo de
prestamos. LIBRO lb. cantidad total de prestamos. Objetivo: isertar el libro en
la ultima posici�n del nodo.
*/
void insertnodofin_prt(NODO_PRT **cabeza, NODO_PRT **cola, PRESTAMOS prt) {
  NODO_PRT *nuevo;

  nuevo = (NODO_PRT *)malloc(sizeof(NODO_PRT));

  nuevo->prt = prt;

  nuevo->sig = NULL;
  nuevo->ant = *cola;

  if (*cabeza == NULL)
    *cabeza = nuevo;
  if (*cola)
    (*cola)->sig = nuevo;
  *cola = nuevo;

  return;
}

/**
Funci�n: gets_prt.
Argumentos: FILE *pf. Puntero al file con los prestamos a leer.
            NODO_PRT **cabeza. direcci�n de memoria de la cabeza del nodo de
prestamos. NODO_PRT **cola. direcci�n de memoria de la cabeza del nodo de los
prestamos. Objetivo: Leer todos los prestamos desde el archivo proporcionado y
guardarlo en su nodo correspondiente
*/
int gets_prt(FILE *pf, NODO_PRT **cabeza, NODO_PRT **cola) {
  int cant = 0;
  NODO_PRT *IND = NULL;
  IND = (NODO_PRT *)malloc(sizeof(NODO_PRT));
  while (fread(&IND->prt, sizeof(LIBRO), 1, pf) == 1) {
    insertnodofin_prt(cabeza, cola, IND->prt);
    IND = (NODO_PRT *)malloc(sizeof(NODO_PRT));
    cant++;
  }

  return cant;
}

/**
Funci�n: Fecha_ACT.
Objetivo: Obtener una cadena de caractes con la fecha actual en el
          siguiente formato: (dd/mm/yyy).
*/
char *Fecha_ACT() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  char *fecha_actual = (char *)malloc(11 * sizeof(char));
  sprintf(fecha_actual, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);

  return fecha_actual;
}

/**Funci�n: prestar.
Argumento: NODO_PRT **cabeza. doble puntero del primer nodo de la lista de
prestamos. NODO_PRT **cola. doble puntero al ultimo nodo de la lista de
prestamos. NODO_LB *cabeza_lb. puntero al primer nodo de la lista de libros.
           NODO_USR *cabeza_usr. puntero al primer nodo de la lista de usuarios,
           int *cant_prt. puntero al total de prestamos.
           int cant_lb. total de libros.
           int cant_usr. total de usuarios.
Objetivo: prestar el libro seleccionado al usuario seleccionado e identificar si
es posible o no.
*/
void prestar(NODO_PRT **cabeza, NODO_PRT **cola, NODO_LB *cabeza_lb,
             NODO_USR *cabeza_usr, int *cant_prt, int cant_lb, int cant_usr) {
  NODO_USR *usuarios;
  NODO_LB *books;
  NODO_PRT *prestamo;
  PRESTAMOS prt;

  int i = 0;
  for (usuarios = cabeza_usr; i < showid_cursor_usr(cabeza_usr, 2, 4, cant_usr);
       usuarios = usuarios->sig)
    ;
  for (books = cabeza_lb, i = 0; i < showid_cursor(cabeza_lb, 2, 4, cant_lb);
       books = books->sig)
    ;

  for (prestamo = *cabeza; prestamo; prestamo = prestamo->sig)
    if (strcmp(prestamo->prt.ISBN, books->lb.ISBN) == 0) {
      perror("ERROR!! ESTE LIBRO ESTA PRESTADO\n");
      return;
    }

  strcpy(prt.ISBN, books->lb.ISBN);
  for (prestamo = *cabeza; prestamo; prestamo = prestamo->sig)
    if (strcmp(prestamo->prt.iddocumento, usuarios->usr.iddocumento) == 0) {
      perror("ERROR!! ESTE USUARIO DEBE UN LIBRO\n");
      return;
    }
  strcpy(prt.iddocumento, usuarios->usr.iddocumento);
  gotoxy(2, 4);
  printf("Fecha de prestamo: ");
  prt.fecprestamo = Capf_prestamo(Fecha_ACT(), STR_FECHA, 19, 4);
  if (prt.fecprestamo.dd) {
    gotoxy(2, 6);
    printf("Fecha de devoluci%cn: ", 162);
    prt.fecdevolucion = Capf_prestamo(Fecha_ACT(), STR_FECHA, 23, 6);
    if (prt.fecdevolucion.dd) {
      gotoxy(2, 8);
      printf("Dias de prestamo: ");
      if ((prt.diasprestamo = numerivo(20, 8))) {
        gotoxy(2, 10);
        printf("Monto del prestamo: ");
        if ((prt.montoprestamo = flotantes(22, 10))) {
          gotoxy(2, 12);
          printf("Recargo diario: ");
          if ((prt.recargodiario = flotantes(22, 12))) {
            *cant_prt += 2;
            insertnodofin_prt(cabeza, cola, prt);
            return;
          }
        }
      }
    }
  }

  ScreenClear();
  colordefault();
  system("cls");
  printf("HAS CANCELADO EL PRESTAMO!\n");
  system("pause");
}

/**
Funci�n: Capf_prestamo.
Argumento: char *str. Direcci�n de la fila o campo a capturar.
           int n. maximo caracteres a capturar. int (x) y (y).
           posicion de columna y fila del puntero en la terminal.
Objetivo: Capturar una fecha y evaluar si esta es correcta o no.
retorna: una estructura compuesta por 3 variables int, dias, mes y yyy.
*/
FECHA Capf_prestamo(char *str, int n, int x, int y) {
  int ind = 0, digitos = 0, validacion = 0;
  char chr;
  FECHA fecha;

  _setcursortype(100);
  do {
    if (validacion == 1) {
      validacion--;
      system("cls");
      gotoxy(2, y);
      printf("Fecha de prestamo: ");
    }
    showfield(str, ind, n, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != ESP);

    if (chr == DERECHA) {
      if (ind < n - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr != ENTER && chr != ESC) {
          if (chr == BKSP && isdigit(str[ind - 1])) {
            if (ind) {
              digitos--;
              ind--;
              str[ind] = ESP;
            }
          } else if (chr == BKSP)
            continue;
          else {
            if (ind < n && digitos < NUMEROS_FECHA) {
              digitos++;
              *(str + ind) = chr;
              if (ind == 1 || ind == 4)
                ind += 2;
              else
                ind++;
            }
          }
        }
      }
    }
    if (chr == ENTER) {
      fecha = evaluarfecha(str);
      if (!(fecha.dd)) {
        chr = 0;
        ind = 0;
        digitos = 0;
        validacion++;
        for (int ind = 0; ind < n; ind++)
          str[ind] = 0;
        gotoxy(2, 8);
        if (fecha.yyy == 0)
          printf("FECHA ERRONEA!!! INTENTE NUEVAMENTE:\n");
        system("pause");
        system("cls");
      } else
        return (fecha);
    }
    if (chr == ESC) {
      fecha.dd = 0;
      return (fecha);
    }

  } while (chr != ENTER);
  return fecha;
}

/**
Funci�n: flotantes.
Argumento:int (x) y (y).
          posicion de columna y fila del puntero en la terminal.
Objetivo: capturar un campo de digitos respectando las pautas recividas.
*/
float flotantes(int x, int y) {

  int ind = 0, puntos = 0, enteros = 0;
  char chr;
  int cant = 0, total = CANTINI;
  char *str = (char *)malloc(sizeof(char) * total);
  memset(str, 0, sizeof(str));
  if (!str) {
    printf("Error al asignar memoria");
    return -1;
  }

  _setcursortype(100);
  do {
    if (cant == total) {
      total += CANTINC;
      str = (char *)realloc(str, sizeof(char) * total);
      memset(str + cant, 0, sizeof(str));
    }
    showfield(str, ind, total, x, y);
    do {
      chr = getch();
    } while (!(isdigit(chr)) && chr != ENTER && chr != ESC &&
             chr != IZQUIERDA && chr != BKSP && chr != DERECHA && chr != PUNTO);

    if (chr == DERECHA) {
      if (ind < total - 1)
        ind++;
    } else {

      if (chr == IZQUIERDA) {
        if (ind > 0)
          ind--;
      } else {

        if (chr == BKSP) {
          if (ind) {
            ind--;
            total--;
            strcpy(str + ind, str + ind + 1);
          }
        } else if (chr != ENTER) {
          if (ind < total) {
            if ((!(isdigit(chr)) && !(puntos) && enteros) || isdigit(chr)) {
              if (!(isdigit(chr)))
                puntos++;
              enteros++;
              *(str + ind) = chr;
              ind++;
              cant++;
            }
          }
        }
      }
    }
  } while (chr != ENTER && chr != ESC);
  float edicion = atof(str);
  if (chr != ESC) {
    *(str + ind) = '\0';
    free(str);
    return (edicion);
  } else
    return (0);
}

/**
Funci�n: guardar_prestamos.
Argumento: NODO_PRT *cabeza. primer nodo.
           FILE *pf. direcci�n del archivo de prestamos.
Objetivo: guardar todos los prestamos en la direcci�n proporcionada.
*/
void guardar_prestamos(NODO_PRT *cabeza, FILE *pf) {

  if ((pf = fopen(ARCH_PRT, "wb")) == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
  }

  for (NODO_PRT *ind = cabeza; ind; ind = ind->sig)
    fwrite(&(ind->prt), sizeof(PRESTAMOS), 1, pf);

  fclose(pf);
}

/**
Funci�n: showprt_cursor
Argumentos: NODO_PRT *cabeza. Lista con los datos de prestamos a mostrar.
            int x, y. posicion de columna y fila a utilizar en la terminal.
            int cont_prt. Canidad de prestamos capturados.
objetivo: mostrar los datos del usuario realizando el efecto de scroll.
*/
void showprt_cursor(NODO_PRT *cabeza, int x, int y, int cant_prt) {

  int FIL = 0, comienzo = 0, scroll = SHOW_SCROLL;
  char s;

  gotoxy(x, y);
  if (!(cabeza)) {
    system("cls");
    printf("NO HAY PRESTAMOS REGISTRADOS!!!\n");
    system("pause");
    return;
  }

  if (cant_prt < scroll)
    scroll = cant_prt;

  _setcursortype(0);
  system("cls");

  do {
    showusuarios_scroll_prt(cabeza, x, y, FIL, comienzo, scroll);
    do {
      s = getch();
    } while (s != ESC && s != ABAJO && s != ARRIBA && s != ENTER);

    if (s == ARRIBA) {
      if (FIL != 0)
        FIL--;
      else {
        FIL = cant_prt - 1;
        comienzo = cant_prt - scroll - 1;
      }
      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

    if (s == ABAJO) {
      if (FIL < cant_prt - 1)
        FIL++;
      else {
        FIL = 0;
        comienzo = 0;
      }

      if (FIL > scroll + comienzo - 1)
        comienzo++;
      else if (FIL < comienzo)
        comienzo--;
      continue;
    }

  } while (s != ESC);
  _setcursortype(100);
}

/**
Funci�n: showusuarios_scroll_prt.
Argumentos: NODO_USR *cabeza. Lista de prestamos a motrar. int x, y. posicion de
columna y fila a usar en la terminal. int Fil. indice del prestamo seleccionado
al momento de mostrar. int comienzo. indice desde donde se empezara a imprimir.
            int mostrar. cantidad de datos a mostrar.
Objetivo: Mostrar los prestamos desde la posicion comienzo hasta mostrar, y
resaltar el prestamo en que se encuentra el cursor en ese momento.
*/
void showusuarios_scroll_prt(NODO_PRT *cabeza, int x, int y, int fil,
                             int comienzo, int mostrar) {
#define CARACTERES_FC 18
#define CARACTERES_FD 20
#define CARACTERES_15 15
  ScreenClear();

  char IDDOCUMENTO[] = {"IDDOCUMENTO"};
  char isbn[] = {"ISBN"};
  char fprestamo[] = {"FECHA DE PRESTAMO"};
  char fdevolucion[] = {"FECHA DE DEVOLUCION"};
  char diasprestamo[] = {"DIAS PRESTAMOS"};
  char recargodiario[] = {"RECARGO DIARIO"};

  NODO_PRT *nc;
  int i = 0;
  for (nc = cabeza; i < comienzo; nc = nc->sig, i++)
    ;

  setcolor(YELLOW, BLACK);
  gotoxy(x, y);
  printf("%-*s%-*s%-*s%-*s%-*s%-*s", LENIDDOC, IDDOCUMENTO, LENISBN + 1, isbn,
         CARACTERES_FC + 1, fprestamo, CARACTERES_FD, fdevolucion,
         CARACTERES_15, diasprestamo, CARACTERES_15, recargodiario);

  for (int ind = comienzo, j = 0; ind < mostrar + comienzo;
       ind++, j++, nc = nc->sig) {
    setcolor(WHITE, MAGENTA);
    gotoxy(x, y + j + 1);
    if (fil == ind)
      setcolor(BLACK, YELLOW);
    printf("%-*s%-*s%2hu/%2hu/%-4hu %2hu/%2hu/%-4hu%-*d%-*s", LENIDDOC,
           nc->prt.iddocumento, LENISBN, nc->prt.ISBN, nc->prt.fecprestamo.dd,
           nc->prt.fecprestamo.mm, nc->prt.fecprestamo.yyy,
           nc->prt.fecdevolucion.dd, nc->prt.fecdevolucion.mm,
           nc->prt.fecdevolucion.yyy, CARACTERES_15, nc->prt.diasprestamo,
           CARACTERES_15, nc->prt.recargodiario);
  }
  colordefault();
}
