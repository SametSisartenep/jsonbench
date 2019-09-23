#include <u.h>
#include <libc.h>
#include <json.h>

enum {
	MB = 1024*1024
};

vlong t0, Δt;

void
usage(void)
{
	fprint(2, "usage: %s file\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	JSON *j;
	char buf[8*MB];
	int fd;

	JSONfmtinstall();
	ARGBEGIN{
	default: usage();
	}ARGEND;
	if(argc != 1)
		usage();
	fd = open(argv[0], OREAD);
	if(fd < 0)
		sysfatal("open: %r");
	if(read(fd, buf, sizeof buf) <= 0)
		sysfatal("read: %r");
	t0 = nsec();
	j = jsonparse(buf);
	Δt = nsec()-t0;
	fprint(2, "jsonparse took %lldns\n", Δt);
	if(j == nil)
		sysfatal("jsonparse: %r");
	t0 = nsec();
	print("%J\n", j);
	Δt = nsec()-t0;
	fprint(2, "jsonfmt took %lldns\n", Δt);
	exits(0);
}
