# Build without virtualization

Your PC does not support virtualization (WSL2/Docker). You can still build in two ways:

---

## Option A: WSL1 (recommended – **no virtualization**)

WSL1 does not require Hyper-V or virtualization: it runs as a Windows subsystem.

### 1. Enable WSL1 only

Open **PowerShell as Administrator** and run:

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

Then **restart your PC**.

### 2. Set WSL1 as default

After restarting, open PowerShell again (normal) and run:

```powershell
wsl --set-default-version 1
```

### 3. Install Ubuntu

- Open **Microsoft Store**, search for **Ubuntu** (the one without a version number) and install it.
- Or run: `wsl --install -d Ubuntu` (if it asks for extra components, install only what is needed for WSL1).

### 4. First run of Ubuntu

- Open **Ubuntu** from the Start menu.
- Complete setup (username and password).
- Then install the required packages:

```bash
sudo apt update && sudo apt install -y build-essential binutils-arm-none-eabi git libpng-dev
```

### 5. Build the project

From the project folder in Windows (in WSL the path is `/mnt/c/Users/Administrator/Documents/pokefirered-master`):

```bash
cd /mnt/c/Users/Administrator/Documents/pokefirered-master
```

If the **agbcc** folder is missing or empty:

```bash
git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh ../pokefirered-master
cd ..
```

If **agbcc** is already there (e.g. you cloned it from Windows):

```bash
cd agbcc
./build.sh
./install.sh ..
cd ..
```

Then build:

```bash
make -j$(nproc) all
```

The generated ROM will be: **pokefirered.gba** in the same folder.

---

## Option B: MSYS2 (Windows only, no VM)

MSYS2 is a Unix-like environment that runs natively on Windows (no virtualization).

### 1. Install devkitPro (GBA only)

1. Download the installer: https://github.com/devkitPro/installer/releases  
2. Run the installer and on the components screen leave only **GBA Development**.  
3. Install to `C:\devkitPro` (default path).

### 2. Start devkitPro MSYS2

Open:

`C:\devkitPro\msys2\msys2_shell.bat`

### 3. Packages in MSYS2

In the MSYS2 shell:

```bash
pacman -S make gcc zlib-devel git
```

Then install libpng:

- Download: https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download  
- In the MSYS2 shell (adjust the path if you saved it elsewhere):

```bash
cd ~
# or cd /c/Users/Administrator/Downloads if it's in Downloads
tar xf libpng-1.6.37.tar.xz
cd libpng-1.6.37
./configure --prefix=/usr
make check
make install
cd ..
```

### 4. Build the project

Go to the project folder (e.g. on Windows `C:\Users\Administrator\Documents\pokefirered-master`):

```bash
cd /c/Users/Administrator/Documents/pokefirered-master
```

Clone and install agbcc (if you have not already):

```bash
git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh ..
cd ..
```

Then:

```bash
make -j$(nproc) all
```

The ROM will be **pokefirered.gba**.

---

## Summary

| Method   | Virtualization? | Notes                    |
|----------|------------------|--------------------------|
| **WSL1** | No              | Faster, recommended      |
| **MSYS2**| No              | Windows only, a bit slower |

If something fails, describe the error (you can paste the message) and we can fix it step by step.
