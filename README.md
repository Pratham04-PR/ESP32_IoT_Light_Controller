# ESP32 IoT Lighting Controller

| | |
|---|---|
| **Author** | Pratham Pathak |
| **Intern ID** | CITS2620 |
| **Internship** | CodTech IT Solutions Pvt. Ltd. |
| **Project Duration** | 13 June – 26 June 2026 |

A standalone ESP32-based local IoT lighting controller with a self-hosted
embedded HTTP server, AJAX-based browser control, persistent state
storage, and a dynamic web UI.

## Features
- ESP32 broadcasts its own WiFi network (SoftAP mode: `Room_Lights`) —
  no router or internet dependency.
- Single-page dashboard served directly from the ESP32.
- One-tap ON/OFF control via a relay module.
- Live status indicator ("ESP32 Online", current light state).
- Instant UI updates via `fetch()` — button presses swap in new HTML
  without a full page reload.
- Persistent state: light on/off status is saved to flash (`Preferences`
  library, backed by ESP32's NVS) and restored automatically after
  a power cycle or reboot.

## How it works
1. On boot, the ESP32 reads the last saved light state from NVS and
   restores the relay to that state.
2. It starts a WiFi Access Point — connect to it directly from a phone
   or laptop, then visit the ESP32's IP in a browser.
3. `/on` and `/off` routes toggle the relay and immediately persist the
   new state, so it's remembered even if power is cut.
4. The frontend calls these routes via `fetch()` and swaps in the
   returned HTML fragment without reloading the page.

## Hardware
| Component | ESP32 Pin |
|---|---|
| Relay module (active-low) | GPIO 23 |

## Setup
1. Open the `.ino` file in Arduino IDE, select your ESP32 board.
2. Upload.
3. On your phone/laptop, connect to WiFi network `Room_Lights`
   (password: `12345678`).
4. Open a browser and visit the IP printed in Serial Monitor
   (typically `192.168.4.1` for SoftAP mode).

## Talking points for interviews
- Why SoftAP was chosen over station mode — makes the device usable
  anywhere, with no dependency on an existing router.
- Why the relay logic is active-low, and what that means physically
  (`LOW` energizes the relay coil to switch the load on).
- Why `Preferences` (NVS-backed) was used instead of a plain RAM
  variable — state survives reboots/power loss.
- The server is synchronous (`WebServer`, polled via `handleClient()`),
  not the async `ESPAsyncWebServer` model — worth knowing the
  difference and trade-offs if asked.

## Possible extensions
- Support station mode + SoftAP fallback for production use.
- Add multiple relay channels for controlling more than one device.
- Migrate to `ESPAsyncWebServer` for genuinely non-blocking request handling.
