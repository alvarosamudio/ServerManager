# Server Manager

Server Manager is a simple yet powerful graphical utility designed to manage local web server services on Linux systems. It provides an intuitive interface to start, stop, restart, and monitor the status of Apache, MariaDB, and FTP services.

## Features

- **Service Management**: Easily start, stop, and restart Apache, MariaDB, and FileZilla/FTP services.
- **Real-time Status**: View the current running status of your services at a glance.
- **Bulk Actions**: Start or stop all services with a single click.
- **Multi-language Support**: Fully localized in English, Spanish, Portuguese, Mandarin, Italian, and French.
- **Robust Execution**: Built with Qt C++ using secure process handling.

## Installation

### Prerequisites

- Qt 5 development libraries (`qt5-default`, `qttools5-dev-tools`)
- Build essentials (`build-essential`)

### Building from Source

1. Clone the repository:

   ```bash
   git clone https://github.com/alvarosamudio/servermanager.git
   cd servermanager
   ```

2. Generate translations and compile:

   ```bash
   lrelease servermanager.pro
   qmake
   make
   ```

3. Run the application:
   ```bash
   ./ServerManager
   ```

### Building a Debian Package (.deb)

To create a verifiable Debian package for installation on Ubuntu, Debian, or Kali Linux:

```bash
dpkg-buildpackage -us -uc
```

This will generate a `.deb` file in the parent directory that can be installed using `dpkg -i` or `apt`.

## Usage

Launch the application to see the dashboard. The status of each service is updated automatically. Use the respective buttons to manage individual services or the "Start All" / "Stop All" buttons for bulk management.

The application automatically detects your system language. If your language is supported (ES, ZH, PT, IT, FR), the interface will be translated automatically.

## License

This project is licensed under the [MIT License](LICENSE).
