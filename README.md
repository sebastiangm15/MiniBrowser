# MiniBrowser

**MiniBrowser** este o aplicație scrisă în limbajul C ce simulează funcționalitățile de bază ale unui browser web.  
Proiectul implementează gestionarea taburilor, navigarea înainte și înapoi în istoric, deschiderea și închiderea taburilor, precum și afișarea conținutului curent.

---

## 📂 Structura proiectului

- **`main.c`** – punctul de intrare, gestionează comenzile citite din fișier și logica principală.  
- **`functions.c`** – implementări pentru operațiile pe liste, pagini și taburi.  
- **`stack.c`** – implementarea stivei pentru istoricul de navigare.  
- **`tab.c`** – inițializarea și configurarea taburilor.  
- **`functions.h`** – fișier header cu declarațiile structurilor și funcțiilor.  

---

## ⚙️ Funcționalități

- **Taburi multiple**: deschidere (`NEW_TAB`), închidere (`CLOSE`), comutare (`OPEN`), navigare între taburi (`PREV`, `NEXT`).  
- **Navigare în pagini**: accesarea unei pagini (`PAGE`), navigarea înapoi (`BACKWARD`) și înainte (`FORWARD`).  
- **Istoric**: afișarea istoricului de navigare pentru un tab (`PRINT_HISTORY`).  
- **Afișare taburi**: listarea taburilor curente și conținutul tabului activ (`PRINT`).  

---

## 🚀 Utilizare

### Compilare
Se compilează toate fișierele sursă:
```bash
gcc main.c functions.c stack.c tab.c -o minibrowser
