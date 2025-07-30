#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <io.h>

#define D88_HEADER_SIZE 17
#define MAX_PATH 128

int found_any = 0;  // D88 ?? ?? ??

void set_disk_name(const char *filepath, const char *filename_no_ext) {
    FILE *fp;
    unsigned char header[D88_HEADER_SIZE];
    int i;

    fp = fopen(filepath, "rb+");
    if (!fp) {
        printf("  [ERROR] ファイルが開けられません: %s\n", filepath);
        return;
    }

    fread(header, 1, D88_HEADER_SIZE, fp);

    // ?? ???? ?? (0x00 -> ??)
    printf("  %s  :  \"", filepath);
    for (i = 0; i < D88_HEADER_SIZE; i++) {
        char c = header[i];
        if (c == 0x00) c = ' ';
        else if (c < 32 || c > 126) c = ' '; // ????? ?? ??
        putchar(c);
    }

    // ???? ??? ? ??
    memset(header, 0x00, D88_HEADER_SIZE);
    strncpy((char *)header, filename_no_ext, 8);

    fseek(fp, 0, SEEK_SET);
    fwrite(header, 1, D88_HEADER_SIZE, fp);
    fclose(fp);

    // ? ???? ?? (?? 17??? ?? ?? ??)
    printf("\"  -->  \"");
    for (i = 0; i < D88_HEADER_SIZE; i++) {
        char c = header[i];
        if (c == 0x00) c = ' ';
        putchar(c);
    }
    printf("\"\n");

    found_any = 1;  // D88 ??? ????? ??
}

void process_directory(const char *path) {
    struct find_t fileinfo;
    char search[MAX_PATH];
    char filepath[MAX_PATH];
    char subpath[MAX_PATH];
    char name[13];
    char *dot;

    // D88 ?? ??
    sprintf(search, "%s\\*.D88", path);
    if (_dos_findfirst(search, _A_NORMAL, &fileinfo) == 0) {
        do {
            sprintf(filepath, "%s\\%s", path, fileinfo.name);

            // ?? ?? ???? ??? ??
            strncpy(name, fileinfo.name, 12);
            name[12] = '\0';
            dot = strchr(name, '.');
            if (dot) *dot = '\0';

            set_disk_name(filepath, name);
        } while (_dos_findnext(&fileinfo) == 0);
    }

    // ?? ?? ??
    sprintf(search, "%s\\*", path);
    if (_dos_findfirst(search, _A_SUBDIR, &fileinfo) == 0) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR) &&
                strcmp(fileinfo.name, ".") != 0 &&
                strcmp(fileinfo.name, "..") != 0) {

                sprintf(subpath, "%s\\%s", path, fileinfo.name);
                printf("\n[フォルダー変更] %s\n", subpath);
                process_directory(subpath);
            }
        } while (_dos_findnext(&fileinfo) == 0);
    }
}

int main(void) {
    printf("D88ファイルのディスク名処理プログラム v0.1     (c) windship 2025\n");
    printf("\n現在フォルダのD88ファイルのディスク名を処理します。\n");

    process_directory(".");

    if (!found_any) {
        printf("\nD88ファイルを発見できませんでした。\n");
        return 1;
    }

    printf("\nすべてのD88ファイルのディスク名を処理しました。\n");
    return 0;
}
