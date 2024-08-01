#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

// Function to send key events to Godot via a TCP socket
void send_key_event_to_godot(const std::string &key) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    
    // Convert IP address to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address or Address not supported" << std::endl;
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed: is PNGTuber+ running?" << std::endl;
        close(sock);
        return;
    }

    send(sock, key.c_str(), key.size(), 0);
    close(sock);
}

// Function to set up a global keyboard grab and handle key events
void setup_global_keyboard_grab() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        return;
    }

    Window root = DefaultRootWindow(display);

    // Grabs top row number keys (considered different than numpad)
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("0")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("1")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("2")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("3")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("4")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("5")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("6")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("7")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("8")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("9")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, XKeysymToKeycode(display, XStringToKeysym("Home")), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);

    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            char buffer[10];
            KeySym keysym;
            XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);
            std::string key_str(buffer);
            char* escape_key = XKeysymToString(keysym);

            
            // Exit so we can ungrab the keys
            if(strcmp(escape_key, "Home") == 0) {
                return;
            } else {
                // Send key event to Godot
                send_key_event_to_godot(key_str);
            }
        }
    }

    XCloseDisplay(display);
}

void cleanup() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        return;
    }

    Window root = DefaultRootWindow(display);
    XUngrabKey(display, XStringToKeysym("0"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("1"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("2"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("3"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("4"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("5"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("6"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("7"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("8"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("9"), AnyModifier, root);
    XUngrabKey(display, XStringToKeysym("Home"), AnyModifier, root);


    XCloseDisplay(display);
}

int main() {
    setup_global_keyboard_grab();
    cleanup();
    return 0;
}
