# File Monitoring Program

A program to monitor file changes in a specific directory and handle them appropriately.

## Compilation

The program can be compiled using the provided ./build.sh script. Simply run the following command in the terminal:


```bash
./build.sh
```

This will compile all the necessary source files and produce an executable named file-monitor.
## Usage

After compiling the program, you can run it with the following command:

```bash
./file-monitor <directory_path>
```

Replace <directory_path> with the path to the directory you want to monitor.

The program will run in the background and monitor the specified directory for file changes. Whenever a new file is created or an existing file is modified, the program will log the event in a file named /var/log/file-monitor/log-YYYY-MM-DD.log, where YYYY-MM-DD is the current date. The program will also automatically remove log files older than 7 days.