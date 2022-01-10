#! /bin/bash
sudo mount disk2 /mnt
ls -a -i -l /mnt        # show . and .., inode #, long format
sudo umount /mnt