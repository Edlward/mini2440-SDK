# mini2440-SDK
 SDK for mini2440
 
 1> 支持Nor 启动， tftp烧写    
 2> 支持Nand启动         
 3> 支持jffs2文件系统         
 4> 支持yaffs2文件系统      
 
 mini2440 从u-boot-> kernel->fs->driver   
 
u-boot   
  make mini2440_config    
  make all  
  
kernel   
  make s3c2410_defconfig
  make menuconfig    
    File system --->    
      Miscellaneous filesystem --->   
        <*> YAFFS2 filesystem support   
  make uImage   
  
ftp烧写：
kernel：
  tftp 30000000 uImage  
  nand erase 0x00060000 0x200000   
  nand write.jffs2 30000000 0x60000 0x200000  
fs：  
  tftp 30000000 fs_mini_mdev.yaffs2  
  tftp erase root   
  nand write.jffs2 30000000 0x260000 889bc0   
  
nfs :
bootloader:
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/u-boot.bin       
  nand erase bootloader      
  nand write.jffs2 30000000 bootloader         
  
kernel :     
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/uImage    
  nand erase 0x60000 0x200000         
  nand write.jffs2 30000000 0x60000 0x200000      
  // nand erase kernel ; nand write.jffs2 30000000 kernel         


fs-yaffs2:        
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.yaffs2         
  nand erase root           
  nand write.yaffs 30000000 0x260000 85d640         

fs-jffs2     
  nfs 30000000 192.168.1.133:/home/flinn/mini2440/bin/rootfs.jffs2        
  nand erase root     
  nand write.jffs2 30000000 260000 $filesize        
  set bootargs console=ttySAC0,115200 root=/dev/mtdblock3 rootfstype=jffs2        

nfs-start :
  // see Documents/nfsroot.txt in linux kernel         
  set bootargs noinitrd root=/dev/nfs nfsroot=192.168.1.133:/home/flinn/mini2440/rootfs/mini_mdev_fs   ip=192.168.1.123:192.168.1.133:192.168.1.1:255.255.255.0::eth0:off init=/linuxrc console=ttySAC0      
  save
  
  
分区信息 ：   
  0x00000000-0x00040000 : "bootloader"       
  0x00040000-0x00060000 : "params"        
  0x00060000-0x00260000 : "kernel"           
  0x00260000-0x10000000 : "root"        
<<<<<<< HEAD
>>>>>>> 8a45597c758acfcf1dab7d06152acbd00471b19e
=======
>>>>>>> 8a45597c758acfcf1dab7d06152acbd00471b19e
