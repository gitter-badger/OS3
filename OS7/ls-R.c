#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
struct strbuf {
	char *ptr;
	size_t len;
};
void traverse(struct strbuf *buf);
void traverseSub(struct strbuf *buf, int first);
struct strbuf *strbuf_new(void);
void strbuf_realloc(struct strbuf *buf, size_t size);
void print_error(char *s) {
	fprintf(stderr, "%s: %s\n", s, strerror(errno));
}
void die (const char *s) {
	perror(s);
	exit(1);
}
int main(int argc, char *argv[]) {
	struct strbuf *pathbuf;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s dir\n", argv[0]);
		exit(1);
	}
	pathbuf = strbuf_new();
	strbuf_realloc(pathbuf, strlen(argv[1]));
	strcpy(pathbuf->ptr, argv[1]);
	traverse(pathbuf);
	exit(0);
}
void traverse(struct strbuf *pathbuf) {
	traverseSub(pathbuf, 1);
}
void traverseSub(struct strbuf *pathbuf, int first) {
	DIR *d;
	struct dirent *ent;
	struct stat st;
	d = opendir(pathbuf->ptr);
	if (!d) {
		switch (errno) {
			case ENOTDIR:
				return;
			case ENOENT:
				if (first) {
					die(pathbuf->ptr);
				} else {
					return;
				}
			case EACCES: /* permission error. just print and continue */
				puts(pathbuf->ptr);
				print_error(pathbuf->ptr);
				return;
			default:
				perror(pathbuf->ptr);
				exit(1);
		}
	}
	puts(pathbuf->ptr);
	while (ent = readdir(d)) {
		if (strcmp(ent->d_name, ".") == 0)
			continue;
		if (strcmp(ent->d_name, "..") == 0)
			continue;
		strbuf_realloc(pathbuf, pathbuf->len + 1 + strlen(ent->d_name) + 1);
		/* special handling for the root directory */
		if (strcmp(pathbuf->ptr, "/") != 0) {
			strcat(pathbuf->ptr, "/");
		}
		strcat(pathbuf->ptr, ent->d_name);
		if (lstat(pathbuf->ptr, &st) < 0) {
			switch (errno) {
				case ENOENT:
					break;
				case EACCES:
					print_error(pathbuf->ptr);
					break;
				default:
					die(pathbuf->ptr);
			}
		}
		else {
			if (S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode)) {
				traverseSub(pathbuf, 0);
			}
			else {
				puts(pathbuf->ptr);
			}
		}
		*strrchr(pathbuf->ptr, '/') = '\0';
	}
	closedir(d);
}
#define INITLEN 1024
struct strbuf * strbuf_new(void) {
	struct strbuf *buf;

	buf = (struct strbuf*)malloc(sizeof(struct strbuf));
	if (!buf) {
		die("malloc(3)");
	}
	buf->ptr = malloc(INITLEN);
	if (!buf->ptr) {
		die("malloc(3)");
	}
	buf->len = INITLEN;
	return buf;
}
void strbuf_realloc(struct strbuf *buf, size_t len) {
	char *tmp;
	if (buf->len > len)
		return;
	tmp = realloc(buf->ptr, len);
	if (!tmp) {
		die("realloc(3)");
	}
	buf->ptr = tmp;
	buf->len = len;
}
