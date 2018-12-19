cmd_init/halt.o := arm-linux-gcc -Wp,-MD,init/.halt.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/home/flinn/mini2440/package/busybox-1.7.0/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=KBUILD_STR(1.7.0)" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes  -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -Wdeclaration-after-statement     -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(halt)"  -D"KBUILD_MODNAME=KBUILD_STR(halt)" -c -o init/halt.o init/halt.c

deps_init/halt.o := \
  init/halt.c \
    $(wildcard include/config/init.h) \
    $(wildcard include/config/feature/initrd.h) \
    $(wildcard include/config/feature/clean/up.h) \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/ture/ipv6.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/gunzip.h) \
    $(wildcard include/config/ktop.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/ture/editing/savehistory.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/inux.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config///.h) \
    $(wildcard include/config//nommu.h) \
    $(wildcard include/config//mmu.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/byteswap.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/byteswap.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/endian.h \
    $(wildcard include/config/.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/features.h \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/tify/level.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ern/inlines.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/gnu/stubs.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/endian.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/arpa/inet.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netinet/in.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdint.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/wchar.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/wordsize.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/socket.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/uio.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/types.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/types.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/include/stddef.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/typesizes.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/time.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/select.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/select.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigset.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/time.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/sysmacros.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/pthreadtypes.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sched.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/uio.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/socket.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/include/limits.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/include/syslimits.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/limits.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix1_lim.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/local_lim.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/limits.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix2_lim.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/xopen_lim.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/stdio_lim.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sockaddr.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/socket.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/sockios.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/in.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/include/stdbool.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/mount.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ioctl.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/ioctls.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/ioctls.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/ioctl.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/ioctl-types.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ttydefaults.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/ctype.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/xlocale.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/dirent.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/dirent.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/errno.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/errno.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/errno.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/errno.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/fcntl.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/fcntl.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/stat.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/stat.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/inttypes.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/mntent.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdio.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/paths.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/netdb.h \
    $(wildcard include/config/3/ascii/rules.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/rpc/netdb.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/siginfo.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/netdb.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/setjmp.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/setjmp.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/signal.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/signum.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigaction.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigcontext.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/sigcontext.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigstack.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/ucontext.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/procfs.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/time.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/user.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sigthread.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/libio.h \
    $(wildcard include/config/a.h) \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/_G_config.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/wchar.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/gconv.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/include/stdarg.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/sys_errlist.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/stdlib.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/waitflags.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/waitstatus.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/alloca.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/mman.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/mman.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/statfs.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/statfs.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/wait.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/resource.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/resource.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/termios.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/termios.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/unistd.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/posix_opt.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/environments.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/confname.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/getopt.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/utime.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/locale.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/bits/locale.h \
  include/pwd_.h \
    $(wildcard include/config/use/bb/pwd/grp.h) \
  include/grp_.h \
  include/shadow_.h \
    $(wildcard include/config/use/bb/shadow.h) \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/param.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/linux/param.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/asm/param.h \
  include/xatonum.h \
  /usr/local/bin/3.4.5/bin/../lib/gcc/arm-linux/3.4.5/../../../../arm-linux/sys-include/sys/reboot.h \
    $(wildcard include/config/cad.h) \

init/halt.o: $(deps_init/halt.o)

$(deps_init/halt.o):
