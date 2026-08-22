# ESP32 IoT Lighting Controller

| | |
|---|---|
| **Author** | Pratham Pathak |

A standalone ESP32-based local IoT lighting controller with a self-hosted embedded HTTP server, asynchronous browser control using the Fetch API, persistent state storage, and a dynamic web UI.

---

## Features

- ESP32 broadcasts its own WiFi network using **SoftAP mode** (`Room_Lights`), requiring no router or internet connection.
- Single-page dashboard served directly from the ESP32.
- One-tap ON/OFF control through a relay module.
- Live device and light-status indicators.
- Asynchronous UI updates using the **JavaScript Fetch API**, without a full-page reload.
- HTTP response validation and browser-side connection error handling.
- Persistent light state using the **ESP32 Preferences library**, backed by NVS flash storage.
- Automatically restores the previous light state after reboot or power cycle.
- Modular firmware structure with dedicated functions for UI generation, relay control, and HTTP handlers.

---

## System Architecture

```text
                 Phone / Laptop
                       │
                       │ WiFi
                       ▼
              ┌─────────────────┐
              │   ESP32 SoftAP  │
              │  Room_Lights    │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │ Embedded HTTP   │
              │     Server      │
              └────────┬────────┘
                       │
              ┌────────┴────────┐
              │                 │
           /on route        /off route
              │                 │
              └────────┬────────┘
                       ▼
                ┌─────────────┐
                │ setLight()  │
                └──────┬──────┘
                       │
                       ▼
                  GPIO 23
                       │
                       ▼
                 Relay Module
                       │
                       ▼
                    Light


              ESP32 Persistent Storage
                       │
                       ▼
              Preferences / NVS
                       │
                       ▼
                 lightState
