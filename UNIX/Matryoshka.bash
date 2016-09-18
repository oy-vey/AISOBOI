dd if=/dev/zero of=drive-image count=512M #apparent-size=??? actual-size=???
mke2fs -t ext2 -q drive-image #apparent-size=??? actual-size=???
mkdir home/oracle/matryoshka
sudo mount -o loop=/dev/loop0 drive-image home/oracle/matryoshka
cd home/oracle/matryoshka
mkdir aaa bbb ccc

###
dd of=drive-image-sparse bs=1 seek=512M count=0 # apparent-size=512M, actual-size=0M
mke2fs -t ext2 -q drive-image-sparse # apparent-size=512M, actual-size=???M
mkdir home/oracle/matryoshka-sparse
sudo mount -o loop=/dev/loop0 drive-image-sparse home/oracle/matryoshka-sparse
