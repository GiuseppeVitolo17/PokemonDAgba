# Build senza virtualizzazione

Il PC non supporta la virtualizzazione (WSL2/Docker). Puoi compilare comunque in due modi:

---

## Opzione A: WSL1 (consigliata – **non usa virtualizzazione**)

WSL1 non richiede Hyper-V né virtualizzazione: funziona come sottosistema Windows.

### 1. Abilita solo WSL1

Apri **PowerShell come Amministratore** ed esegui:

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

Poi **riavvia il PC**.

### 2. Imposta WSL1 come predefinito

Dopo il riavvio, apri di nuovo PowerShell (normale) e esegui:

```powershell
wsl --set-default-version 1
```

### 3. Installa Ubuntu

- Apri **Microsoft Store**, cerca **Ubuntu** (quello senza numero di versione) e installalo.
- Oppure: `wsl --install -d Ubuntu` (se ti chiede componenti aggiuntivi, installa solo ciò che serve per WSL1).

### 4. Prima apertura di Ubuntu

- Apri **Ubuntu** dal menu Start.
- Completa la configurazione (username e password).
- Poi installa i pacchetti necessari:

```bash
sudo apt update && sudo apt install -y build-essential binutils-arm-none-eabi git libpng-dev
```

### 5. Build del progetto

Dalla cartella del progetto in Windows (in WSL il percorso è `/mnt/c/Users/Administrator/Documents/pokefirered-master`):

```bash
cd /mnt/c/Users/Administrator/Documents/pokefirered-master
```

Se la cartella **agbcc** non c’è o è vuota:

```bash
git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh ../pokefirered-master
cd ..
```

Se **agbcc** c’è già (es. l’hai clonato da Windows):

```bash
cd agbcc
./build.sh
./install.sh ..
cd ..
```

Poi compila:

```bash
make -j$(nproc) all
```

La ROM generata sarà: **pokefirered.gba** nella stessa cartella.

---

## Opzione B: MSYS2 (solo Windows, nessuna VM)

MSYS2 è un ambiente tipo Unix che gira nativo su Windows (nessuna virtualizzazione).

### 1. Installa devkitPro (solo GBA)

1. Scarica l’installer: https://github.com/devkitPro/installer/releases  
2. Esegui l’installer e nella schermata componenti lascia solo **GBA Development**.  
3. Installa in `C:\devkitPro` (percorso predefinito).

### 2. Avvia MSYS2 di devkitPro

Apri:

`C:\devkitPro\msys2\msys2_shell.bat`

### 3. Pacchetti in MSYS2

Nella shell MSYS2:

```bash
pacman -S make gcc zlib-devel git
```

Poi installa libpng:

- Scarica: https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.xz/download  
- Nella shell MSYS2 (adattando il percorso se lo salvi altrove):

```bash
cd ~
# oppure cd /c/Users/Administrator/Downloads se l’hai in Download
tar xf libpng-1.6.37.tar.xz
cd libpng-1.6.37
./configure --prefix=/usr
make check
make install
cd ..
```

### 4. Build del progetto

Vai nella cartella del progetto (es. in Windows è `C:\Users\Administrator\Documents\pokefirered-master`):

```bash
cd /c/Users/Administrator/Documents/pokefirered-master
```

Clona e installa agbcc (se non l’hai già fatto):

```bash
git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh ..
cd ..
```

Poi:

```bash
make -j$(nproc) all
```

La ROM sarà **pokefirered.gba**.

---

## Riepilogo

| Metodo  | Virtualizzazione? | Note                    |
|--------|--------------------|-------------------------|
| **WSL1** | No                 | Più veloce, consigliato |
| **MSYS2** | No                 | Solo Windows, un po’ più lento |

Se qualcosa non va, descrivi l’errore (anche incollando il messaggio) e si può correggere passo passo.
