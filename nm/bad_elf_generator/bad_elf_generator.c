#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>

#define ERROR_MAGIC "error_magic"
#define ERROR_CLASS "error_class"
#define ERROR_DATA "error_data"
#define NO_ERROR    "no_error"

typedef struct {
    void *mapped;
    size_t size;
} MappedFile;

// Fonction pour mapper un fichier ELF en mémoire
MappedFile get_mapped_file_memory(const char *file_name) {
    int fd = open(file_name, O_RDWR);  
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat filestat;
    if (fstat(fd, &filestat) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    void *mapped = mmap(NULL, filestat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    MappedFile mf = {mapped, filestat.st_size};
    return mf;
}

void save_modified_executable(MappedFile mf, const char *new_name) {
    int fd = open(new_name, O_CREAT | O_WRONLY, 0755);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, mf.mapped, mf.size) != mf.size) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

void backup_elf(void *backup, const void *original, size_t size) {
    memcpy(backup, original, size);  // Sauvegarde l'état initial
}

void restore_elf(void *original, const void *backup, size_t size) {
    memcpy(original, backup, size);  // Restaure l'état initial
}

// Injection d'erreurs dans le fichier ELF
// Injection d'erreurs dans le fichier ELF
void inject_error_magic(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size); 
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    ehdr->e_ident[EI_MAG0] = 0x00;  // Mauvais Magic
    save_modified_executable(mf, "error_magic");
}

void inject_error_class(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);  
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    ehdr->e_ident[EI_CLASS] = ELFCLASSNONE;  // Mauvais Class
    save_modified_executable(mf, "error_class");
}

void inject_error_data(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size); 
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    ehdr->e_ident[EI_DATA] = ELFDATANONE;  // Mauvais Data Encoding
    save_modified_executable(mf, "error_data");
}


// Erreur sur l'offset de la table des sections (e_shoff)
void inject_error_shoff(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    ehdr->e_shoff = 0xFFFFFFFFFFFFFFFF;  // Offset de la table des sections hors limites
    save_modified_executable(mf, "error_shoff");
}

// Erreur sur le nombre de sections (e_shnum)
void inject_error_shnum(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    ehdr->e_shnum = 0xFFFF;  // Nombre de sections invalide
    save_modified_executable(mf, "error_shnum");
}

// Erreur sur le nombre de symboles (dans la section symtab)
void inject_error_symtab_size(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);
    Elf64_Shdr *section_headers = (Elf64_Shdr *)((char *)mf.mapped + ((Elf64_Ehdr *)mf.mapped)->e_shoff);
    
    // Trouver la section symtab et corrompre la taille
    for (int i = 0; i < ((Elf64_Ehdr *)mf.mapped)->e_shnum; i++) {
        if (section_headers[i].sh_type == SHT_SYMTAB) {
            section_headers[i].sh_size = 0xFFFFFFFF;  // Taille de la table des symboles invalide
            break;
        }
    }
    save_modified_executable(mf, "error_symtab_size");
}

void inject_error_symtab_section_header(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)mf.mapped;
    Elf64_Shdr *section_headers = (Elf64_Shdr *)((char *)mf.mapped + ehdr->e_shoff);
    
    // Trouver la section symtab et la supprimer
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (section_headers[i].sh_type == SHT_SYMTAB) {
            memset(&section_headers[i], 0, sizeof(Elf64_Shdr));
            break;
        }
    }
    save_modified_executable(mf, "error_no_symtab_section_header");
}

// Fichier sans erreurs
void elf_with_no_error(MappedFile mf, void *backup) {
    restore_elf(mf.mapped, backup, mf.size);  
    save_modified_executable(mf, "no_error");
}

int main() {
    MappedFile mf = get_mapped_file_memory("executable_file");

    void *backup = malloc(mf.size);
    if (!backup) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    backup_elf(backup, mf.mapped, mf.size);

    inject_error_magic(mf, backup);
    inject_error_class(mf, backup);
    inject_error_data(mf, backup);
    inject_error_shnum(mf, backup);
    inject_error_symtab_section_header(mf, backup);
    elf_with_no_error(mf, backup);

    free(backup);
    if (munmap(mf.mapped, mf.size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    printf("Les exécutables modifiés ont été créés avec succès.\n");
    return 0;
}