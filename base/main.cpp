#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <boost/asio.hpp>
#include <filesystem>
#include <csignal>

using namespace std;
using namespace boost::asio;

const char* window_title = "My WebView App";
const char* window_icon = "licox64.png"; // Set your icon path
const int port = 8081; // Change this to an unused port
const std::string assets_dir = "assets"; // Directory for assets
bool running = true; // Flag to control server loop

// Simple HTTP server
void start_server() {
    io_service io_service;
    ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port));

    while (running) {
        ip::tcp::socket socket(io_service);
        acceptor.accept(socket);

        // Read the request
        char request[1024];
        socket.read_some(boost::asio::buffer(request));

        // Extract the requested file path from the request
        std::string request_str(request);
        std::string requested_file = request_str.substr(4, request_str.find(" ", 4) - 4); // Get the requested URI

        if (requested_file == "/") {
            requested_file = "/index.html"; // Serve index.html by default
        }

        std::string file_path = assets_dir + requested_file;

        // Try to read the file content
        std::ifstream file(file_path);
        std::stringstream response;
        if (file) {
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            response << "HTTP/1.1 200 OK\r\n";
            response << "Content-Type: text/html\r\n";
            response << "Content-Length: " << content.length() << "\r\n";
            response << "\r\n";
            response << content;
        } else {
            // If file not found, send a 404 response
            response << "HTTP/1.1 404 Not Found\r\n";
            response << "Content-Type: text/html\r\n";
            response << "Content-Length: 36\r\n";
            response << "\r\n";
            response << "<h1>404 Not Found</h1>";
        }

        boost::asio::write(socket, boost::asio::buffer(response.str()));
    }

    // Clean up
    acceptor.close();
}

// Signal handler to set the running flag to false
void signal_handler(int signal) {
    running = false;
}

// Function to handle window destruction
void on_window_destroy(GtkWidget* widget, gpointer data) {
    running = false; // Stop the server loop
    gtk_main_quit(); // Exit the GTK main loop
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), window_title);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Set the window icon
    GdkPixbuf* icon = gdk_pixbuf_new_from_file(window_icon, NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    WebKitWebView* web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

    // Load the HTML file
    std::string url = "http://localhost:" + std::to_string(port);
    webkit_web_view_load_uri(web_view, url.c_str());

    // Connect the destroy signal
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(exit), NULL);

    gtk_widget_show_all(window);
}

int main(int argc, char* argv[]) {
    // Set up signal handling for graceful shutdown
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    // Start the server in a separate thread
    std::thread server_thread(start_server);

    GtkApplication* app = gtk_application_new("com.example.MyWebViewApp", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Wait for the server thread to finish
    running = false; // Set running to false to stop the server loop
    server_thread.join();

    g_object_unref(app);
    return status;
}
