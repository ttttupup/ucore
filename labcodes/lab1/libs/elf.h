#ifndef __LIBS_ELF_H__
#define __LIBS_ELF_H__

#include <defs.h>

#define ELF_MAGIC    0x464C457FU            // "\x7FELF" in little endian

/* file header */
struct elfhdr {
    uint32_t e_magic;     // must equal ELF_MAGIC   elf魔数
    uint8_t e_elf[12];
    uint16_t e_type;      // 1=relocatable, 2=executable, 3=shared object, 4=core image   文件类型，1 = 可重定位的，2 = 可执行的，3 = 共享的，4 = 核心的
    uint16_t e_machine;   // 3=x86, 4=68K, etc.  机器的指令集结构，例如 0x03 代表 x86，0x08 代表 MIPS 等
    uint32_t e_version;   // file version, always 1  ELF 文件版本
    uint32_t e_entry;     // entry point if executable  程序入口的地址
    uint32_t e_phoff;     // file position of program header or 0   program header table 的偏移地址
    uint32_t e_shoff;     // file position of section header or 0   section header table 的偏移地址
    uint32_t e_flags;     // architecture-specific flags, usually 0   与机器的架构相关的值
    uint16_t e_ehsize;    // size of this elf header                   ELF header 大小
    uint16_t e_phentsize; // size of an entry in program header        program header table 条目大小
    uint16_t e_phnum;     // number of entries in program header or 0  program header table 条目数量
    uint16_t e_shentsize; // size of an entry in section header        section header table 条目大小
    uint16_t e_shnum;     // number of entries in section header or 0   section header table 条目数量
    uint16_t e_shstrndx;  // section number that contains section name strings    含有 section 名称的条目索引
};

/* program section header */   // program header table 程序头表
struct proghdr {
    uint32_t p_type;   // loadable code or data, dynamic linking info,etc.   // program header 类型
    uint32_t p_offset; // file offset of segment                  // 相对于文件的偏移地址
    uint32_t p_va;     // virtual address to map segment          // 虚拟地址
    uint32_t p_pa;     // physical address, not used            // 物理地址
    uint32_t p_filesz; // size of segment in file                  // 在文件中的大小
    uint32_t p_memsz;  // size of segment in memory (bigger if contains bss）  // 在内存中的大小
    uint32_t p_flags;  // read/write/execute bits                          // 相关的标志
    uint32_t p_align;  // required alignment, invariably hardware page size  // 对齐方式
};

#endif /* !__LIBS_ELF_H__ */

