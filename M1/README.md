# M1
In this laboratory exercise, I have implemented the [pstree.c](./M1/pstree.c), which is a program capable of displaying the user's running processes in a tree-like structure. The program offers several command-line arguments to customize the output:
```
         -p         show pids,PIDS are shown as decimal numbers.
         -t         hidden threads and only show the processes.
         -n         sort processes with the same parent by PID.
for example:
        ./pstree-64 [-p] [-n] [-t]
```
you can also add pid to the end of the command , to only display the sub-tree with a specific root process whose pid is at the end of the command.
```
        ./pstree-64 [-p] [-t] [-n] pid 
```
## Problems 
### P1
Before beginning your laboratory work in Linux, it is essential to have a clear understanding of how proceeses are saved. All processes are stored in a directory called "/proc" as subdirectories,identified by their porcess IDs.For instance , a process with ID 1 would be stored in "/proc/1" , and a process with ID 2 would be stored in "/proc/2", and so on.

To access  process information , run the following command:
        
        vim /proc/{pid}/status

Upon running this command , a file containing essential information about the process will be displayed . 
         
        file information

The following information is particularly important:
- Pid: the process ID
- Tgid: the process group ID
- PPid: the parent  process ID
- Name: the process name


Furthermore,all Threads are save in the directory "/proc/{pid}/task". The directory structure is as follow:

        /proc/{pid}/task
                        /{tid}
                        /{tid}
                        /{tid}
                        ...

Each subdirctory corresponds to a thread , identified by its thread ID(tid). Understanding these file structures and commands is crucial for efficient and effective work of Linux processes and threads .


## Example

### E0
```
./pstree-64 -t
──systemd─┬─systemd-journal
          ├─vmware-vmblock-
          ├─systemd-udevd
          ├─systemd-oomd
          ├─systemd-resolve
          ├─systemd-timesyn
          ├─VGAuthService
          ├─vmtoolsd
          ├─accounts-daemon
          ├─acpid
          ├─avahi-daemon───avahi-daemon
          ├─bluetoothd
          ├─cron
          ├─dbus-daemon
          ├─NetworkManager
          ├─irqbalance
          ├─networkd-dispat
          ├─polkitd
          ├─power-profiles-
          ├─rsyslogd
          ├─snapd
          ├─switcheroo-cont
          ├─systemd-logind
          ├─udisksd
          ├─wpa_supplicant
          ├─ModemManager
          ├─cupsd───dbus
          ├─unattended-upgr
          ├─gdm3───gdm-session-wor───gdm-wayland-ses───gnome-session-b
          ├─cups-browsed
          ├─kerneloops
          ├─kerneloops
          ├─systemd─┬─(sd-pam)
          │         ├─pipewire
          │         ├─pipewire-media-
          │         ├─pulseaudio
          │         ├─snapd-desktop-i───snapd-desktop-i
          │         ├─dbus-daemon
          │         ├─gvfsd───gvfsd-trash
          │         ├─gvfsd-fuse
          │         ├─gnome-session-c
          │         ├─gnome-session-b─┬─at-spi-bus-laun───dbus-daemon
          │         │                 ├─gsd-disk-utilit
          │         │                 ├─evolution-alarm
          │         │                 └─update-notifier
          │         ├─gnome-shell─┬─Xwayland
          │         │             └─gjs
          │         ├─xdg-document-po───fusermount3
          │         ├─xdg-permission-
          │         ├─xdg-desktop-por
          │         ├─xdg-desktop-por
          │         ├─gnome-shell-cal
          │         ├─evolution-sourc
          │         ├─goa-daemon
          │         ├─dconf-service
          │         ├─gvfs-udisks2-vo
          │         ├─evolution-calen
          │         ├─gvfs-mtp-volume
          │         ├─gvfs-gphoto2-vo
          │         ├─gvfs-goa-volume
          │         ├─evolution-addre
          │         ├─goa-identity-se
          │         ├─gvfs-afc-volume
          │         ├─at-spi2-registr
          │         ├─gjs
          │         ├─sh───ibus-daemon─┬─ibus-memconf
          │         │                  ├─ibus-extension-
          │         │                  └─ibus-engine-sim
          │         ├─gsd-a11y-settin
          │         ├─gsd-color
          │         ├─gsd-datetime
          │         ├─gsd-housekeepin
          │         ├─gsd-keyboard
          │         ├─gsd-media-keys
          │         ├─gsd-power
          │         ├─gsd-print-notif
          │         ├─gsd-rfkill
          │         ├─gsd-screensaver
          │         ├─gsd-sharing
          │         ├─gsd-smartcard
          │         ├─gsd-sound
          │         ├─gsd-wacom
          │         ├─ibus-portal
          │         ├─vmtoolsd
          │         ├─gsd-printer
          │         ├─gvfsd-metadata
          │         ├─snap-store
          │         ├─tracker-miner-f
          │         ├─xdg-desktop-por
          │         ├─gjs
          │         ├─gsd-xsettings
          │         ├─ibus-x11
          │         ├─gnome-terminal-─┬─bash───vim
          │         │                 └─bash───pstree-64
          │         ├─code─┬─code───code
          │         │      ├─code───code
          │         │      ├─code
          │         │      ├─code─┬─cpptools
          │         │      │      ├─code
          │         │      │      └─code
          │         │      ├─code───code
          │         │      └─code
          │         ├─chrome_crashpad
          │         └─cpptools-srv
          ├─gnome-keyring-d
          ├─rtkit-daemon
          ├─upowerd
          ├─packagekitd
          ├─colord
          └─fwupd
```
### E1
```
./pstree -p 2263

code(2263)─┬─{sandbox_ipc_thr}(2264)
           ├─{ThreadPoolServi}(2267)
           ├─{ThreadPoolForeg}(2269)
           ├─{Chrome_IOThread}(2270)
           ├─{MemoryInfra}(2271)
           ├─{code}(2272)
           ├─{code}(2273)
           ├─{code}(2274)
           ├─{code}(2275)
           ├─{code}(2276)
           ├─{ThreadPoolSingl}(2281)
           ├─{Bluez}(2282)
           ├─{CrShutdownDetec}(2283)
           ├─{gmain}(2284)
           ├─{dconf}(2285)
           ├─{gdbus}(2286)
           ├─{inotify_reader}(2288)
           ├─{ThreadPoolSingl}(2291)
           ├─{CompositorTileW}(2293)
           ├─{VideoCaptureThr}(2294)
           ├─{code}(2296)
           ├─{code}(2297)
           ├─{code}(2298)
           ├─{code}(2299)
           ├─{code}(2300)
           ├─{ThreadPoolSingl}(2310)
           ├─{CacheThread_Blo}(2341)
           ├─{code}(2355)
           ├─code(2265)───code(2364)─┬─{Thread<00>}(2366)
           │                         ├─{Thread<01>}(2367)
           │                         ├─{code}(2368)
           │                         ├─{ThreadPoolServi}(2369)
           │                         ├─{Chrome_ChildIOT}(2371)
           │                         ├─{ThreadPoolForeg}(2372)
           │                         └─{VizCompositorTh}(2373)
           ├─code(2266)───code(2342)─┬─{ThreadPoolServi}(2343)
           │                         ├─{Chrome_ChildIOT}(2345)
           │                         ├─{GpuMemoryThread}(2347)
           │                         ├─{ThreadPoolForeg}(2348)
           │                         ├─{Compositor}(2351)
           │                         ├─{ThreadPoolSingl}(2352)
           │                         ├─{CompositorTileW}(2353)
           │                         ├─{CompositorTileW}(2354)
           │                         ├─{DedicatedWorker}(2436)
           │                         ├─{MemoryInfra}(2445)
           │                         ├─{WebCrypto}(2450)
           │                         ├─{ThreadPoolForeg}(2580)
           │                         └─{ThreadPoolForeg}(2587)
           ├─code(2309)─┬─{ThreadPoolServi}(2319)
           │            ├─{Chrome_ChildIOT}(2321)
           │            ├─{ThreadPoolForeg}(2323)
           │            └─{inotify_reader}(2324)
           ├─code(2377)─┬─{ThreadPoolServi}(2378)
           │            ├─{ThreadPoolForeg}(2379)
           │            ├─{Chrome_ChildIOT}(2380)
           │            ├─{code}(2382)
           │            ├─{code}(2383)
           │            ├─{code}(2384)
           │            ├─{code}(2385)
           │            ├─{code}(2386)
           │            ├─{code}(2409)
           │            ├─{code}(2410)
           │            ├─{code}(2411)
           │            ├─{code}(2412)
           │            ├─{code}(2413)
           │            ├─cpptools(2437)─┬─{cpptools}(2438)
           │            │                ├─{cpptools}(2439)
           │            │                ├─{cpptools}(2440)
           │            │                ├─{cpptools}(2441)
           │            │                ├─{cpptools}(2442)
           │            │                ├─{cpptools}(2443)
           │            │                ├─{cpptools}(2511)
           │            │                ├─{cpptools}(2512)
           │            │                ├─{cpptools}(2513)
           │            │                ├─{cpptools}(2514)
           │            │                └─{cpptools}(2552)
           │            ├─code(2451)─┬─{ThreadPoolServi}(2456)
           │            │            ├─{ThreadPoolForeg}(2457)
           │            │            ├─{code}(2458)
           │            │            ├─{code}(2459)
           │            │            ├─{code}(2460)
           │            │            ├─{code}(2461)
           │            │            └─{code}(2462)
           │            └─code(2503)─┬─{ThreadPoolServi}(2504)
           │                         ├─{ThreadPoolForeg}(2505)
           │                         ├─{code}(2506)
           │                         ├─{code}(2507)
           │                         ├─{code}(2508)
           │                         ├─{code}(2509)
           │                         ├─{code}(2510)
           │                         └─{code}(2526)
           ├─code(2387)─┬─{ThreadPoolServi}(2389)
           │            ├─{ThreadPoolForeg}(2390)
           │            ├─{Chrome_ChildIOT}(2391)
           │            ├─{code}(2394)
           │            ├─{code}(2395)
           │            ├─{code}(2396)
           │            ├─{code}(2397)
           │            ├─{code}(2407)
           │            ├─{code}(2419)
           │            ├─{code}(2420)
           │            ├─{code}(2421)
           │            ├─{code}(2422)
           │            ├─{code}(2423)
           │            └─code(2424)─┬─{ThreadPoolServi}(2425)
           │                         ├─{ThreadPoolForeg}(2426)
           │                         ├─{code}(2427)
           │                         ├─{code}(2428)
           │                         ├─{code}(2429)
           │                         ├─{code}(2430)
           │                         ├─{code}(2431)
           │                         ├─{code}(2432)
           │                         ├─{code}(2433)
           │                         ├─{code}(2434)
           │                         └─{code}(2435)
           └─code(2388)─┬─{ThreadPoolServi}(2398)
                        ├─{Chrome_ChildIOT}(2400)
                        ├─{ThreadPoolForeg}(2401)
                        ├─{code}(2403)
                        ├─{code}(2404)
                        ├─{code}(2405)
                        ├─{code}(2406)
                        ├─{code}(2408)
                        ├─{code}(2414)
                        ├─{code}(2415)
                        ├─{code}(2416)
                        ├─{code}(2417)
                        ├─{code}(2418)
                        ├─{code}(2519)
                        └─{code}(2520)
```