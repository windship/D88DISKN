# D88DISKN
D88 Disk Namer / Disk name adjust tool for D88 disk image file header 

Simple disk name adjusting tool for D88 disk image file header.

PC-8801 disk image format 'D88' has header information at the beginning of it.<br>
You can find more informations from this page: https://boukichi.github.io/HuDisk/DISK.html

<a href="https://archive.org/details/88emu-100">'D88SR'</a> PC-8801 emulator uses *.D88 images for its disk. You can use internal disk mount menu by vf4 key on the keyboard, but it uses DISK NAME only, not DISK IMAGE FILE NAME.<br>
If there's no disk name in D88 image's header, you can see nothing on the vf4 mount menu.<br>
You have to fix/adjust DISK NAME in header to see properly. 

Normally we retro gamers uses full rom set. I counted total disk image file number on my rom set, and it was over 3800.<br>
It will take veeeery long time if you edit every single file's header one by one. It's definitely painful.

This tool helps auto disk name adjusting by using disk image file name.<br>
No HEX editor needed, no manual edit needed.<br>
Try and enjoy!

<b>* Usage</b>
  
 1) Make a folder at where you want and just put D88DISKN.exe file into it. ex) **'B:\D88DISKN\D88DISKN.exe'**
 2) Set D88DISKN folder in your path from AUTOEXEC.BAT. ex) **'path=B:\;B:\D88DISKN;'**
 3) Reboot your PC-98 once to make your path setting enable.
 4) Go to the directory including D88 files what you want adjust disk name.
 5) Type 'D88DISKN' to execute. It will start to search *.D88 files in your current folder and its subfolders.<br>
    If D88 files found, it will change disk name space(first 17 bytes) to blank by filling '00' first, and replace it with D88 filename.
 6) If your D88 images have long file name, PC-98 DOS will use 'xxxxxx~1.D88' style shortened file name and D88DISKN will use it for disk name.

<b>* Copyright</p></b>
  I used ChatGPT for entire code of this.<br>
  I didn't programmed at all for this program, I just explained my idea and ordered to code it.<br>
  So I don't want to tell my copyright strongly. Just enjoy, fork and enhance it if you want :)
